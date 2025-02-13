from Scheduler import Scheduler
import Job

scheduler = Scheduler()

scheduler.add_process(Job.Job("a", 10, 5, 0))
scheduler.add_process(Job.Job("b", 23, 23, 0))
scheduler.add_process(Job.Job("c", 43, 4, 0))
scheduler.add_process(Job.Job("d", 5, 3, 0))
scheduler.add_process(Job.Job("e", 43, 12, 0))

scheduler.run()
