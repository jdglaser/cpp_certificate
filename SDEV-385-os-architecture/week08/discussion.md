# Discussion Post

*The term ‘page fault’ (page in and page out) seems to indicate that an error occurred, when in fact, that may not be the case. Discuss the page fault handling mechanism in Linux (you may have to do some research outside of the book and lecture). Are there times when a page fault really indicates an error? If so, give a detailed example. Are there times when a page fault does not indicate an error? If so, give a detailed example.*

Virtual memory in Linux is a powerful tool for providing more space in main memory (RAM).  With virtual memory, the space on disk is used as an extension of the RAM. Reading and writing to the disk is slower, so only items that aren't being used are transferred to virtual memory.  When the original content in virtual memory is needed again, it is loaded back into main memory.  Modern Linux operating systems use a method called paging to load fixed size parts - usually kilobytes in size - at a time called pages into physical memory.

Virtualization allows us to load programs into memory that are larger than the actual physical memory. When we use virtual memory, a memory amangement unit (MMU) maps virtual memory to actual physical memory. The diagram below shows an example of this:

Oftentimes systems use a method of demand paging where pages are loaded from virtual memory into real memory as they are needed, swapping out pages that are not needed. One important thing to note about this method is that during execution of a program, memory may be needed again from a page that was already swapped out. This causes a page fault to occur, which transfers control back to the operating system, and then loads the page back into memory. In this case a page fault is not necessarily an error, but is a normal part of program exectuion when virtual memory is involved.  The below graphic shows this process in action:

An actual error with page faults may occur when the system starts thrashing. Thrashing occurs when pages are swapped out to make room for pages that need to be swapped in, but the pages that were swapped out are also immediately needed again. This back and forth of swapping out causes the system to spend too much time handling page faults.

**References**

https://www.geeksforgeeks.org/virtual-memory-in-operating-system/

https://tldp.org/LDP/sag/html/vm-intro.html#:~:text=Linux%20supports%20virtual%20memory%2C%20that,be%20used%20for%20another%20purpose.

https://www.tutorialspoint.com/operating_system/os_virtual_memory.htm