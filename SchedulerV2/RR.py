from Scheduler import Scheduler
from Job import Job, State, JobInfo

class RR(Scheduler):
	def __init__(self, quantum: int):
		super().__init__()
		self.queue: list[Job] = []
		self.quantum: int = quantum

	def queue_waiting_jobs(self):
		while self.jobs and self.jobs[0].arrival <= self.time:
			job = self.jobs.pop(0)
			job.state = State.ready
			self.queue.append(job)

	def run(self):
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
		for a in self.chart_info:
			print(a)
		self.stop()