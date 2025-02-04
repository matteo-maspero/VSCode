import tkinter as tk

class Gui:
	def __init__(self):
		self.__setupRoot__()
		self.__setupFrame__()
		self.__setupMenu__()

	def __setupRoot__(self):
		self.__root__ = tk.Tk()
		self.__root__.title("Scheduler")
		self.__root__.geometry("800x600")
		self.__root__.state('zoomed')

	def __setupFrame__(self):
		self.__frame__ = tk.Frame(master=self.__root__)
		self.__frame__.pack(fill=tk.BOTH, expand=True)

	def __setupMenu__(self):
		self.__menu__ = tk.Menu(master=self.__root__)
		self.__root__.config(menu=self.__menu__)

		self.__fileMenu__ = tk.Menu(master=self.__menu__, tearoff=False)
		self.__menu__.add_cascade(label="File", menu=self.__fileMenu__)

		self.__fileMenu__.add_command(label="Open")
		self.__fileMenu__.add_separator()
		self.__fileMenu__.add_command(label="Exit", command=self.__root__.quit)

	def run(self):
		# Running the main loop
		self.__root__.mainloop()

if __name__ == "__main__":
	gui = Gui()
	gui.run()