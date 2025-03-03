class Panel(ttk.PanedWindow):
	def __init__(self, master: App):
		super().__init__(master=master)

		self.setup()
		self.configure_grid()

	def setup(self):
		pass

	def configure_grid(self):
		self.columnconfigure(index=0, weight=1)
		self.rowconfigure(index=0, weight=1)


class JobInfo(Panel):
	def __init__(self, master: App):
		super().__init__(master=master)
		self.job_tree = JobTree(master=self)

		self.setup()
		self.add(self.job_tree, text="Job info")

	def setup(self):
		self.grid(row=0, column=0, sticky="nsew")

	def create_widgets(self):
		pass


class JobTree(ttk.Treeview):
	def __init__(self, master: JobInfo):
		super().__init__(master=master)
		self.scrollbar = Scrollbar(master=self)

		self.setup()
		self.configure_tree()

	def setup(self):
		self.configure(
			columns=("name", "arrival", "burst", "priority"),
			selectmode="extended",
			show="headings",
			yscrollcommand=self.scrollbar.set,
		)
		self.grid(row=0, column=0, sticky="nsew")

		a = [
			("P1", 0, 5, 1),
			("P2", 0, 3, 2),
			("P3", 0, 8, 3),
			("P4", 0, 6, 4),
			("P5", 0, 2, 5),
		]

		for i in a:
			self.insert("", "end", values=i)

	def configure_tree(self):
		self.column("name", width=140)
		self.column("arrival", width=100)
		self.column("burst", width=100)
		self.column("priority", width=100)
		self.heading("name", text="Job name", anchor="w")
		self.heading("arrival", text="Arrival ms", anchor="w")
		self.heading("burst", text="Burst ms", anchor="w")
		self.heading("priority", text="Priority", anchor="w")


class Scrollbar(ttk.Scrollbar):
	def __init__(self, master: JobTree):
		super().__init__(master=master, command=master.yview)

		self.setup()

	def setup(self):
		self.pack(side="right", fill="y")


class Shell(ttk.Frame):
	def __init__(self, master: JobInfo):
		super().__init__(master=master)

	def setup(self):
		self.grid(row=1, column=0, sticky="nsew")


class Button(ttk.Button):
	def __init__(self, master: Shell):
		super().__init__(master=master)

		self.setup()

	def setup(self):
		self.grid(row=0, column=0, sticky="nsew")
