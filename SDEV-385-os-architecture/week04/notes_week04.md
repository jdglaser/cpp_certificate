# Week 4 Notes - Threads

+ **Thread** - flow of control within a process
+ **Multithreaded process** - contains several different flow of control within same address space
  + **Benefits**:
    + Increased responsiveness to user
    + resource sharing within process
    + economy
    + scalability factors
    + more efficient use of multiple processing cores
+ **User-level threads** - threads visible to programmer - unknown to kernel
  + Faster to create nd manage than kernel threads - no intervention from kernel required
+ **Kernel-level threads** - operating-system kernel supports these threads
+ Three different types of models for kernel and user threads
  + **Many to one** - many user threads to one single kernel thread
  + **One-to-one** - each user thread matches to one kernel thread
  + **Many-to-many** - multiplexes many user threads to smaller or equal number of kernel threads
+ Three primary thread libraryies provide API for creating and managing threads:
  + **POSIX Pthreads**
  + **Windows Threads**
  + **Java Threadsd**
+ **Implicit threading** - creation and management of threading transferred to compilers and run-time libraries
  + Strategies include:
    + thread pools
    + OpenMP
    + Grand Central Dispatch
+ Some challenges for multithreaded programming
  + `fork()` and `exec()` system calls
  + signal handling
  + thread cancellation
  + thread-local storage
  + scheduler activations

