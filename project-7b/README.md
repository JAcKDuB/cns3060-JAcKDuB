Project 7b Scheduling Simulation 
====================

Jon Warner
------------

It was interesting to come up with the algorithms of the different scheduling styles, and to see the effects on performance.  The project took longer than I would have liked and I ran across my first genuine
memory error with C++ in this project. Which took a while to iron out because they never error out anywhere near the source.  An out of bounds exception would have been nice. 

Given the sample data the Shortest Remaining Time Next (SRT) algorithm gave the best results by a comfortable margin. Round Robin (RR) and Shortest Job First (SJF) tied for second, but different sample data would have delivered different results.

- First Come First Serve (FCFS) had one of the longest times because it is inefficient to wait for the long processes while the little ones sit in line and wait.  It would definately show its weakness when a long string of
long processes came down the pipe. On the up side though, there would be no starvation.
- With 6 of the 10 processes jumping in to be finished immediately and scoring the lowest average turnaround time, SRT shined on this data set.  I could see SRT being a big offender with starvation, given the right data set however.
and we also didn't account for the time it takes to switch contexts so it would probably have performed a little closer to RR and SJF with those added.
- of course the RR times are as unrealistic as the SRT because of it's absence of context switches. Once you add those, it becomes the worst player on this team.  However this methodology is the best of both worlds.  It will
allow for the short processes to get finished quickly and make sure that longer processes don't starve.