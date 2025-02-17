from enum import Enum


class Job:
	"""

	"""
	def __init__(self, name: str, arrival: int, burst: int, priority: int) -> None:
		self.name: str = name
		self.arrival: int = arrival
		self.burst: int = burst
		self.priority: int = priority
		self.state: State = State.new


class State(Enum):
	"""
	This enumeration defines all the valid states that a job can be in
	during its lifecycle. It provides a clear and standardized way to
	manage and categorize process states.
	:ivar new: Indicates that the process or task is newly
	created and has not yet started.
	:ivar ready: Indicates that the process or task is ready
	to run but is not yet executing.
	:ivar running: Indicates that the process or task is
	currently being executed.
	:ivar waiting: Indicates that the process or task is
	waiting for a specific event or resource.
	:ivar terminated: Indicates that the process or task
	has completed execution or has been stopped.
	"""
	new = "new"
	ready = "ready"
	running = "running"
	waiting = "waiting"
	terminated = "terminated"
