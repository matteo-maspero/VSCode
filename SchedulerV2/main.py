from Scheduler import Scheduler
from Job import Job

scheduler = Scheduler()
scheduler.add_process(Job(1, "a", 10, 5, 0))
scheduler.add_process(Job(2, "b", 23, 23, 0))
scheduler.add_process(Job(3, "c", 43, 4, 0))
scheduler.add_process(Job(4, "d", 5, 3, 0))
scheduler.add_process(Job(5, "e", 43, 12, 0))
scheduler.run()