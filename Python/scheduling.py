import os
from threading import Thread
from enum import Enum

class State(Enum):
	Ready = 0
	Running = 1
	Waiting = 2
	Terminated = 3

class Process:
	__id : str
	__priority : int
	__state : State
	__arrivalTime_ms : int
	__burstTime_ms : int

	def __init__(self, id : str, arrivalTime_ms : int, burstTime_ms : int, priority : int):
		self.__id = id
		self.__priority = priority
		self.__state = State.Ready
		self.__arrivalTime_ms = arrivalTime_ms
		self.__burstTime_ms = burstTime_ms

	def getID(self) -> str:
		return self.__id
	
	def getPriority(self) -> int:
		return self.__priority
	
	def getState(self) -> State:
		return self.__state
	
	def getArrivalTime(self) -> int:
		return self.__arrivalTime_ms
	
	def getBurstTime(self) -> int:
		return self.__burstTime_ms

	def changeState(self, state : State):
		self.__state = state

	def decreaseBurstTime(self):
		self.__burstTime_ms = self.__burstTime_ms - 1

class CLI:
	__running : bool
	__buffer : str
	__cmd : str
	__args : tuple[str]
	__processes : list[Process]
	__commandsRefs : dict[str, callable]

	def __init__(self):
		self.__running = False
		self.__buffer = ''
		self.__cmd = ''
		self.__args = ()
		self.__processes = []

		self.__commandsRefs = {
			'cd' : self.__changeDirectory,
			'cd..' : self.__changeDirectoryUp,
			'mkdir' : self.__makeDirectory,
			'rmdir' : self.__removeDirectory,
			'cls' : self.__clearConsole,
			'clear' : self.__clearConsole,
			'help' : self.__help,
			'?' : self.__help,
			'exit' : self.__exit,

			#COMANDI PROCESSI
			'mkprc' : self.__appendProcess,
			'rmprc' : self.__deleteProcess,
			'listprc' : self.__listProcesses,
			'fcfs' : self.__FCFS,
		}

	def run(self):
		self.__running = True

		while self.__running:
			self.__getInput()
			self.__formatInput()
			self.__parseInput()


	def __getInput(self):
		self.__buffer = input(os.getcwd() + ' > ')

	def __formatInput(self):
		self.__buffer = self.__buffer.strip().lower()

	def __parseInput(self):
		self.__cmd, *self.__args = self.__buffer.split()

		try:
			self.__commandsRefs[self.__cmd]()
		except:
			print('Invalid command, type "help" for a list of commands.\n')

	def __changeDirectory(self):
		if not self.__args:
			print('Command expects 1 argument. None are given.\n')
			return
		
		if self.__args[0] == '..':
			self.__changeDirectoryUp()
			return
		
		try:
			os.chdir(self.__args[0])
		except FileNotFoundError:
			print('Directory does not exist.\n')
		except:
			print('Failed to change directory.\n')

	def __changeDirectoryUp(self):
		try:
			os.chdir('..')
		except:
			print('Failed to change directory.\n')

	def __makeDirectory(self):
		if not self.__args:
			print('Command expects 1 argument. None are given.\n')
			return

		try:
			os.mkdir(self.__args[0])
			print('Directory created successfully.\n')
		except FileExistsError:
			print('Directory already exists.\n')
		except:
			print('Failed to create directory.\n')

	def __removeDirectory(self):
		if not self.__args:
			print('Command expects 1 argument. None are given.\n')
			return
		
		try:
			os.rmdir(self.__args[0])
			print('Directory removed successfully.\n')
		except FileNotFoundError:
			print('Directory does not exist.\n')
		except:
			print('Failed to remove directory.\n')

	def __clearConsole(self):
		os.system('cls' if os.name == 'nt' else 'clear')

	def __exit(self):
		self.__running = False

	def __help(self):
		print(
			'\tcd <directory> - Change directory.\n'
			'\tcd.. - Change directory up.\n'
			'\tcd.. - Change directory up.\n'
			'\tmkdir <directory> - Create directory.\n'
			'\trmdir <directory> - Remove directory.\n'
			'\tcls - Clear console.\n'
			'\tclear - Clear console.\n'
			'\thelp - Display this message.\n'
			'\t? - Display this message.\n'
			'\texit - Exit the program.\n'

			#COMANDI PROCESSI
			'\tmkprc <id> <arrivalTime> <burstTime> <priority> - Create a process.\n'
			'\trmprc <id> - Remove a process.\n'
			'\tlistprc - List all processes.\n'

			#COMANDI SCHEDULER
			'\tfcfs - First Come First Serve scheduling.\n'
		)

	#COMANDI PROCESSI
	def __appendProcess(self):
		try:
			for process in self.__processes:
				if process.getID() == self.__args[0]:
					print('Failed to create process.\n')
					return
					
			self.__processes.append(Process(*self.__args))
		except:
			print('Failed to create process.\n')

	def __deleteProcess(self):
		try:
			for process in self.__processes:
				if process.getID() == self.__args[0]:
					self.__processes.remove(process)
					break
		except:
			print('Failed to remove process.\n')

	def __listProcesses(self):
		for process in self.__processes:
			print(
				f'ID: {process.getID()}\n'
				f'Priority: {process.getPriority()}\n'
				f'State: {process.getState().name}\n'
				f'Arrival Time: {process.getArrivalTime()}\n'
				f'Burst Time: {process.getBurstTime()}\n'
			)

	#COMANDI SCHEDULER
	def __FCFS(self):
		self.__processes.sort(key = lambda x: x.getArrivalTime())
		self.__processes.sort(key = lambda x: x.getPriority())

		for process in self.__processes:
			process.changeState(State.Running)
			baseBurst = process.getBurstTime()

			while(process.getBurstTime() > 0):
				print(
					f'\tProcess {process.getID()} is running.\n'
					f'\tProgress: [{'#' * process.getBurstTime / baseBurst * 10}]\n'
				)

				process.decreaseBurstTime()

			process.changeState(State.Terminated)

def main():
	myCLI = CLI()
	myCLI.run()

if __name__ == '__main__':
	main()