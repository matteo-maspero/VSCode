from enum import Enum


class Job:
	def __init__(self, name: str, arrival: int, burst: int, priority: int) -> None:
		self.name = name
		self.arrival = arrival
		self.burst = burst
		self.priority = priority
		self.state = State.NEW


class State(Enum):
	NEW = 1
	READY = 2
	RUNNING = 3
	WAITING = 4
	DEAD = 5
