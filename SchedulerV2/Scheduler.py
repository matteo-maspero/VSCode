from abc import abstractmethod
from Job import Job, JobInfo

class Scheduler:
	processes: list[Job] = []
	jobs: list[Job] = []
	chart_info: list[JobInfo] = []
	time: int = 0

	def __init__(self):
		# hooks to GUI methods
		self.update_processes_hook: callable = None
		self.update_chart_hook: callable = None

	def add_process(self, job: Job):
		self.processes.append(job)

		if self.update_processes_hook:
			self.update_processes_hook()

	def rem_process(self, job: Job):
		self.processes.remove(job)

		if self.update_processes_hook:
			self.update_processes_hook()

	def sleep(self, time_ms: int):
		self.time = self.time + time_ms

	def sleep_until(self, time: int):
		self.sleep(time - self.time)

	@abstractmethod
	def run(self):
		pass

	def reset(self):
		self.jobs = []
		self.chart_info = []
		self.time = 0

		if self.update_chart_hook:
			self.update_chart_hook()
