from tkinter import *
from Job import Job
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

"""
	Color palette
"""
GREY1 = "#1a1a1a"
GREY2 = "#2a2a2a"
GREY3 = "#3a3a3a"
WHITE1 = "#e5e5e5"

class Gui:
	def __init__(self, scheduler):
		self.scheduler = scheduler

		self.setupRoot()
		self.setupWindow()
		self.setupJobsList()
		self.setupJobInput()
		self.setupGanttChart()
		self.setupStatistics()

	def setupRoot(self):
		self.root = Tk()
		self.root.title("Scheduler GUI")
		self.root.iconbitmap('Scheduler\\icon.ico')
		self.root.geometry("1000x600")
		self.root.state("zoomed")

	def setupWindow(self):
		self.window = Frame(master=self.root)
		self.window.pack(fill=BOTH, expand=True)
		self.window.configure(bg = GREY1)
		self.window.grid_columnconfigure(0, weight=1)
		self.window.grid_columnconfigure(1, weight=4)
		self.window.grid_rowconfigure(0, weight=1)
		self.window.grid_rowconfigure(1, weight=20)
		self.window.grid_rowconfigure(2, weight=10)
		self.window.grid_rowconfigure(3, weight=1)

	def setupJobsList(self):
		self.jobsList = Listbox(self.window, bg=GREY1, fg=WHITE1, bd=0, highlightthickness=1, highlightbackground=GREY2, highlightcolor=GREY3)
		self.jobsList.grid(row=0, column=0, rowspan=2, sticky="nsew")

	def setupJobInput(self):
		self.jobInputFrame = Frame(self.window, bg=GREY1, highlightthickness=1, highlightbackground=GREY2, highlightcolor=GREY3)
		self.jobInputFrame.grid(row=2, column=0, sticky="nsew")

		Label(self.jobInputFrame, text="Add a new process:", bg=GREY1, fg=WHITE1, font=("Helvetica", 16)).grid(row=0, column=0, columnspan=2, pady=10)

		Label(self.jobInputFrame, text="Job ID", bg=GREY1, fg=WHITE1).grid(row=1, column=0, padx=5, pady=5)
		self.jobIdEntry = Entry(self.jobInputFrame, bg=GREY2, fg=WHITE1)
		self.jobIdEntry.grid(row=1, column=1, padx=5, pady=5)

		Label(self.jobInputFrame, text="Priority", bg=GREY1, fg=WHITE1).grid(row=2, column=0, padx=5, pady=5)
		self.priorityEntry = Entry(self.jobInputFrame, bg=GREY2, fg=WHITE1)
		self.priorityEntry.grid(row=2, column=1, padx=5, pady=5)

		Label(self.jobInputFrame, text="Arrival Time", bg=GREY1, fg=WHITE1).grid(row=3, column=0, padx=5, pady=5)
		self.arrivalTimeEntry = Entry(self.jobInputFrame, bg=GREY2, fg=WHITE1)
		self.arrivalTimeEntry.grid(row=3, column=1, padx=5, pady=5)

		Label(self.jobInputFrame, text="Burst Time", bg=GREY1, fg=WHITE1).grid(row=4, column=0, padx=5, pady=5)
		self.burstTimeEntry = Entry(self.jobInputFrame, bg=GREY2, fg=WHITE1)
		self.burstTimeEntry.grid(row=4, column=1, padx=5, pady=5)

		self.addButton = Button(self.jobInputFrame, text="Add", command=self.addJob, bg=GREY3, fg=WHITE1)
		self.addButton.grid(row=5, column=0, pady=10)

		self.clearButton = Button(self.jobInputFrame, text="Clear", command=self.clearInputs, bg=GREY3, fg=WHITE1)
		self.clearButton.grid(row=5, column=1, pady=10)

		self.fcfsButton = Button(self.jobInputFrame, text="Execute FCFS", command=self.scheduler.executeFCFS, bg=GREY3, fg=WHITE1)
		self.fcfsButton.grid(row=6, column=0, pady=10)

		self.sjfButton = Button(self.jobInputFrame, text="Execute SJF", command=self.scheduler.executeSJF, bg=GREY3, fg=WHITE1)
		self.sjfButton.grid(row=6, column=1, pady=10)

	def addJob(self):
		try:
			name = self.jobIdEntry.get()
			if name == "":
				raise ValueError
			priority = int(self.priorityEntry.get())
			arrival = int(self.arrivalTimeEntry.get())
			burst = int(self.burstTimeEntry.get())
		except:
			self.clearInputs()
			return
		
		self.scheduler.addJob(Job(name, priority, arrival, burst))

	def clearInputs(self):
		self.jobIdEntry.delete(0, END)
		self.priorityEntry.delete(0, END)
		self.arrivalTimeEntry.delete(0, END)
		self.burstTimeEntry.delete(0, END)
		
	def updateJobsList(self):
		self.jobsList.delete(0, END)
		for job in self.scheduler.readyQueue:
			self.jobsList.insert(END, f"Job ID: {job.name}, Priority: {job.priority}, Arrival: {job.arrival}, Burst: {job.burst}")

	def setupGanttChart(self):
		self.ganttFrame = Frame(self.window, bg=GREY1, highlightthickness=1, highlightbackground=GREY2, highlightcolor=GREY3)
		self.ganttFrame.grid(row=0, column=1, rowspan=2, sticky="nsew")

		self.fig, self.ax = plt.subplots(figsize=(10, 5))
		self.canvas = FigureCanvasTkAgg(self.fig, master=self.ganttFrame)
		self.canvas.get_tk_widget().pack(fill=BOTH, expand=True)

	def updateGanttChart(self):
		self.ax.clear()
		self.ax.set_title('Gantt Chart')
		self.ax.set_xlabel('Time ms')
		self.ax.set_ylabel('Jobs')

		job_colors = ['tab:blue', 'tab:orange', 'tab:green', 'tab:red', 'tab:purple', 'tab:brown', 'tab:pink', 'tab:gray', 'tab:olive', 'tab:cyan']
		for i, (job, start) in enumerate(self.scheduler.chartInfo):
			self.ax.broken_barh([(start, job.burst)], (i * 15, 9), facecolors=(job_colors[i % len(job_colors)]))
			self.ax.text(start + job.burst / 2, i * 15 + 4.5, job.burst, ha='center', va='center', color='white')

		self.ax.set_yticks([i * 15 + 4.5 for i in range(len(self.scheduler.chartInfo))])
		self.ax.set_yticklabels([job.name for job, _ in self.scheduler.chartInfo])
		self.canvas.draw()

	def setupStatistics(self):
		self.statsFrame = Frame(self.window, bg=GREY1, highlightthickness=1, highlightbackground=GREY2, highlightcolor=GREY3)
		self.statsFrame.grid(row=2, column=1, sticky="nsew")

		Label(self.statsFrame, text="Medium Wait Time:", bg=GREY1, fg=WHITE1, font=("Helvetica", 14)).grid(row=0, column=0, padx=10, pady=10, sticky="w")
		self.mediumWaitTimeLabel = Label(self.statsFrame, text="0", bg=GREY1, fg=WHITE1, font=("Helvetica", 14))
		self.mediumWaitTimeLabel.grid(row=0, column=1, padx=10, pady=10, sticky="e")

		Label(self.statsFrame, text="Medium Turnaround Time:", bg=GREY1, fg=WHITE1, font=("Helvetica", 14)).grid(row=1, column=0, padx=10, pady=10, sticky="w")
		self.mediumTurnaroundTimeLabel = Label(self.statsFrame, text="0", bg=GREY1, fg=WHITE1, font=("Helvetica", 14))
		self.mediumTurnaroundTimeLabel.grid(row=1, column=1, padx=10, pady=10, sticky="e")

	def updateStatistics(self, w, t):
		self.mediumWaitTimeLabel.config(text=str(w))
		self.mediumTurnaroundTimeLabel.config(text=str(t))

	"""
		Functions
	"""
	def execute(self):
		self.root.mainloop()