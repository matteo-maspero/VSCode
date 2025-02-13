from tkinter import *
from dateutil.utils import within_delta
from matplotlib import pyplot
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from Job import Job, State, JobInfo

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
	def __init__(self, scheduler):
		self.scheduler = scheduler
		self.x: int = 0
		self.y: int = 0

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

		# Make window draggable
		self.header.bind("<ButtonPress-1>", self.start_move)
		self.header.bind("<ButtonRelease-1>", self.stop_move)
		self.header.bind("<B1-Motion>", self.do_move)

		# Icon
		self.icon = PhotoImage(file="icon.png").subsample(2)
		self.icon_label = Label(master=self.header, image=self.icon, bg=GREY2)
		self.icon_label.pack(side=LEFT, fill=Y)

		# Title
		self.title = Label(master=self.header, text="aaa GUI by Maspero, Zappa & Sorbara", bg=GREY2, fg=WHITE1, font=("Arial", 10), border=0)
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
		self.list = Frame(master=self.window, bg=GREY2, highlightthickness=.5, highlightbackground=GREY1, highlightcolor=GREY1, border=0)
		self.list.grid(row=1, column=0, sticky="nsew")
		self.update_list([])

		"""
			GANTT CHART CONFIGURATION
		"""
		self.chart = Frame(self.window, bg=GREY1, highlightthickness=1, highlightbackground=GREY2, highlightcolor=GREY3)
		self.chart.grid(row=1, column=1, rowspan=2, sticky="nsew")

		self.fig, self.ax = pyplot.subplots(figsize=(10, 5))
		self.canvas = FigureCanvasTkAgg(self.fig, master=self.chart)
		self.canvas.get_tk_widget().pack(fill=BOTH, expand=True)
		self.update_chart([])

		"""
			INPUTS CONFIGURATION
		"""
		self.inputs = Frame(master=self.window, bg=GREY2, highlightthickness=.5, highlightbackground=GREY1, highlightcolor=GREY1, border=0)
		self.inputs.grid(row=2, rowspan=2, column=0, sticky="nsew")
		
		# Algorithm selection
		self.algorithm_label = Label(master=self.inputs, text="Select Algorithm:", bg=GREY2, fg=WHITE1, font=("Arial", 10), border=0)
		self.algorithm_label.pack(pady=10, anchor="w", padx=10)
		self.algorithm_var = StringVar(value="FCFS")  # Default selection
		self.algorithm_dropdown = OptionMenu(self.inputs, self.algorithm_var, "FCFS", "RR", "SJF", command=self.change_alg)
		self.algorithm_dropdown.config(bg=GREY3, fg=WHITE1, font=("Arial", 10), highlightthickness=0, activebackground=GREY4, activeforeground=WHITE1, border=0)
		self.algorithm_dropdown.pack(pady=5, padx=10, anchor="w")

		# Process inputs
		self.name_label = Label(master=self.inputs, text="Name:", bg=GREY2, fg=WHITE1, font=("Arial", 10), border=0)
		self.name_label.pack(pady=5, anchor="w", padx=10)
		self.name_var = StringVar()
		self.name_entry = Entry(master=self.inputs, textvariable=self.name_var, bg=GREY3, fg=WHITE1, font=("Arial", 10), highlightthickness=0, insertbackground=WHITE1, borderwidth=1, relief=FLAT)
		self.name_entry.pack(pady=5, padx=10, anchor="w")

		self.arrival_label = Label(master=self.inputs, text="Arrival (ms):", bg=GREY2, fg=WHITE1, font=("Arial", 10), border=0)
		self.arrival_label.pack(pady=5, anchor="w", padx=10)
		self.arrival_var = StringVar()
		self.arrival_entry = Entry(master=self.inputs, textvariable=self.arrival_var, bg=GREY3, fg=WHITE1, font=("Arial", 10), highlightthickness=0, insertbackground=WHITE1, borderwidth=1, relief=FLAT)
		self.arrival_entry.pack(pady=5, padx=10, anchor="w")

		self.burst_label = Label(master=self.inputs, text="Burst (ms):", bg=GREY2, fg=WHITE1, font=("Arial", 10), border=0)
		self.burst_label.pack(pady=5, anchor="w", padx=10)
		self.burst_var = StringVar()
		self.burst_entry = Entry(master=self.inputs, textvariable=self.burst_var, bg=GREY3, fg=WHITE1, font=("Arial", 10), highlightthickness=0, insertbackground=WHITE1, borderwidth=1, relief=FLAT)
		self.burst_entry.pack(pady=5, padx=10, anchor="w")

		self.priority_label = Label(master=self.inputs, text="Priority:", bg=GREY2, fg=WHITE1, font=("Arial", 10), border=0)
		self.priority_label.pack(pady=5, anchor="w", padx=10)
		self.priority_var = StringVar()
		self.priority_entry = Entry(master=self.inputs, textvariable=self.priority_var, bg=GREY3, fg=WHITE1, font=("Arial", 10), highlightthickness=0, insertbackground=WHITE1, borderwidth=1, relief=FLAT)
		self.priority_entry.pack(pady=5, padx=10, anchor="w")

		# Add process button
		self.add_button = Button(master=self.inputs, text="Add Process", bg=GREY3, fg=WHITE1, font=("Arial", 10), command=self.add_process, relief=FLAT, highlightthickness=0, activebackground=GREY4, activeforeground=WHITE1, border=0)
		self.add_button.pack(pady=10, padx=10, anchor="w")

		# Start button
		self.start_button = Button(master=self.inputs, text="Execute", bg=GREY3, fg=WHITE1, font=("Arial", 10), command=self.scheduler.execute, relief=FLAT, highlightthickness=0, activebackground=GREY4, activeforeground=WHITE1, border=0)
		self.start_button.pack(pady=10, padx=10, anchor="w")

		"""
			OUTPUTS CONFIGURATION
		"""
		self.outputs = Frame(master=self.window, bg=GREY2, highlightthickness=.5, highlightbackground=GREY1, highlightcolor=GREY1, border=0)
		self.outputs.grid(row=3, column=1, sticky="nsew")

	"""
		IMPORTANT METHODS
	"""

	def update_chart(self, chart_info: list[JobInfo]):
		self.ax.clear()
		self.ax.set_title('Gantt Chart')
		self.ax.set_xlabel('Time ms')
		self.ax.set_ylabel('Processes')

		job_colors = ['tab:blue', 'tab:orange', 'tab:green', 'tab:red', 'tab:purple', 'tab:brown', 'tab:pink',
		              'tab:gray', 'tab:olive', 'tab:cyan']

		for i, info in enumerate(chart_info):
			self.ax.broken_barh([(info.start, info.width)], (info.id * 10, 10), facecolors=(job_colors[i % len(job_colors)]))
			self.ax.text(info.start + info.width / 2, i * 15 + 4.5, info.width, ha='center', va='center', color='white')

		self.ax.set_yticks([i * 10 + 5 for i in range(len(chart_info))])
		self.ax.set_yticklabels([info.name for info in chart_info])
		self.canvas.draw()

	def add_process(self):
		try:
			name = self.name_var.get()
			arrival = int(self.arrival_var.get())
			burst = int(self.burst_var.get())
			priority = int(self.priority_var.get())
			self.scheduler.add_process(Job(name, arrival, burst, priority))
		except ValueError:
			pass

	def update_list(self, jobs: list[Job]):
		for j, header in enumerate(["Process:", "Arrival ms:", "Burst ms:", "Priority:"]):
			label = Label(master=self.list, text=header, bg=GREY2, fg=WHITE1, font=("Arial", 10, "bold"), border=0)
			label.grid(row=0, column=j, sticky="nsew", pady=10)

		for i, job in enumerate(jobs):
			for j, value in enumerate([job.name, job.arrival, job.burst, job.priority]):
				label = Label(master=self.list, text=value, bg=GREY2, fg=WHITE1, font=("Arial", 10), border=0)
				label.grid(row=i + 1, column=j, sticky="nsew", pady=5)

	def change_alg(self, _):
		self.scheduler.chosen_algorithm = self.algorithm_var.get()
		if self.scheduler.chosen_algorithm == "RR":
			# Add quantum input if it doesn't exist
			if not hasattr(self, 'quantum_label'):
				self.quantum_label = Label(
					master=self.inputs, text="Quantum (ms):", bg=GREY2, fg=WHITE1, font=("Arial", 10), border=0
				)
				self.quantum_label.pack(pady=10, anchor="w", padx=10)
				self.quantum_var = StringVar()
				self.quantum_entry = Entry(
					master=self.inputs, textvariable=self.quantum_var, bg=GREY3, fg=WHITE1, font=("Arial", 10),
					highlightthickness=0, insertbackground=WHITE1, borderwidth=1, relief=FLAT
				)
				self.quantum_entry.pack(pady=5, padx=10, anchor="w")
			# Assign the quantum value to the scheduler
			self.quantum_var.trace("w", lambda *args: self.update_quantum())
		else:
			# Remove quantum input if it exists
			if hasattr(self, 'quantum_label'):
				self.quantum_label.destroy()
				self.quantum_entry.destroy()
				del self.quantum_label
				del self.quantum_entry
				del self.quantum_var

	def update_quantum(self):
		try:
			self.scheduler.quantum = max(1, int(self.quantum_var.get()))
		except ValueError:
			pass  # Ignore invalid input

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

	def stop_move(self, _):
		self.x = None
		self.y = None

	def do_move(self, _):
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
