import tkinter as tk
from tkinter import ttk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import threading
import time

# Create the main application window
root = tk.Tk()
root.geometry("800x600")  # Set window size
root.state('zoomed')
root.title("Modern Scheduler GUI")

# Apply a modern theme
style = ttk.Style()
style.theme_use('clam')  # You can try 'clam', 'alt', 'default', or 'classic'

# Create a frame to hold the columns
frame = ttk.Frame(root, padding="10")
frame.pack(fill=tk.BOTH, expand=True)

# Configure the grid layout with 2 columns
frame.columnconfigure(0, weight=1)
frame.columnconfigure(1, weight=3)

# Create widgets for each column
left_column = ttk.Frame(frame, relief=tk.SUNKEN, padding="10")
left_column.grid(row=0, column=0, sticky="nsew", padx=5, pady=5)

right_column = ttk.Frame(frame, relief=tk.SUNKEN, padding="10")
right_column.grid(row=0, column=1, sticky="nsew", padx=5, pady=5)

# Add a label to the left column
ttk.Label(left_column, text="Left Column", font=("Helvetica", 16)).pack(pady=10)

# Add a Listbox to the left column to show processes
process_listbox = tk.Listbox(left_column, font=("Helvetica", 14))
process_listbox.pack(fill=tk.BOTH, expand=True, pady=10)

# Add some sample processes to the Listbox
processes = ["Process 1", "Process 2", "Process 3"]
for process in processes:
	process_listbox.insert(tk.END, process)

# Add a label to the right column
ttk.Label(right_column, text="Right Column", font=("Helvetica", 16)).pack(pady=10)

# Create a menu bar
menu_bar = tk.Menu(root)
root.config(menu=menu_bar)

# Create a File menu
file_menu = tk.Menu(menu_bar, tearoff=0)
menu_bar.add_cascade(label="File", menu=file_menu)
file_menu.add_command(label="New")
file_menu.add_command(label="Open")
file_menu.add_command(label="Save")
file_menu.add_separator()
file_menu.add_command(label="Exit", command=root.quit)

# Create an Edit menu
edit_menu = tk.Menu(menu_bar, tearoff=0)
menu_bar.add_cascade(label="Edit", menu=edit_menu)
edit_menu.add_command(label="Undo")
edit_menu.add_command(label="Redo")
edit_menu.add_separator()
edit_menu.add_command(label="Cut")
edit_menu.add_command(label="Copy")
edit_menu.add_command(label="Paste")
# Sample data for FCFS scheduling
processes = ['P1', 'P2', 'P3']
arrival_times = [0, 2, 4]
burst_times = [5, 3, 56]
quantum_time = 3

# Create a figure for the graph
fig, ax = plt.subplots(figsize=(6, 4))

# Function to update the graph in real-time
def update_graph():
	current_time = 0
	remaining_burst_times = burst_times[:]
	process_queue = []
	while any(remaining_burst_times):
		for i in range(len(processes)):
			if arrival_times[i] <= current_time and remaining_burst_times[i] > 0 and i not in process_queue:
				process_queue.append(i)
		
		if process_queue:
			current_process = process_queue.pop(0)
			start_time = current_time
			execution_time = min(quantum_time, remaining_burst_times[current_process])
			remaining_burst_times[current_process] -= execution_time
			current_time += execution_time
			
			# Clear the previous plot
			ax.clear()

			# Plot the processes
			for j in range(len(processes)):
				if remaining_burst_times[j] < burst_times[j]:
					ax.broken_barh([(arrival_times[j], burst_times[j] - remaining_burst_times[j])], (j - 0.4, 0.8), facecolors=('tab:blue'))

			# Set labels and title
			ax.set_yticks(range(len(processes)))
			ax.set_yticklabels(processes)
			ax.set_xlabel('Time')
			ax.set_title('Round Robin Scheduling')

			# Draw the updated plot
			canvas.draw()

			# Simulate real-time by sleeping
			time.sleep(1)
		else:
			current_time += 1

# Add the plot to the right column
canvas = FigureCanvasTkAgg(fig, master=right_column)
canvas.draw()
canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)

# Start the thread to update the graph
thread = threading.Thread(target=update_graph)
thread.start()

root.mainloop()