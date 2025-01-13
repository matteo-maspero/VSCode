import os

class Process:
	pass

class Scheduler:
	pass

class CLI:
	__running : bool
	__currentPath : str
	__inputBuffer : str
	__cmd : str
	__args : tuple[str]

	__scheduler : Scheduler

	__commandsRefs : dict[str, callable]

	def __init__(self):
		self.__running = True
		self.__currentPath = 'C:\\'

		self.__scheduler = Scheduler()

		self.__commandsRefs = {
			'cd' : self.__changeDirectory,
			'cd..' : self.__changeDirectoryUp,
			'mkdir' : self.__makeDirectory,
			'rmdir' : self.__removeDirectory,
		}

	def run(self):
		while self.__running:
			self.__getInput()
			self.__formatInput()
			self.__parseInput()


	def __getInput(self):
		self.__inputBuffer = input(self.__currentPath + ' > ')

	def __formatInput(self):
		self.__inputBuffer = self.__inputBuffer.strip().lower()

	def __parseInput(self):
		self.__cmd, *self.__args = self.__inputBuffer.split()

		try:
			self.__commandsRefs[self.__cmd]()
		except:
			print('Invalid command, type "help" for a list of commands.\n')

	def __changeDirectory(self):
		if not self.__args:
			print('No arguments parsed.\n')
			return
		
		if self.__args[0] == '..':
			self.__changeDirectoryUp()
			return
		
		self.__currentPath = self.__currentPath + self.__args[0] + '\\'

	def __changeDirectoryUp(self):
		self.__currentPath = self.__currentPath.rsplit('\\', 2)[0] + '\\'

	def __makeDirectory(self):
		if not self.__args:
			print('No arguments parsed.\n')
			return

		if not isinstance(self.__args[0], str):
			print('Argument must be a string.\n')
			return

		directoryPath = self.__currentPath + self.__args[0] + '\\'
		
		try:
			os.mkdir(directoryPath)
			print('Directory created successfully.\n')
		except FileExistsError:
			print('Directory already exists.\n')
		except:
			print('Failed to create directory.\n')

	def __removeDirectory(self):
		pass

	def main():
		myCLI = CLI()
		myCLI.run()

	if __name__ == '__main__':
		main()

	def __removeDirectory(self):
		pass

def main():
	myCLI = CLI()
	myCLI.run()

if __name__ == '__main__':
	main()