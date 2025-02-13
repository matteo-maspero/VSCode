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
	def __init__(self, job_id: int, name: str, arrival_ms: int, burst_ms: int, priority: int):
		self.id: int = job_id
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
	def __init__(self, job_id, name, start_ms, width_ms):
		self.id = job_id
		self.name = name
		self.start = start_ms
		self.width = width_ms

	def __str__(self) -> str:
		return f"{self.name}: from {self.start}ms to {self.start + self.width}ms. ({self.width}ms)"

	def get_xrange(self) -> list[tuple[int, int]]:
		return [(self.start, self.width)]