import tkinter as tk
from tkinter import ttk
import Modules.theme as theme
from Modules.theme import Palette


class App(tk.Tk):
	def __init__(self):
		super().__init__()
		self.style = ttk.Style(master=self)
		self.h_pane = HPane(master=self)

		self.setup()
		self.enable_dark_theme()

	def setup(self):
		self.minsize(width=800, height=600)
		self.geometry("800x600")
		self.state("zoomed")
		self.title("Scheduler GUI")

	def enable_dark_theme(self):
		theme.create_dark_theme(window=self)
		theme.use_dark_theme(window=self)


class HPane(tk.PanedWindow):
	def __init__(self, master: App, **kwargs):
		super().__init__(master=master, **kwargs)
		self.job_handler = JobHandler(master=self)
		self.v_paned = VPaned(master=self)

		self.setup()
		self.add_panes()

	def setup(self):
		self.configure(orient="horizontal", background=Palette.BG_DARK, sashwidth=2, border=0)
		self.pack(fill="both", expand=True)

	def add_panes(self):
		self.add(self.job_handler, width=1, minsize=300, stretch="always")
		self.add(self.v_paned, width=4, minsize=1300, stretch="always")


class JobHandler(tk.PanedWindow):
	def __init__(self, master: HPane, **kwargs):
		super().__init__(master=master, **kwargs)
		self.job_info = JobInfo(master=self)
		self.shell = Shell(master=self)

		self.setup()
		self.add_panes()

	def setup(self):
		self.configure(orient="vertical", background=Palette.BG_DARK, sashwidth=2, border=0)

	def add_panes(self):
		self.add(self.job_info, height=7, minsize=500, stretch="always")
		self.add(self.shell, height=3, minsize=220, stretch="always")

		
class JobInfo(ttk.Frame):
	def __init__(self, master: JobHandler, **kwargs):
		super().__init__(master=master, **kwargs)
		self.job_tree = JobTree(master=self)
		self.job_tree_scrollbar = JobTreeScrollbar(master=self, command=self.job_tree.yview)
		self.job_tree.configure(yscrollcommand=self.job_tree_scrollbar.set)

		self.setup()

	def setup(self):
		self.pack(side="top", fill="both", expand=True)

		
class JobTree(ttk.Treeview):
	def __init__(self, master: JobInfo, **kwargs):
		super().__init__(master=master, **kwargs)
		self.setup()
		self.setup_columns()

		for i in range(1,10):
			self.insert(parent="", index="end", values=(f"P{i}", 0, 0, 0))


	def setup(self):
		self.configure(
			columns=("name", "arrival", "burst", "priority"),
			selectmode="extended",
			show="headings",
		)
		self.tag_configure("oddrow", background=Palette.BG_NORMAL)
		self.tag_configure("evenrow", background=Palette.BG_EVEN)
		self.pack(side="left", fill="both", expand=True)

	def setup_columns(self):
		self.column("name", width=80)
		self.column("arrival", width=40)
		self.column("burst", width=40)
		self.column("priority", width=40)
		self.heading("name", text="Job name", anchor="w")
		self.heading("arrival", text="Arrival", anchor="w")
		self.heading("burst", text="Burst", anchor="w")
		self.heading("priority", text="Priority", anchor="w")


class JobTreeScrollbar(ttk.Scrollbar):
	def __init__(self, master: JobInfo, **kwargs):
		super().__init__(master=master, **kwargs)
		self.setup()

	def setup(self):
		self.configure(orient="vertical")
		self.pack(side="right", fill="y")


class Shell(ttk.Frame):
	def __init__(self, master: JobHandler, **kwargs):
		super().__init__(master=master, **kwargs)
		self.input_job_button = GenericButton(master=self, text="Insert a new job")
		self.generate_random_job_button = GenericButton(master=self, text="Generate a new random job")
		self.remove_selected_jobs_button = GenericButton(master=self, text="Remove selected jobs")
		self.select_algorithm_combobox = SelectAlgorithmCombobox(master=self)
		self.input_quantum_time = InputQuantumTime(master=self)

		self.setup()

	def setup(self):
		self.pack(side="bottom", fill="both", expand=True)


class GenericButton(ttk.Button):
	def __init__(self, master: Shell, **kwargs):
		super().__init__(master=master, **kwargs)
		self.setup()

	def setup(self):
		self.configure(width=30)
		self.pack(side="top", anchor="w", padx=8, pady=(8,0))


class SelectAlgorithmCombobox(ttk.Combobox):
	def __init__(self, master: Shell, **kwargs):
		super().__init__(master=master, **kwargs)
		self.variable = tk.Variable(value="FCFS")
		self.title = ttk.Label(master=master, text="Select algorithm:")

		self.setup_title()
		self.setup()

	def setup_title(self):
		self.title.configure(anchor="w", width=30)
		self.title.pack(side="top", anchor="w", padx=8, pady=(8,0))

	def setup(self):
		self.configure(textvariable=self.variable, state="readonly", values=("FCFS", "SJF", "RR"), width=33)
		self.pack(side="top", anchor="w", padx=8)


class InputQuantumTime(ttk.Entry):
	def __init__(self, master: Shell, **kwargs):
		super().__init__(master=master, **kwargs)
		self.variable = tk.Variable(value=4)
		self.title = ttk.Label(master=master, text="Insert quantum time:")

		self.setup_title()
		self.setup()

	def setup_title(self):
		self.title.configure(anchor="w", width=30)
		self.title.pack(side="top", anchor="w", padx=8, pady=(8,0))

	def setup(self):
		self.configure(width=35)
		self.pack(side="top", anchor="w", padx=8)


class VPaned(tk.PanedWindow):
	def __init__(self, master: HPane, **kwargs):
		super().__init__(master=master, **kwargs)
		self.chart = Chart(master=self)
		self.console = Console(master=self)

		self.setup()
		self.add_panes()

	def setup(self):
		self.configure(orient="vertical", background=Palette.BG_DARK, sashwidth=2, border=0)

	def add_panes(self):
		self.add(self.chart, height=5, minsize=600, stretch="always")
		self.add(self.console, height=3, minsize=200, stretch="always")


class Chart(ttk.Frame):
	def __init__(self, master: VPaned, **kwargs):
		super().__init__(master=master, **kwargs)
		self.setup()

	def setup(self):
		pass


class Console(ttk.Frame):
	def __init__(self, master: VPaned, **kwargs):
		super().__init__(master=master, **kwargs)
		self.setup()

	def setup(self):
		pass
