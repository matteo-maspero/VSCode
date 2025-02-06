class JobInfo:
	def __init__(self, name, start_ms, width_ms):
		self.name = name
		self.start_ms = start_ms
		self.width_ms = width_ms

	def __str__(self) -> str:
		return f"{self.name}: from {self.start_ms} to {self.width_ms}"

	def get_xrange(self) -> list[tuple[int, int]]:
		return [(self.start_ms, self.width_ms)]
