from tkinter import ttk, Place
from sys import getwindowsversion
from pywinstyles import apply_style as change_header_color_w10, change_header_color as change_header_color_w11


class Palette:
	BG_NORMAL = "#2b2d30"
	BG_EVEN = "#202030"
	BG_DARK = "#1e1f22"
	BG_LIGHT = "#3c3f41"
	BG_SELECTED = "#214283"
	FG_NORMAL = "#ffffff"


def create_dark_theme(window):
	window.style.theme_create(
		themename="dark",
		settings={
			".": {
				"configure": {
					"background": Palette.BG_NORMAL,
					"foreground": Palette.FG_NORMAL,
					"highlightthickness": 0,
					"focuscolor": 0,
					"borderwidth": 0,
					"font": ("Consolas", 10),
				}
			},

			"Treeview": {
				"configure": {
					"focuscolor": Palette.BG_NORMAL,
					"fieldbackground": Palette.BG_DARK,
				},
				"map": {
					"background": [("selected", Palette.BG_SELECTED)],
				}
			},

			"Heading": {
				"configure": {
					"background": Palette.BG_LIGHT,
					"font": ("Consolas", 10, "bold"),
				}
			},

			"Item": {
				"configure": {
					"indicatorsize": 12,
					"indicatormargins": 4,
				}
			},

			"Cell": {
				"configure": {
					"padding": 4,
				}
			},

			"Vertical.TScrollbar": {
				"configure": {
					"arrowsize": 8,
					"arrowcolor": Palette.FG_NORMAL,
					"background": Palette.BG_LIGHT,
					"troughcolor": Palette.BG_NORMAL,
					"width": 8,
				}
			},

			"TButton": {
				"configure": {
					"background": Palette.BG_LIGHT,
					"foreground": Palette.FG_NORMAL,
					"padding": 4,
				},
				"map": {
					"background": [("active", Palette.BG_SELECTED)],
					"padding": [("pressed", (5,5,3,3))],
				}
			},

			"TLabel": {
				"configure": {
					"background": Palette.BG_LIGHT,
					"foreground": Palette.FG_NORMAL,
					"padding": 4,
				}
			},

			"TCombobox": {
				"configure": {
					"arrowcolor": Palette.FG_NORMAL,
					"arrowsize": 12,
					"background": Palette.BG_LIGHT,
					"foreground": Palette.FG_NORMAL,
					"selectbackground": Palette.BG_LIGHT,
					"padding": 4,
				}
			},

			"TEntry": {
				"configure": {
					"background": Palette.BG_LIGHT,
					"foreground": Palette.FG_NORMAL,
					"padding": 4,
					"insertcolor": Palette.FG_NORMAL,
				}
			},
		}
	)


def use_dark_theme(window):
	window.style.theme_use("dark")
	window.configure(background=Palette.BG_DARK)

	# Change header color for Windows 10 and 11
	version = getwindowsversion()
	if version.major < 10:
		return

	if version.build < 22000:
		change_header_color_w10(window, "dark")
		window.update()
	else:
		change_header_color_w11(window, Palette.BG_DARK)
