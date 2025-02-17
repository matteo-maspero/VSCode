from tkinter import *
import pywinstyles, sys
from Job import Job, State

# The color palette for our project.
DARK_GREY1 = "#1e1f22"
DARK_GREY2 = "#2b2d30"
WHITE1 = "#fafafa"


class App(Tk):
	"""

	"""
	def __init__(self, title: str, size: tuple[int, int]) -> None:
		# Configure the window of our application.
		super().__init__()
		self.minsize(size[0], size[1])
		self.set_dark_theme()
		self.config(bg=DARK_GREY1)
		self.iconbitmap("logo.ico")
		self.title(title)
		self.state("zoomed")

		# Define the layout of our application.
		self.columnconfigure(index=0, weight=1)
		self.columnconfigure(index=1, weight=3)
		self.rowconfigure(index=0, weight=6)
		self.rowconfigure(index=1, weight=1)
		self.rowconfigure(index=2, weight=3)

		# Set up the widgets we need.
		self.job_list = JobList(self)

	def set_dark_theme(self) -> None:
		version = sys.getwindowsversion()

		if version.major == 10 and version.build >= 22000:
			# We are running Windows 11 or later.
			pywinstyles.change_header_color(self, DARK_GREY2)
		elif version.major == 10:
			# We are running Windows 10.
			pywinstyles.apply_style(self, "dark")
			self.update()
			"""
			...if self.update doesnt work...
			self.wm_attributes("-alpha", 0.99)
			self.wm_attributes("-alpha", 1)
			"""


class JobList(Frame):
	def __init__(self, parent: Tk) -> None:
		# Configure the frame of our job list.
		super().__init__(parent)
		self.items: dict[Job, ListItem] = {}
		self.config(bg=DARK_GREY2)
		self.grid(row=0, column=0, sticky="nsew", padx=1, pady=1)
		self.columnconfigure(index=0, weight=1)
		ListItem(self, 0, "Name:", "Arrival:", "Burst:", "Priority:")

	def add_item(self, job: Job) -> None:
		item = ListItem(self, len(self.items) + 1, job.name, job.arrival, job.burst, job.priority)
		self.items[job] = item

	def remove_item(self, job: Job) -> None:
		self.items[job].destroy()
		del self.items[job]

class ListItem(Frame):
	"""

	"""
	def __init__(self, parent: JobList, row: int, name: str | float, arrival: str | float, burst: str | float, priority: str | float) -> None:
		# Configure the frame of this list item.
		super().__init__(parent)
		self.config(bg=DARK_GREY1)
		self.grid(row=row, column=0, sticky="ew", padx=1, pady=1)

		# Define a column for each of our job's details.
		self.columnconfigure(index=0, weight=4)
		self.columnconfigure(index=(1, 2, 3), weight=1)

		# Create the labels for each of our job's details.
		Label(self, text=name, anchor="w", bg=DARK_GREY1, fg=WHITE1).grid(row=0, column=0, sticky="nsew")
		Label(self, text=arrival, anchor="w", bg=DARK_GREY1, fg=WHITE1).grid(row=0, column=1, sticky="nsew")
		Label(self, text=burst, anchor="w", bg=DARK_GREY1, fg=WHITE1).grid(row=0, column=2, sticky="nsew")
		Label(self, text=priority, anchor="w", bg=DARK_GREY1, fg=WHITE1).grid(row=0, column=3, sticky="nsew")


if __name__ == "__main__":
	app = App(title="Scheduler by Maspero, Zappa & Sorbara", size=(800, 600))
	app.after(0, app.focus_force)

	# Add some dummy jobs to our job list.
	app.job_list.add_item(Job("Job 1", 0, 10, 1))
	app.job_list.add_item(Job("Job 2", 1, 20, 2))
	app.job_list.add_item(Job("Job 3", 2, 30, 3))

	app.mainloop()

"""
	CTkFrame(self, bg_color=DARK_GREY2).grid(row=0, column=0, sticky="nsew", padx=1, pady=1)
	CTkFrame(self, bg_color=DARK_GREY2).grid(row=0, column=1, rowspan=2, sticky="nsew", padx=1, pady=1)
	CTkFrame(self, bg_color=DARK_GREY2).grid(row=1, column=0, rowspan=2, sticky="nsew", padx=1, pady=1)
	CTkFrame(self, bg_color=DARK_GREY2).grid(row=2, column=1, sticky="nsew", padx=1, pady=1)
"""
