from Job import Job, State, JobInfo
from GUI import GUI

class Scheduler:
	def __init__(self):
		self.processes: list[Job] = []
		self.jobs: list[Job] = []
		self.queue: list[Job] = []
		self.chart_info: list[JobInfo] = []
		self.quantum: int = 0
		self.time: int = 0
		self.gui: GUI = GUI()

	def run(self):
		self.gui.root.mainloop()

	def sleep(self, time_ms: int):
		self.time = self.time + time_ms

	def sleep_until(self, time: int):
		self.sleep(time - self.time)

	def set_quantum(self, quantum: int):
		if quantum < 1:
			raise ValueError("Quantum must be greater than 0")
		
		self.quantum = quantum

	def add_process(self, job: Job):
		self.processes.append(job)
		self.gui.update_list(self.processes)

	def rem_process(self, job: Job):
		self.processes.remove(job)
		self.gui.update_list(self.processes)

	def clear(self):
		self.jobs = []
		self.chart_info = []
		self.time = 0

	def queue_waiting_jobs(self):
		while self.jobs and self.jobs[0].arrival <= self.time:
			job = self.jobs.pop(0)
			job.state = State.ready
			self.queue.append(job)

	def FCFS(self):
		self.jobs = self.processes.copy()
		self.jobs.sort(key=lambda job: (job.arrival, job.priority))

		while self.jobs:
			if self.jobs[0].arrival > self.time:
				self.sleep_until(self.jobs[0].arrival)

			job: Job = self.jobs.pop(0)
			execution_time: int = job.burst
			job_info: JobInfo = JobInfo(job.name, self.time, execution_time)

			job.state = State.running
			job.burst = max(0, job.burst - execution_time)
			self.sleep(execution_time)

			job.state = State.terminated
			self.chart_info.append(job_info)
		self.clear()

	def SJF(self):
		self.jobs = self.processes.copy()
		self.jobs.sort(key=lambda job: (job.burst, job.priority))

		while self.jobs:
			if self.jobs[0].arrival > self.time:
				self.sleep_until(self.jobs[0].arrival)

			job: Job = self.jobs.pop(0)
			execution_time: int = job.burst
			job_info: JobInfo = JobInfo(job.name, self.time, execution_time)

			job.state = State.running
			job.burst = max(0, job.burst - execution_time)
			self.sleep(execution_time)

			job.state = State.terminated
			self.chart_info.append(job_info)
		self.clear()

	def RR(self):
		self.jobs = self.processes.copy()
		self.jobs.sort(key=lambda value: (value.arrival, value.priority))

		while self.jobs or self.queue:
			if not self.queue and self.jobs[0].arrival > self.time:
				self.sleep_until(self.jobs[0].arrival)

			self.queue_waiting_jobs()
			job = self.queue[0]
			execution_time = min(self.quantum, job.burst)
			job_info = JobInfo(job.name, self.time, execution_time)
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
			self.chart_info.append(job_info)
		self.clear()