from Scheduler import Scheduler
from Job import Job, State, JobInfo

class FCFS(Scheduler):
	def run(self):
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

		self.reset()

f = FCFS()
f.add_process(Job("P1", 0, 5, 1))
f.add_process(Job("P2", 1, 3, 2))
f.add_process(Job("P3", 2, 8, 3))
f.add_process(Job("P4", 3, 6, 4))
f.run()