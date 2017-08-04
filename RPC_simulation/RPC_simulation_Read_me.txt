This program is to simulate the implementation of RPC using tuple spaces. The idea here is to simulate not to implement at the system level, so basically I built a multithreaded application using multiple threads (n+1 threads), n threads are those thread that simulate the client RPC calls for the operation to be performed, and the one thread is a looping server that takes client calls, and write results to the tuple space.

Keeping mind of that in tuple spaces a ‘take’ operation will block if it can’t match the results. 

So, the client will place an operation, using the ‘write’ method of tuple spaces, to place a tuple that contains the operation id (unique), the operation itself, and the operation parameters. 
