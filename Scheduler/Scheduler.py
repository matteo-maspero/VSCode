import time as Time
from Job import Job, State
from Gui import Gui

class Scheduler:
	def __init__(self):
		self.readyQueue: list[Job] = []
		self.running: bool = False
		self.tick: int = 0
		self.chartInfo = []
		self.gui = Gui(self)

	def sleep(self, ms: int):
		#Time.sleep(ms * .001)
		self.tick = self.tick + ms

	def sleepUntil(self, ms: int):
		self.sleep(ms - self.tick)

	def addJob(self, job: Job):
		self.readyQueue.append(job)
		self.gui.updateJobsList()

	def removeJob(self, job: Job):
		self.readyQueue.remove(job)
		self.gui.updateJobsList()

	def reset(self):
		self.readyQueue.clear()
		self.running = False
		self.tick = 0
		self.chartInfo.clear()
		self.gui.updateJobsList()
		self.gui.updateGanttChart()
		self.gui.updateStatistics(0, 0)

	# SJF
	def sortSJF(self):
		self.readyQueue.sort(key = lambda job: (job.burst, -job.priority))
		self.gui.updateJobsList()
	
	def executeSJF(self):
		if self.running:
			return
		
		self.tick = 0
		self.chartInfo.clear()
		self.sortSJF()
		jobs = self.readyQueue.copy()
		self.running = True

		while self.running:
			if not jobs:
				break

			if jobs[0].arrival > self.tick:
				self.sleepUntil(jobs[0].arrival)
				
			job: Job = jobs.pop(0)
			start: int = self.tick
			job.state = State.running
			self.sleep(job.burst)
			job.state = State.terminated
			self.chartInfo.append((job, start))
		self.running = False
		self.gui.updateGanttChart()
		self.updateTimes()

	# FCFS
	def sortFCFS(self):
		self.readyQueue.sort(key = lambda job: (job.arrival, -job.priority))
		self.gui.updateJobsList()

	def executeFCFS(self):
		if self.running:
			return
		
		self.tick = 0
		self.chartInfo.clear()
		self.sortFCFS()
		jobs = self.readyQueue.copy()
		self.running = True

		while self.running:
			if not jobs:
				break

			if jobs[0].arrival > self.tick:
				self.sleepUntil(jobs[0].arrival)
				
			job: Job = jobs.pop(0)
			start: int = self.tick
			job.state = State.running
			self.sleep(job.burst)
			job.state = State.terminated
			self.chartInfo.append((job, start))
		self.running = False
		self.gui.updateGanttChart()
		self.updateTimes()

	def updateTimes(self):
		total_turnaround = 0
		total_waiting = 0
		
		for info in self.chartInfo:
			waiting = info[1] - info[0].arrival
			turnaround = info[0].burst + waiting
			total_waiting += waiting
			total_turnaround += turnaround
		
		num_jobs = len(self.readyQueue)
		avg_turnaround = total_turnaround / num_jobs
		avg_waiting = total_waiting / num_jobs
		self.gui.updateStatistics(avg_waiting, avg_turnaround)

if __name__ == "__main__":
	sch = Scheduler()
	sch.gui.execute()
	