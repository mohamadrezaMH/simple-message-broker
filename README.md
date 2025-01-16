Overview of How Shared Memory Works  
Shared memory is one of the common methods for interprocess communication (IPC) to share data between processes. In this method, a portion of memory is shared among processes, allowing for the transfer of information between them.

The working of shared memory is as follows: a process creates a shared memory region and then grants access to this memory to other processes. The processes can read or write data, and any changes made by one process are visible to the other processes as well.

Using shared memory can optimize system and application performance, as data is transferred between processes at high speed without the need for copying. However, security issues may arise, as synchronization and coordination between processes require precise and controlled management.

Overview of fork() and Its Features  
The fork() function is a system call available in Unix-like operating systems. When the fork() function is called, a new process is created, which is an exact copy of the calling process.

Some features of fork() include:  
1. Creating an Exact Copy of the Parent Process: The child process created by fork() inherits all the resources and states of the parent process, including memory, variables, signals, and files.  
2. Different PID: The child process has its own automatically assigned Process ID (PID).  
3. Execution Order: The child process may start executing either after the parent process or concurrently, depending on the operating system.  
4. Independent Output: Each process has its own independent output.  
5. Resource Sharing: Once the parent and child processes are separated, shared resources, such as shared folders, are no longer shared between them.

Using fork() is highly useful for creating child processes and parallel processing in concurrent programming. It allows for the execution of different parts of a program in parallel, ensuring coordination and cooperation between processes.
