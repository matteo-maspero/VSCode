l = {
	('help', '?') : 'Displays a list of commands.',
	('exit', 'quit') : 'Exits the program.'
}

for k, v in l.items():
	print(f'{k[0]}: {v}')