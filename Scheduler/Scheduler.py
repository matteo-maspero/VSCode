import time as Time
from idlelib.debugobj_r import remote_object_tree_item

from Job import Job, State
from Gui import Gui

class Scheduler:
	def __init__(self):
		self.readyQueue: list[Job] = []
		self.jobs: list[Job] = []
		self.queue: list[Job] = []
		self.tick: int = 0
		self.chartInfo = []
		self.gui = Gui(self)
		self.quantum: int = 4

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
		self.tick = 0
		self.chartInfo.clear()
		self.sortSJF()
		jobs = self.readyQueue.copy()

		while jobs:
			if jobs[0].arrival > self.tick:
				self.sleepUntil(jobs[0].arrival)
				
			job: Job = jobs.pop(0)
			start: int = self.tick
			job.state = State.running
			self.sleep(job.burst)
			job.state = State.terminated
			self.chartInfo.append((job, start))
		self.gui.updateGanttChart()
		self.updateTimes()

	# FCFS
	def sortFCFS(self):
		self.readyQueue.sort(key = lambda job: (job.arrival, -job.priority))
		self.gui.updateJobsList()

	def executeFCFS(self):
		self.tick = 0
		self.chartInfo.clear()
		self.sortFCFS()
		jobs = self.readyQueue.copy()

		while jobs:
			if jobs[0].arrival > self.tick:
				self.sleepUntil(jobs[0].arrival)
				
			job: Job = jobs.pop(0)
			start: int = self.tick
			job.state = State.running
			self.sleep(job.burst)
			job.state = State.terminated
			self.chartInfo.append((job, start))
		self.gui.updateGanttChart()
		self.updateTimes()

	#RR
	def queue_waiting_jobs(self):
		while self.jobs and self.jobs[0].arrival <= self.tick:
			job = self.jobs.pop(0)
			job.state = State.ready
			self.queue.append(job)

	def run(self):
		if not self.readyQueue:
			return

		self.jobs = self.readyQueue.copy()
		self.jobs.sort(key=lambda value: (value.arrival, value.priority))

		while self.jobs or self.queue:
			if not self.queue and self.jobs[0].arrival > self.tick:
				self.sleepUntil(self.jobs[0].arrival)

			self.queue_waiting_jobs()
			job = self.queue[0]
			execution_time = min(self.quantum, job.burst)
			self.chartInfo.append((job, self.tick))
			job.state = State.running
			job.burst = max(0, job.burst - execution_time)

			self.sleep(execution_time)
			self.queue_waiting_jobs()

			if job.burst > 0:
				job.state = State.waiting
				self.queue.append(job)
				self.queue[0].state = State.ready
			else:
				job.state = State.terminated

			self.queue.remove(job)
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
		avg_turnaround = total_turnaround / num_jobs if num_jobs > 0 else 0
		avg_waiting = total_waiting / num_jobs if num_jobs > 0 else 0
		self.gui.updateStatistics(avg_waiting, avg_turnaround)

if __name__ == "__main__":
	sch = Scheduler()
	sch.gui.execute()
	