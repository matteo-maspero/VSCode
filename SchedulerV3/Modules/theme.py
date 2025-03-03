from tkinter import ttk, Place
from sys import getwindowsversion
from pywinstyles import apply_style as change_header_color_w10, change_header_color as change_header_color_w11


class Palette:
	BG_NORMAL = "#2b2d30"
	BG_DARK = "#1e1f22"
	BG_LIGHT = "#3c3f41"
	FG_NORMAL = "#ffffff"
	FG_SELECTED = "#214283"


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
					"background": [("selected", Palette.FG_SELECTED)],
				}
			},

			"Heading": {
				"configure": {
					"background": Palette.BG_LIGHT,
					"font": ("Consolas", 10, "bold"),
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
