/* user and group to drop privileges to */
static const char *user  = "nobody";
static const char *group = "nobody";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "#000433",     /* after initialization */
	[INPUT] =  "#000f95",   /* during input */
	[FAILED] = "#AA0000",   /* wrong password */
	[CAPS] = "#0011bd",         /* CapsLock on */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;

/* default message */
static const char * message = "Locked! Please enter the password!";

/* text color */
static const char * text_color = "#ffffff";

/* text size (must be a valid size) */
static const char * font_name = "6x10";

