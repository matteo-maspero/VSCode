from Job import Job

class Scheduler:
	def __init__(self):
		self.jobs: list[Job] = []

	def addJob(self, job):
		self.jobs.append(job)

	def printJobs(self):
		for job in self.jobs:
			print(job)

if __name__ == '__main__':
	scheduler = Scheduler()
	scheduler.addJob(
		Job('test', 5, 10)
	)
	scheduler.addJob(
		Job('test2', 5, 10)
	)
	scheduler.addJob(
		Job('test3', 5, 10)
	)
	scheduler.printJobs()