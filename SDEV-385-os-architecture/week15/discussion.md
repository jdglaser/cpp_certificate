# Week 15 Discussion - Flash Driver Operating System

*This week you will take the knowledge that you gained in the course and, as a team, design a minimal operating system that can be run from a flash drive. What functionality will it need? What will the kernel be like? How will you architect the system?*

Designing even a minimal operating system is a huge undertaking. However, conceptually, we can break up the task at hand into categories that make it easier to think about what would need to be completed, and in what order, for our minimal flash drive operating system to work.

One thing we may want to think about first is what language(s) we will use to design our operating system. Obviously many of the very low level system level calls may need to be created using a little bit of assembly language. However, for programming the remainder of ours sytem, we aren't actually stuck in just C for programming an OS. We can use some newer languages as well. For example, the lower level operating system functionality, kernel, and algorithms can be designed using Rust. Rust is a newer open source programming language created by the folks at Mozilla. It has a lot of potential in lower-level programming and promises better memory safety and useability than C. There is actually a guide online for how we might design an OS in Rust, which can be found [here](https://os.phil-opp.com/). For the higher level scripting tasks, we could use a language like Python.

Once we decide what languages we will use (e.g. some assembly, Rust, and Python), then we can begin work on deciding what categories we design first. We can use our textbook from the course to think about these tasks:

- **Process Management**
  - Handling processes - scheduling processes, interprocess communication
  - Threads - multi-threaded programming, multi-core programming, multi-programming algorithms 
  - Process synchronization - algorithm design for handling multi-process synchronization
  - CPU Scheduling - algorithm design for how to schedule processes, special care for multi-process and multi-threaded scheduling
- **Memory Management**
  - Main memory (RAM) - handle memory swapping algorithms, handle paging algorithms, handle segmentation algorithms, create a page table data structure
  - Virtual Memory - algorithm design for virtual memory management (demand paging?)
- **Storage Management**
  - Mass-Storage Structure - design how the disk will be structured and disk scheduling algorithms, design swap space
  - File-system intergface - create "file" data structure, handle access methods, handle file sharing
  - Directory implementation - design data structure for directory file type
  - Recovery - how complex should this be in a simple flash drive OS? Do we need it at all?
  - I/O System - What I/O hardware will we support? Create an application I/O interface, create a Kernel I/O subsystem
- **Security and Protection Management**
  - Implement Access Controls - this can probably be pretty basic in our OS
  - Create a User implementation
  - Handle user authentication

Given the above categories, we can break down the problem at hand. Even still, this OS would take a long time with a lot of collaberation to actually complete.

**References**

Operating System Concepts Essentials, 2nd Edition, Silberschatz, Galvin, Gagne, Wiley Press.

(2020). Rust Language. https://research.mozilla.org/rust/.

(2020). Writing an OS in Rust. Retrieved form https://os.phil-opp.com/.
