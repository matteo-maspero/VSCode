"""
STATES enum
	- NEW
	- READY
	- RUNNING
	- WAITING
	- TERMINATED
"""
class State:
	new = "new"
	ready = "ready"
	running = "running"
	waiting = "waiting"
	terminated = "terminated"

"""
Job class
	- name: str
	- priority: int
	- arrival: int
	- burst: int
	- state: int
"""
class Job:
	def __init__(self, name: str, priority: int, arrival_ms: int, burst_ms: int):
		self.name: str = name
		self.priority: int = priority
		self.arrival: int = arrival_ms
		self.burst: int = burst_ms
		self.state: str = State.new