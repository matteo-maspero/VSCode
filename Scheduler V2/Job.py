from enum import Enum

"""
State enum:
	- new: str
	- ready: str
	- running: str
	- waiting: str
	- terminated: str
"""
class State(Enum):
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
	def __init__(self, name: str, arrival_ms: int, burst_ms: int, priority: int):
		self.name: str = name
		self.arrival: int = arrival_ms
		self.burst: int = burst_ms
		self.priority: int = priority
		self.state: State = State.new