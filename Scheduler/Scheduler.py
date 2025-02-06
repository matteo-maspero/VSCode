import time as Time
from Job import Job

class Scheduler:
	def __init__(self, quantum_ms: int):
		self.__jobs: list[Job] = []
		self.__queue: list[Job] = []
		self.__quantum: int = quantum_ms
		self.__tick: int = 0
		self.__running: bool = False
	
	@property
	def tick_ms(self) -> int:
		return self.__tick
	
	@property
	def quantum_ms(self) -> int:
		return self.__quantum
	
	def addJob(self, job: Job):
		self.__jobs.append(job)

	def __sortJobs(self):
		self.__jobs.sort(key = lambda job: (job.arrival, -job.priority))

	def __loadJobs(self):
		for job in self.__jobs:
			if job.state != "new":
				continue
			if job.arrival > self.__tick:
				continue
			job.state = "ready"
			self.__queue.append(job)

	def __sleep(self, ms: int):
		Time.sleep(ms / 1000)
		self.__tick = self.__tick + ms

	def run(self):
		self.__running = True
		self.__sortJobs()

		while self.__running:
			if len(self.__jobs) == 0 and len(self.__queue) == 0:
				self.__running = False
				break

			self.__loadJobs()

			if len(self.__queue) == 0:
				print(".")
				self.__sleep(1)
				continue

			job = self.__queue.pop(0)
			delta = min(self.__quantum, job.burst_ms)
			#job.state = "running"
			self.__sleep(delta)
			job.burst_ms = job.burst_ms - delta

			if job.burst_ms == 0:
				#job.state = "terminated"
				self.__jobs.remove(job)
			else:
				#job.state = "waiting"
				self.__queue.append(job)
				#self.__queue[0].state = "ready"

			print(job.name, delta)

a = Scheduler(4)
a.addJob(Job("A", 1, 2, 5))
a.addJob(Job("B", 1, 8, 9))
a.addJob(Job("C", 1, 13, 3))
a.addJob(Job("D", 1, 17, 6))
a.run()
pass