import time as Time

__NEXT_OF = {
	"new": ["ready"],
	"ready": ["running"],
	"running": ["waiting", "terminated"],
	"waiting": ["ready"],
	"terminated": []
}

class Job:
	def __init__(self, name: str, priority: int, arrival_ms: int, burst_ms: int):
		self.__name: str = name
		self.__priority: int = priority
		self.__arrival: int = arrival_ms
		self.__burst: int = burst_ms
		self.__state: str = "new"

	@property
	def name(self) -> str:
		return self.__name
	
	@property
	def priority(self) -> int:
		return self.__priority
	
	@property
	def arrival(self) -> int:
		return self.__arrival
	
	@property
	def burst_ms(self) -> int:
		return self.__burst
	
	@burst_ms.setter
	def burst_ms(self, newBurst: int):
		self.__burst = max(0, newBurst)
	
	@property
	def state(self) -> str:
		return self.__state

	@state.setter
	def state(self, newState: str):
		#assert newState in __NEXT_OF[self.__state], f"Invalid state transition from {self.__state} to {newState}."
		self.__state = newState