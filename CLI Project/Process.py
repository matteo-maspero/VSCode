class Process:
	def __init__(self, name : str, state : str, arrival : int, burst : int, priority : int):
		self.name = name
		self.state = state
		self.arrival = arrival
		self.burst = burst
		self.priority = priority