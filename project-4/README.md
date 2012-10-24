Project 3 du
============

Jon Warner
------------

I went all week thinking this was due Thursday, and being a master procrastinator, imagine my suprise. :) I did not have enough time to implement the elevator method, though I think I have it all logic'd out in my head. :)

Writeup
------------
The algorithms used are each different approaches to the same problem, each with their own pros and cons.

First Come First Serve:
This one is great if your "todo" list is small, it also happened to be the easiest to implement and was rather straight-forward.

Shortest Seek Time First:
This is a much more efficient approach as it minimizes travel time.  However, as the list grows the drive may never get to the extreme values causing "starvation" to those values.  This one was more fun to implement and the use of a vector made it really easy to sort through the values and get rid of ones already used.

Elevator:
This method addresses the starvation issue by picking the direction to the shortest destination, and sticking with it till the extreme, then bounding back to the other side.  Using a method similiar to what I did with finding shortest paths I planned on using sorting the vector and attacking it that way.  Best way? maybe not, not enough time to find out