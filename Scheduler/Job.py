class Job:
	def __init__(self, jobId: str, priority: int, burstTime: int):
		self.jobId: str = jobId
		self.priority: int = priority
		self.burstTime: int = burstTime
		self.arrivalTime: int = 0
		self.state: str = "new"