from Scheduler import Scheduler
from Job import Job, State, JobInfo

class SJF(Scheduler):
    def __init__(self):
        super().__init__()

    def run(self):
        self.jobs = self.processes.copy()
        self.jobs.sort(key=lambda job: (job.burst, job.priority))
        self.is_running = True

        while self.is_running:
            if not self.jobs:
                break

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

        self.stop()
