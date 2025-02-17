from tkinter import *
from multipledispatch import dispatch
from sys import getwindowsversion
from pywinstyles import change_header_color, apply_style
from Scheduler import Scheduler
from Job import Job, State

# App configuration:
MAX_JOBS = 32

# The color palette for our project:
DARK_GREY1 = "#1e1f22"
DARK_GREY2 = "#2b2d30"
WHITE1 = "#fafafa"


class App(Tk):
	"""

	"""
	def __init__(self, title: str, size: tuple[int, int]):
		super().__init__()
		self.scheduler: Scheduler = Scheduler(self)

		# App configuration:
		self.minsize(size[0], size[1])
		self.set_dark_theme()
		self.iconbitmap("logo.ico")
		self.title(title)
		self.state("zoomed")

		self.columnconfigure(index=0, weight=1)
		self.columnconfigure(index=1, weight=3)
		self.rowconfigure(index=0, weight=6)
		self.rowconfigure(index=1, weight=1)
		self.rowconfigure(index=2, weight=3)

		self.jobs_panel = JobsPanel(self)

	def set_dark_theme(self):
		version = getwindowsversion()
		self.config(bg=DARK_GREY1)

		if version.major == 10 and version.build >= 22000:
			# We are running Windows 11 or later.
			change_header_color(self, DARK_GREY2)
		elif version.major == 10:
			# We are running Windows 10.
			apply_style(self, "dark")
			self.update()
			"""
			...if 'self.update' doesnt work...
			self.wm_attributes("-alpha", 0.99)
			self.wm_attributes("-alpha", 1)
			"""


class PanelTitle(Label):
	"""

	"""
	def __init__(self, parent: Frame, text: str):
		super().__init__(parent, text=text, font=("Arial", 10, "bold"), anchor="w", bg=DARK_GREY2, fg=WHITE1)
		self.grid(row=0, column=0, sticky="nsew", padx=1, pady=1)


class JobsPanel(Frame):
	"""

	"""
	def __init__(self, parent: App):
		super().__init__(parent, bg=DARK_GREY2)
		self.grid(row=0, column=0, sticky="nsew", padx=1, pady=1)
		self.columnconfigure(index=0, weight=1)
		self.rowconfigure(index=1, weight=1)

		# Panel title:
		self.panel_title = PanelTitle(self, "Jobs")
		self.job_list = self.List(self)

	class List(Frame):
		def __init__(self, parent):
			super().__init__(parent, bg=DARK_GREY2)
			self.grid(row=1, column=0, sticky="nsew", padx=1, pady=1)
			self.columnconfigure(index=0, weight=1)
			self.items: dict[Job, JobsPanel.List.Item] = {}
			self.header = self.Header(self, "Name:", "Arrival:", "Burst:", "Priority:")

		def add_item(self, job: Job):
			assert len(self.items) < MAX_JOBS, "The maximum number of jobs has been exceeded."
			self.items[job] = self.Item(self, job)

		def remove_item(self, job: Job):
			self.items[job].destroy()
			del self.items[job]

		class Header(Frame):
			def __init__(self, parent, *titles: str):
				super().__init__(parent, bg=DARK_GREY1)
				self.grid(row=0, column=0, sticky="ew", padx=1, pady=1)
				self.columnconfigure(index=0, weight=4)
				self.columnconfigure(index=(1,2,3), weight=1)

				for i, title in enumerate(titles):
					Label(self, text=title, anchor="w", bg=DARK_GREY1, fg=WHITE1).grid(row=0, column=i, sticky="nsew")


		class Item(Frame):
			def __init__(self, parent, job: Job):
				super().__init__(parent, bg=DARK_GREY1)
				self.grid(row=len(parent.items), column=0, sticky="ew", padx=1, pady=1)
				self.columnconfigure(index=0, weight=1)

				# TODO
				

if __name__ == "__main__":
	app = App(title="Scheduler by Maspero, Zappa & Sorbara", size=(800, 600))
	app.after(0, app.focus_force)
	app.mainloop()

"""
	CTkFrame(self, bg_color=DARK_GREY2).grid(row=0, column=0, sticky="nsew", padx=1, pady=1)
	CTkFrame(self, bg_color=DARK_GREY2).grid(row=0, column=1, rowspan=2, sticky="nsew", padx=1, pady=1)
	CTkFrame(self, bg_color=DARK_GREY2).grid(row=1, column=0, rowspan=2, sticky="nsew", padx=1, pady=1)
	CTkFrame(self, bg_color=DARK_GREY2).grid(row=2, column=1, sticky="nsew", padx=1, pady=1)
"""
