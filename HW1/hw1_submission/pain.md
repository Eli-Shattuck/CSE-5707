We worked for roughly 2 or 3 hours at a time, over 4 session. And both did some work alone totaling to around 10 to 15 total hours of total pain.

The most pain came from 2 places: (1) the fact that this is just a hard delicate problem, and neither of us had worked on a problem like this before, and (2) trying to debug a problem where the inputs are so large it is not feasible to step through with the program manually.

There was also some difficulty in making our threaded version, in that it is only faster for some cases, and it is not entirely dependent on *n* when it is faster. Neither of us are actually sure exactly why it is slower in some cases.

Another source of difficulty is that it is hard to verify that a solution is optimal. When your program just spits out a huge number that's less than your maximum weight, it's hard to know if it did it's job correctly or not.

The last major issue we had was that we were never able to generate good test cases. This is partially because we never needed them because we had enough trouble with the hard cases provided by other students, but also because we were never able to really articulate what makes an instance particularly hard aside from *n*. We made a simple instance generator, but no matter how much we tried to play with the way we picked the weights and values, we couldn't find cases that were harder than just random.