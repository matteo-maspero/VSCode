class Job:
	def __init__(self, name, arrival, burst, priority):
		self.name = name
		self.arrival = arrival
		self.burst = burst
		self.priority = priority
		self.state = "ready"

class GanttData:
	def __init__(self, jobName, startTime, width):
		self.jobName = jobName
		self.startTime = startTime
		self.width = width

	def __str__(self):
		return f"{self.jobName} {self.startTime} {self.width}"

class RR:
	def __init__(self, quantum: int):
		self.processes: list[Job] = []
		self.jobs: list[Job] = []
		self.queue: list[Job]  = []
		self.chart: list[GanttData] = []
		self.quantum: int = quantum
		self.time: int = 0

	def addJob(self, newJob: Job):
		self.processes.append(newJob)

	def queueNextJob(self):
		for job in self.jobs:
			if job.arrival > self.time:
				break

			job.state = "ready"
			self.queue.append(job)
			self.jobs.remove(job)

	def run(self):
		self.jobs = self.processes.copy()
		self.jobs.sort(key = lambda job: (job.arrival, job.priority))

		while self.jobs or self.queue:
			if not self.queue:
				self.time = self.jobs[0].arrival
			
			self.queueNextJob()
			job = self.queue[0]
			delta = min(self.quantum, job.burst)
			job.burst = max(0, job.burst - delta)
			ganttData = GanttData(job.name, self.time, delta)
			self.time = self.time + delta
			self.queueNextJob()

			if job.burst > 0:
				self.queue.append(job)

			self.queue.remove(job)
			self.chart.append(ganttData)
