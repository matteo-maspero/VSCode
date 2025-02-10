from tkinter import *
from matplotlib import pyplot
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from Job import Job, State, JobInfo
from Scheduler import Scheduler

"""
	COLOR PALETTE
"""
GREY1 = "#1e1f22"
GREY2 = "#2b2d30"
GREY3 = "#3b3d40"
GREY4 = "#4b4d50"
RED1 = "#cc0000"
RED2 = "#aa1111"
WHITE1 = "#f0f0f0"

class GUI:
	def __init__(self):
		self.scheduler: Scheduler = Scheduler()

		"""
			ROOT CONFIGURATION
		"""
		self.root = Tk()
		self.root.geometry(f"{self.get_x_perc(70)}x{self.get_y_perc(70)}")
		self.root.state("zoomed")
		self.root.overrideredirect(True)

		"""
			WINDOW CONFIGURATION
		"""
		self.window = Frame(master=self.root, bg=GREY1)
		self.window.pack(fill=BOTH, expand=True)
		self.window.grid_columnconfigure(index=0, weight=1)
		self.window.grid_columnconfigure(index=1, weight=3)
		self.window.grid_rowconfigure(index=0, minsize=self.get_y_perc(4))
		self.window.grid_rowconfigure(index=1, weight=4)
		self.window.grid_rowconfigure(index=2, weight=1)
		self.window.grid_rowconfigure(index=3, weight=2)

		"""
			HEADER CONFIGURATION
		"""
		self.header = Frame(master=self.window, bg=GREY2, highlightthickness=.5, highlightbackground=GREY1, highlightcolor=GREY1, border=0)
		self.header.grid(row=0, column=0, columnspan=2, sticky="nsew")
		self.header.pack_propagate(False)

		# Make window draggable
		self.header.bind("<ButtonPress-1>", self.start_move)
		self.header.bind("<ButtonRelease-1>", self.stop_move)
		self.header.bind("<B1-Motion>", self.do_move)

		# Icon
		self.icon = PhotoImage(file="icon.png").subsample(2)
		self.icon_label = Label(master=self.header, image=self.icon, bg=GREY2)
		self.icon_label.pack(side=LEFT, fill=Y)

		# Title
		self.title = Label(master=self.header, text="Scheduler GUI by Maspero, Zappa & Sorbara", bg=GREY2, fg=WHITE1, font=("Arial", 10), border=0)
		self.title.pack(side=LEFT, fill=Y)

		# Close Button
		self.close_button = Button(master=self.header, text="✕", justify="center", bg=GREY2, fg=WHITE1, font=("Arial", 10), command=self.root.destroy, relief=FLAT, highlightthickness=0, activebackground=RED2, activeforeground=WHITE1, border=0)
		self.close_button.pack(side=RIGHT, fill=Y, ipadx=10)
		self.close_button.bind("<Enter>", lambda _: self.close_button.config(bg=RED1))
		self.close_button.bind("<Leave>", lambda _: self.close_button.config(bg=GREY2))

		# Window Button
		self.window_button = Button(master=self.header, text="🗗", justify="center", bg=GREY2, fg=WHITE1, font=("Arial", 16), command=self.toggle_window, relief=FLAT, highlightthickness=0, activebackground=GREY4, activeforeground=WHITE1, border=0)
		self.window_button.pack(side=RIGHT, fill=Y, ipadx=10)
		self.window_button.bind("<Enter>", lambda _: self.window_button.config(bg=GREY3))
		self.window_button.bind("<Leave>", lambda _: self.window_button.config(bg=GREY2))

		"""
			PROCESSES LIST CONFIGURATION
		"""
		self.list = Listbox(master=self.window, bg=GREY2, highlightthickness=.5, highlightbackground=GREY1, highlightcolor=GREY1, border=0)
		self.list.grid(row=1, column=0, sticky="nsew")

		"""
			GANTT CHART CONFIGURATION
		"""
		self.chart = Frame(master=self.window, bg=GREY1, highlightthickness=.5, highlightbackground=GREY2, highlightcolor=GREY2, border=0)
		self.chart.grid(row=1, rowspan=2, column=1, sticky="nsew")

		"""
			INPUTS CONFIGURATION
		"""
		self.inputs = Frame(master=self.window, bg=GREY2, highlightthickness=.5, highlightbackground=GREY1, highlightcolor=GREY1, border=0)
		self.inputs.grid(row=2, rowspan=2, column=0, sticky="nsew")

		"""
			OUTPUTS CONFIGURATION
		"""
		self.outputs = Frame(master=self.window, bg=GREY2, highlightthickness=.5, highlightbackground=GREY1, highlightcolor=GREY1, border=0)
		self.outputs.grid(row=3, column=1, sticky="nsew")

	"""
		IMPORTANT METHODS
	"""

	def update_list(self, processes: list[Job]):
		self.list.delete(0, END)
		for process in processes:
			self.list.insert(END, process)

	"""
		OTHER METHODS
	"""
	def get_x_perc(self, x: int) -> int:
		return int(x * .01 * self.root.winfo_screenwidth())
	
	def get_y_perc(self, y: int) -> int:
		return int(y * .01 * self.root.winfo_screenheight())
	
	def start_move(self, event):
		self.x = event.x
		self.y = event.y

	def stop_move(self, event):
		self.x = None
		self.y = None

	def do_move(self, event):
		x = self.root.winfo_pointerx() - self.x
		y = self.root.winfo_pointery() - self.y
		self.root.geometry(f"+{x}+{y}")

	def toggle_window(self):
		if self.root.state() == "normal":
			self.root.state("zoomed")
			self.window_button.config(text="🗗")
		else:
			self.root.state("normal")
			self.window_button.config(text="🗖")
