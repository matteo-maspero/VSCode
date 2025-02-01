from os import system as execute

class CLI:
	def __init__(self):
		self.__running = False
		self.__buffer : str
		
		self.__commands = {
			'clear' : [self.clear, 'Clears the console from previous content.'],
			'exit' : [self.exit, 'Kills the CLI process.'],
			'help' : [self.help, 'Provides information about the supported commands.'],
		}

	def run(self):
		self.__running = True

		while self.__running:
			self.__input()
			self.__execute()
	
	def __input(self):
		self.__buffer = input('> ')

	def __execute(self):
		#	Parse the buffer into a command with possible arguments.
		command = self.__buffer.strip().lower()
		command, *arguments = command.split(' ')

		try:
			#	Tries executing the command with the given arguments.
			self.__commands[command][0](*arguments)
		except KeyError:
			#	Handles the case where the command is not supported.
			print('Invalid command. Type "help" for a list of supported commands.')
		except TypeError:
			#	Handles the case where the command is supported but the arguments are invalid
			print('Invalid arguments passed to command.')
		except Exception:
			#	Handles the case where the command failed to execute.
			raise Exception
	
	def clear(self):
		execute('cls')

	def exit(self):
		self.__running = False

	def help(self):
		for command, [_, description] in self.__commands.items():
			#	Prints the formatted command (fixed length of 16) and its description.
			print(f'{command : <16}{description}')