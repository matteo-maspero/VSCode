from tkinter import *
import sys
import pywinstyles
from Scheduler import Scheduler
from Job import Job, State

# The color palette for our project.
DARK_GREY1 = "#1e1f22"
DARK_GREY2 = "#2b2d30"
WHITE1 = "#fafafa"


class App(Tk):
	"""

	"""
	def __init__(self, title: str, size: tuple[int, int]) -> None:
		super().__init__()
		self.scheduler: Scheduler = Scheduler(self)

		# Configure the window of our application.
		self.minsize(size[0], size[1])
		self.set_dark_theme()
		self.iconbitmap("logo.ico")
		self.title(title)
		self.state("zoomed")

		# Define the layout of our application.
		self.columnconfigure(index=0, weight=1)
		self.columnconfigure(index=1, weight=3)
		self.rowconfigure(index=0, weight=6)
		self.rowconfigure(index=1, weight=1)
		self.rowconfigure(index=2, weight=3)

		# Set up the panels we need.
		self.job_list_panel = JobListPanel(self)
		self.input_panel = InputPanel(self)

	def set_dark_theme(self) -> None:
		version = sys.getwindowsversion()
		self.config(bg=DARK_GREY1)

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


class JobListPanel(Frame):
	"""

	"""
	def __init__(self, parent: Tk) -> None:
		super().__init__(parent)
		self.items: dict[Job, ListItem] = {}

		# Configure the frame of our job list.
		self.config(bg=DARK_GREY2)
		self.grid(row=0, column=0, sticky="nsew", padx=1, pady=1)
		self.columnconfigure(index=0, weight=1)

		self.header = ListItem(self, "Name:", "Arrival:", "Burst:", "Priority:")
		self.header.grid(row=0, column=0, sticky="ew", padx=1, pady=1)

	def add_item(self, job: Job) -> None:
		item = ListItem(self, job.name, job.arrival, job.burst, job.priority)
		self.items[job] = item

	def remove_item(self, job: Job) -> None:
		self.items[job].destroy()
		del self.items[job]


class ListItem(Frame):
	"""

	"""
	def __init__(self, parent: JobListPanel, name: str | float, arrival: str | float, burst: str | float, priority: str | float) -> None:
		super().__init__(parent)

		# Configure the frame of this list item.
		self.config(bg=DARK_GREY1)
		self.grid(row=len(parent.items) + 1, column=0, sticky="ew", padx=1, pady=1)

		# Define a column for each of our job's details.
		self.columnconfigure(index=0, weight=4)
		self.columnconfigure(index=(1, 2, 3), weight=1)

		# Create the labels for each of our job's details.
		Label(self, text=name, anchor="w", bg=DARK_GREY1, fg=WHITE1, width=1).grid(row=0, column=0, sticky="nsew")
		Label(self, text=arrival, anchor="w", bg=DARK_GREY1, fg=WHITE1, width=1).grid(row=0, column=1, sticky="nsew")
		Label(self, text=burst, anchor="w", bg=DARK_GREY1, fg=WHITE1, width=1).grid(row=0, column=2, sticky="nsew")
		Label(self, text=priority, anchor="w", bg=DARK_GREY1, fg=WHITE1, width=1).grid(row=0, column=3, sticky="nsew")


class InputPanel(Frame):
	"""

	"""
	def __init__(self, parent: Tk):
		super().__init__(parent)

		# Configure the frame of our input panel.
		self.config(bg=DARK_GREY2)
		self.grid(row=1, column=0, rowspan=2, sticky="nsew", padx=1, pady=1)

		self.columnconfigure(index=0, weight=1)
		self.columnconfigure(index=1, weight=2)


class InputLabel(Frame):
	def __init__(self, parent: InputPanel, text: str, interface):
		super().__init__(parent)
		self.choice: StringVar = StringVar(self, value="FCFS")

		# Set up the label for our input.
		self.label = Label(self, text="Choose algorithm:", anchor="w", width=1)
		self.label.config(bg=DARK_GREY1, fg=WHITE1)
		self.label.grid(row=0, column=0, sticky="nsew", padx=1, pady=1)

	def on_input(self, _):
		print(self.choice.get())


class AlgorithmChoiceMenu(OptionMenu):
	def __init__(self, parent: InputLabel):
		super().__init__(parent, parent.choice, "FCFS", "SJF", "RR", command=parent.on_input)
		self.config(bg=DARK_GREY1, fg=WHITE1, highlightthickness=0, activebackground=DARK_GREY1, activeforeground=WHITE1, border=0, width=1)
		self.grid(row=0, column=1, sticky="nsew", padx=1, pady=1)


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
