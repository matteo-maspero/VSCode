import os

class Command:
	def __init__(self, desc : str, name : str):
		self.__desc = desc
		self.__name = name

	def __call__(self, *args):
		globals().get(self.__name)(*args)

	def getDesc(self):
		return self.__desc

COMMANDS = {
	('clear', 'cls') : Command('Clears the console.', '__close'),
	('exit') : Command('Exits the program.', '__exit'),
	('help', '?') : Command('Displays a list of commands.', '__help'),
}

def __close():
	if os.name == 'nt':
		os.system('cls')
	else:
		os.system('clear')

def __exit():
	confirm = input('Are you sure you want to exit? (y/n) ').lower()

	if confirm == 'y':
		exit()
	elif confirm == 'n':
		return

def __help(requested : str = None):
	if requested:
		for aliases, command in COMMANDS.items():
			if requested in aliases:
				print(f'{aliases}\t{command.getDesc()}')
				return
		print('Command not found. Type "help" or "?" for a list of commands')
		return
	
	for aliases, command in COMMANDS.items():
		print(f'{aliases}\t{command.getDesc()}')
	print('Type "help" or "?" followed by a command for more information.')

class CLI:
	def __init__(self):
		self.__running = False
		self.__buffer : str
		self.__command : str
		self.__args : tuple

	def run(self):
		self.__running = True

		while self.__running:
			self.__inputBuffer()
			self.__parseBuffer()
			self.__executeCommand()

	def __inputBuffer(self):
		self.__buffer = input('> ')

	def __parseBuffer(self):
		self.__buffer = self.__buffer.strip().lower()
		self.__command, *self.__args = self.__buffer.split(' ')

	def __executeCommand(self):
		try:
			for aliases, command in COMMANDS.items():
				if self.__command in aliases:
					command(*self.__args)
					return
			print('Invalid input. Type "help" or "?" for a list of commands.')
		except TypeError:
			print('Invalid arguments. Type "help" or "?" for a list of commands.')

cli = CLI()
cli.run()