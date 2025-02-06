from abc import abstractmethod
from time import sleep
from Job import Job
from JobInfo import JobInfo

class Scheduler:
	def __init__(self):
		self.processes: list[Job] = []
		self.jobs: list[Job] = []
		self.chart_info: list[JobInfo] = []
		self.time: int = 0
		self.is_running: bool = False
		self.is_real_time: bool = False

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
		if self.is_real_time:
			sleep(time_ms / 1000)
		self.time = self.time + time_ms

	def sleep_until(self, time: int):
		self.sleep(time - self.time)

	@abstractmethod
	def run(self):
		pass

	def stop(self):
		self.jobs = []
		self.chart_info = []
		self.time = 0
		self.update_chart_hook()
