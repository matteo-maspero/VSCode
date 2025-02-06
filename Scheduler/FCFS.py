from Scheduler import Scheduler
from Job import Job, State

class FCFS(Scheduler):
	def sortReadyQueue(self):
		self.readyQueue.sort(key = lambda job: (job.arrival, -job.priority))
		self.gui.updateJobsList()
	
	def execute(self):
		self.sortReadyQueue()
		self.running = True

		while self.running:
			if not self.readyQueue:
				break

			if self.readyQueue[0].arrival > self.tick:
				self.sleepUntil(self.readyQueue[0].arrival)
				
			job: Job = self.readyQueue.pop(0)
			start: int = self.tick
			job.state = State.running
			self.sleep(job.burst)
			job.state = State.terminated
			self.chartInfo.append((job.name, start, self.tick))
