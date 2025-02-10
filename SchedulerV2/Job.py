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

"""
JobInfo class
	- name: str
	- start_ms: int
	- width_ms: int
"""
class JobInfo:
	def __init__(self, name, start_ms, width_ms):
		self.name = name
		self.start_ms = start_ms
		self.width_ms = width_ms

	def __str__(self) -> str:
		return f"{self.name}: from {self.start_ms}ms to {self.start_ms + self.width_ms}ms. ({self.width_ms}ms)"

	def get_xrange(self) -> list[tuple[int, int]]:
		return [(self.start_ms, self.width_ms)]