/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 15;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 3;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
#define ICONSIZE 16   /* icon size */
#define ICONSPACING 5 /* space between icon and title */
static const int topbar             = 1;     /* 0 means bottom bar */
static const int focusonwheel       = 0;     /* 0 means it won't use the wheel instead of click to focus */
static const int user_bh            = 20;       /* height of the bar */
static const char *fonts[]          = { "terminus:size=9", "Siji" }; // Add (Font Awesome 6 Free:size10:antialias=true) and (Font Awesome 6 Brands:size=10:antialias=true) for FontAwesome font
static const char dmenufont[]       = "terminus:size=9";
static const char col_white[]       = "#ffffff"; // white
static const char col_gray[]        = "#b5b5b5"; // gray {for unsellected duh}
static const char col_minus3[]      = "#000329"; // main gabubu color but a bit dimmer but dimmer but dimmer
static const char col_minus2[]      = "#000851"; // main gabubu color but a bit dimmer but dimmer
static const char col_minus1[]      = "#00085f"; // main gabubu color but a bit dimmer
static const char col_plus1[]       = "#0015cf"; // main gabubu color but a bit brighter
static const char col_main[]        = "#000c8e"; // main gabubu color
static const char *colors[][3]      = {
	/*                      fg         bg         border   */
	[SchemeNorm]      = { col_white, col_main, col_minus1 },
	[SchemeSel]       = { col_white, col_minus2,  col_main  },
	[SchemeStatus]    = { col_white, col_minus1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]   = { col_white, col_minus3,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_gray, col_minus1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]   = { col_white, col_minus2,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_gray, col_minus1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "SimpleScreenRecorder",     NULL,       NULL,       0,            1,           -1 },
	{ "Krita",    NULL,       NULL,       0,            1,           -1 },
	{ "mpv",      NULL,       NULL,      0,            1,           -1 },
};

/* window swallowing */
static const int swaldecay = 3;
static const int swalretroactive = 1;
static const char swalsymbol[] = "???";

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "???",      tile },    /* first entry is default */
	{ "???",      NULL },    /* no layout function means floating behavior */
	{ "???",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *dmpc[] = { "dmpc", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *flameshot[] = { "flameshot", "gui",  NULL };
static const char *upvol[]   = { "/usr/bin/pulsemixer", "--id", "sink-0", "--max-volume", "100", "--change-volume", "+5",     NULL }; /* Volume up using pulsemixer */
static const char *downvol[] = { "/usr/bin/pulsemixer", "--id", "sink-0", "--max-volume", "100", "--change-volume", "-5",     NULL }; /* Volume down using pulsemixer */
static const char *mutevol[] = { "/usr/bin/pulsemixer", "--id", "sink-0", "--toggle-mute",     NULL }; /* Mute/unmute using pulsemixer */
static const char *mutemic[] = { "/usr/bin/pulsemixer", "--id", "source-1", "--toggle-mute",     NULL }; /* Mute/unmute mic using pulsemixer */
/*static const char *upvol[]   = { "/usr/bin/amixer", "-q", "sset", "Master", "5%+",     NULL };  Volume up using amixer  */
/*static const char *downvol[] = { "/usr/bin/amixer", "-q", "sset", "Master", "5%-",     NULL };  Volume down using amixer */
/*static const char *mutevol[] = { "/usr/bin/amixer", "-q", "sset", "Master", "toggle",  NULL };  Mute/unmute using amixer */
/*static const char *mutemic[] = { "/usr/bin/amixer", "set", "Capture", "toggle", NULL };  Mute/unmute mic using amixer */
static const char *light_up[] = {"/usr/bin/light", "-A", "5", NULL};
static const char *light_down[] = {"/usr/bin/light", "-U", "5", NULL};
static const char *display[] = {"/bin/ddisplay", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = dmpc } },
	{ 0,                            XK_Print,  spawn,          {.v = flameshot } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = display } },
	{ 0,                            XF86XK_AudioLowerVolume,  spawn,      {.v = downvol } },
	{ 0,                            XF86XK_AudioMute,         spawn,      {.v = mutevol } },
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn,      {.v = upvol   } },
	{ 0,     			XF86XK_MonBrightnessUp,   spawn,      {.v = light_up } },
	{ 0,	        		XF86XK_MonBrightnessDown, spawn,      {.v = light_down } },
	{ 0,                            XF86XK_AudioMicMute,         spawn,      {.v = mutemic } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_u,      swalstopsel,    {0} },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,      swalmouse,      {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

