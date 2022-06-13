--------------------------------
--   Gabubu - awesome theme   --
--                            --
-- by Andrei                  --
-- based on the default theme --
--------------------------------

local theme_assets = require("beautiful.theme_assets")
local xresources = require("beautiful.xresources")
local dpi = xresources.apply_dpi

local gfs = require("gears.filesystem")
local themes_path = gfs.get_themes_dir()

local theme = {}

theme.font          = "terminus 8"

theme.bg_normal     = "#000955"
theme.bg_focus      = "#00063f"
theme.bg_urgent     = "#a10000"
theme.bg_minimize   = "#000f99"
theme.bg_systray    = "#000f81"

theme.fg_normal     = "#ffffff"
theme.fg_focus      = "#ffffff"
theme.fg_urgent     = "#ffffff"
theme.fg_minimize   = "#ffffff"

theme.useless_gap   = dpi(12)
theme.border_width  = dpi(1)
theme.border_normal = "#00085f"
theme.border_focus  = "#000c8e"
theme.border_marked = "#000329"

-- Generate taglist squares:
local taglist_square_size = dpi(4)
theme.taglist_squares_sel = theme_assets.taglist_squares_sel(
    taglist_square_size, theme.fg_normal
)
theme.taglist_squares_unsel = theme_assets.taglist_squares_unsel(
    taglist_square_size, theme.fg_normal
)

theme.menu_submenu_icon = themes_path.."gabubu/submenu.png"
theme.menu_height = dpi(15)
theme.menu_width  = dpi(100)

-- Define the image to load
theme.titlebar_close_button_normal = themes_path.."gabubu/titlebar/close_normal.png"
theme.titlebar_close_button_focus  = themes_path.."gabubu/titlebar/close_focus.png"

theme.titlebar_minimize_button_normal = themes_path.."gabubu/titlebar/minimize_normal.png"
theme.titlebar_minimize_button_focus  = themes_path.."gabubu/titlebar/minimize_focus.png"

theme.titlebar_ontop_button_normal_inactive = themes_path.."gabubu/titlebar/ontop_normal_inactive.png"
theme.titlebar_ontop_button_focus_inactive  = themes_path.."gabubu/titlebar/ontop_focus_inactive.png"
theme.titlebar_ontop_button_normal_active = themes_path.."gabubu/titlebar/ontop_normal_active.png"
theme.titlebar_ontop_button_focus_active  = themes_path.."gabubu/titlebar/ontop_focus_active.png"

theme.titlebar_sticky_button_normal_inactive = themes_path.."gabubu/titlebar/sticky_normal_inactive.png"
theme.titlebar_sticky_button_focus_inactive  = themes_path.."gabubu/titlebar/sticky_focus_inactive.png"
theme.titlebar_sticky_button_normal_active = themes_path.."gabubu/titlebar/sticky_normal_active.png"
theme.titlebar_sticky_button_focus_active  = themes_path.."gabubu/titlebar/sticky_focus_active.png"

theme.titlebar_floating_button_normal_inactive = themes_path.."gabubu/titlebar/floating_normal_inactive.png"
theme.titlebar_floating_button_focus_inactive  = themes_path.."gabubu/titlebar/floating_focus_inactive.png"
theme.titlebar_floating_button_normal_active = themes_path.."gabubu/titlebar/floating_normal_active.png"
theme.titlebar_floating_button_focus_active  = themes_path.."gabubu/titlebar/floating_focus_active.png"

theme.titlebar_maximized_button_normal_inactive = themes_path.."gabubu/titlebar/maximized_normal_inactive.png"
theme.titlebar_maximized_button_focus_inactive  = themes_path.."gabubu/titlebar/maximized_focus_inactive.png"
theme.titlebar_maximized_button_normal_active = themes_path.."gabubu/titlebar/maximized_normal_active.png"
theme.titlebar_maximized_button_focus_active  = themes_path.."gabubu/titlebar/maximized_focus_active.png"

theme.wallpaper = themes_path.."gabubu/wallpaper.png"

-- You can use your own layout icons like this:
theme.layout_fairh = themes_path.."gabubu/layouts/fairhw.png"
theme.layout_fairv = themes_path.."gabubu/layouts/fairvw.png"
theme.layout_floating  = themes_path.."gabubu/layouts/floatingw.png"
theme.layout_magnifier = themes_path.."gabubu/layouts/magnifierw.png"
theme.layout_max = themes_path.."gabubu/layouts/maxw.png"
theme.layout_fullscreen = themes_path.."gabubu/layouts/fullscreenw.png"
theme.layout_tilebottom = themes_path.."gabubu/layouts/tilebottomw.png"
theme.layout_tileleft   = themes_path.."gabubu/layouts/tileleftw.png"
theme.layout_tile = themes_path.."gabubu/layouts/tilew.png"
theme.layout_tiletop = themes_path.."gabubu/layouts/tiletopw.png"
theme.layout_spiral  = themes_path.."gabubu/layouts/spiralw.png"
theme.layout_dwindle = themes_path.."gabubu/layouts/dwindlew.png"
theme.layout_cornernw = themes_path.."gabubu/layouts/cornernww.png"
theme.layout_cornerne = themes_path.."gabubu/layouts/cornernew.png"
theme.layout_cornersw = themes_path.."gabubu/layouts/cornersww.png"
theme.layout_cornerse = themes_path.."gabubu/layouts/cornersew.png"

-- Generate Awesome icon:
theme.awesome_icon = theme_assets.awesome_icon(
    theme.menu_height, theme.bg_focus, theme.fg_focus
)

-- Define the icon theme for application icons. If not set then the icons
-- from /usr/share/icons and /usr/share/icons/hicolor will be used.
theme.icon_theme = nil

return theme
