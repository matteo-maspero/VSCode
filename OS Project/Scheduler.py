from CLI import CLI

class Scheduler(CLI):
	def __init__(self):
		super().__init__()
		__processes = []
		__queue = []
		__clock_ms = 0
		__quantum_ms = 0