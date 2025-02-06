import time as Time
from Job import Job
from Gui import Gui

class Scheduler:
	def __init__(self):
		self.readyQueue: list[Job] = []
		self.running: bool = False
		self.tick: int = 0
		self.chartInfo = []
		self.gui = Gui(self)

	def sleep(self, ms: int):
		Time.sleep(ms * .001)
		self.tick = self.tick + ms

	def sleepUntil(self, ms: int):
		self.sleep(ms - self.tick)

	def addJob(self, job: Job):
		self.readyQueue.append(job)
		self.gui.updateJobsList()

	def removeJob(self, job: Job):
		self.readyQueue.remove(job)
		self.gui.updateJobsList()

	# The following methods should be overrided by the child class
	def sortQueue(self):
		pass
	def execute(self):
		pass

if __name__ == "__main__":
	sch = Scheduler()
	sch.gui.execute()
	