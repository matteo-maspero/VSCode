import os
from enum import Enum

class State(Enum):
	Ready = ["Running"]
	Running = ["Waiting", "Terminated"]
	Waiting = ["Running"]
	Terminated = []

	def isSetValid(self, old : 'State', new : 'State') -> bool:
		return new.name in self[old.name]

class Process:
	__id : str
	__state : State
	__arrivalms : int
	__burstms : int
	__priority : int

	def __init__(self, id : str, arrivalms : int, burstms : int, priority : int):
		self.__id = id.strip().lower()
		self.__state = State.Ready
		self.__arrivalms = arrivalms
		self.__burstms = burstms
		self.__priority = priority

	def __str__(self) -> str:
		return f'{self.__id} {self.__state.name} {self.__arrivalms} {self.__burstms} {self.__priority}'
		
	def setState(self, newState : State):
		if not State.isSetValid(self.__state, newState):
			raise Exception(f'Invalid state transition from {self.__state} to {newState}')
		
		self.__state = newState

	def getId(self) -> str:
		return self.__id
	def getState(self) -> State:
		return self.__state
	def getArrival(self) -> int:
		return self.__arrivalms
	def getBurst(self) -> int:
		return self.__burstms
	def getPriority(self) -> int:
		return self.__priority

class Scheduler:
	__stack : list[Process]
	__tickms : int

	def __init__(self):
		self.__stack = []
		self.__tickms = 0

	def addProcess(self, id : str, arrivalms : int, burstms : int, priority : int):
		self.__stack.append( Process(id, arrivalms, burstms, priority) )
	
	def delProcess(self, id : str):
		for process in self.__stack:
			if process.getId() == id:
				self.__stack.remove(process)
				break

	def listProcesses(self):
		print('Stack dei processi: [id, state, arrivoms, burstms, priorita\']')

		for process in self.__stack:
			print(process)

		print()

class FCFS(Scheduler):
	pass

class CLI:
	__running : bool
	__buffer : str
	__key : str
	__args : tuple
	__scheduler : Scheduler
	__references : dict[callable]

	def __init__(self):
		self.__running = False
		self.__scheduler = Scheduler()

		self.__references = {
			'help' : self.__help,
			'?' : self.__help,
			'cls' : self.__clearConsole,
			'clear' : self.__clearConsole,
			'exit' : self.__exit,
			#	SCHEDULER COMMANDS
			'add' : self.__addProcess,
			'del' : self.__delProcess,
			'list' : self.__listProcesses
		}

	def run(self):
		self.__running = True

		while(self.__running):
			self.__input()
			self.__toCommandAndArgs()
			self.__execute()

	def __input(self):
		self.__buffer = input('> ')

	def __toCommandAndArgs(self):
		buffer = self.__buffer.strip().lower()
		self.__key, *self.__args = buffer.split(' ')

	def __execute(self):
		try:
			self.__references[self.__key]()
		except KeyError:
			print('Comando invalido. Digitare "help" o "?" per visualizzare la lista dei comandi supportati.\n')
		except Exception as message:
			raise Exception(message)
	
	#	BASE COMMANDS DEF
	
	def __help(self):
		print(
			'Lista dei comandi disponibili:\n'
			'"help" "?"\tMostra una lista dei comandi.\n'
			'"cls" "clear"\tPulisce la console.\n'
			'"exit"\t\tEsci dal programma.\n'
			'"add"\t\tAggiungi un processo.\tadd <id : str> <arrivalms : int> <burstms : int> <priority : int>\n'
			'"del"\t\tRimuovi un processo.\tdel <id : str>\n'
			'"list"\t\tMostra i processi in coda.\n'
		)

	def __clearConsole(self):
		os.system('cls' if os.name == 'nt' else 'clear')

	def __exit(self):
		self.__running = False

	#	SCHEDULER COMMANDS DEF

	def __addProcess(self):
		if(len(self.__args) != 4):
			print('Numero di argomenti non valido.\n')
			return
		
		self.__scheduler.addProcess(*self.__args)

	def __delProcess(self):
		if len(self.__args) != 1:
			print('Numero di argomenti non valido.\n')
			return
		
		self.__scheduler.delProcess(self.__args[0])

	def __listProcesses(self):
		self.__scheduler.listProcesses()

def main():
	myCLI = CLI()
	myCLI.run()

if __name__ == '__main__':
	main()