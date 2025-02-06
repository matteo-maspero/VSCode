from Scheduler import Scheduler
from Job import Job, State
from JobInfo import JobInfo

class RR(Scheduler):
	def __init__(self, quantum: int):
		super().__init__()
		self.queue: list[Job] = []
		self.quantum: int = quantum

	def queue_waiting_jobs(self):
		while self.jobs[0].arrival <= self.time:
			job = self.jobs.pop(0)
			job.state = State.ready
			self.queue.append(job)

	def run(self):
		self.jobs = self.processes.copy()
		self.jobs.sort(key=lambda value: (value.arrival, value.priority))
		self.is_running = True

		while self.is_running:
			if not self.jobs and not self.queue:
				break

			if not self.queue:
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
				self.queue.append(job)

			self.queue.remove(job)
			self.chart_info.append(job_info)

		self.stop()

rr = RR(4)
rr.add_process(Job("A", 0, 10, 1))
rr.add_process(Job("B", 1, 10, 2))
rr.add_process(Job("C", 2, 10, 3))
rr.add_process(Job("D", 3, 10, 4))
rr.run()