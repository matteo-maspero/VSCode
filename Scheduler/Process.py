STATES = {
	"new": ["ready"],
	"ready": ["running"],
	"running": ["ready", "waiting", "terminated"],
	"waiting": ["ready"],
	"terminated": []
}

class Process:
	def __init__(self, id: str, priority: int, burstTime: int):
		self.__id: str = id
		self.__priority: int = priority
		self.__burstTime: int = burstTime
		self.__arrivalTime: int = 0
		self.__state: str = "new"

	@property
	def id(self) -> str:
		return self.__id

	@property
	def priority(self) -> int:
		return self.__priority

	@property
	def burst_time_ms(self) -> int:
		return self.__burstTime

	@property
	def arrival_time(self) -> int:
		return self.__arrivalTime

	@property
	def state(self) -> str:
		return self.__state

	@state.setter
	def state(self, state: str):
		assert state in STATES[self.__state], f"Invalid state transition from '{self.__state}' to '{state}'"
		self.__state = state

	@burst_time_ms.setter
	def burst_time_ms(self, burstTime: int):
		assert burstTime < self.__burstTime, f"New burst time '{burstTime}' should not be greater than the current burst time '{self.__burstTime}'."
		self.__burstTime = burstTime