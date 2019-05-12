# 1. Overview:


The simulation programmed in this repository was the first bigger program that I created. Everything was done using Visual Studio.  It covers material from object oriented programming, boost library and general knowledge about algorithms.
The outlook of system is that there is process generator, 3 CPUs, 4 I/O devices, a random queue to CPU and 4 FIFO queues to I/Os.

Processes are generated with certain times. Time after process will be executed in CPU, time after there will be I/O device call, time in which process will be held in I/O device.
Basic idea is that process will go from random queue to first available CPU and wants to be executed by it, but gets interrupted by I/O calls. The time that the process has been in CPU is subtracted from time drawn at the process born(generation). Then process go to I/O queue or straight to I/O if it&#39;s empty. It stays here for certain amount of time and it go again to CPU queue. Process is deleted when execution time drawn at the beginning is equal to sum of partial executions.


# 2. Project task:


The process scheduling (also called as CPU scheduler) is the activity of the process manager that
handles the removal of the running process from the CPU and the selection of another process on
the basis of a particular strategy. A scheduling allows one process to use the CPU while another is
waiting for I/O, thereby making the system more efficient, fast and fair. In a multitasking computer
system, processes may occupy a variety of states. When a new process is created it is
automatically admitted the ready state, waiting for the execution on a CPU. Processes that are ready
for the CPU are kept in a ready queue. A process moves into the running state when it is chosen for
execution. The process&#39;s instructions are executed by one of the CPUs of the system. A process
transitions to a waiting state when a call to an I/O device occurs. The processes which are blocked
due to unavailability of an I/O device are kept in a device queue. When a required I/O device
becomes idle one of the processes from its device queue is selected and assigned to it. After
completion of I/O, a process switches from the waiting state to the ready state and is moved to the
ready queue. A process may be terminated only from the running state after completing its
execution. Terminated processes are removed from the OS.

Simulation method – Activity Scanning




# 3. Description of time and conditional events:


Time events:

- generation of process
- termination of process on CPU
- termination of process on I/O device
Time events in proper order for correctly working simulation. Each based on simulation time, or time generated to break/suspend or end of testing/suspension.

Conditional events:

- starting work on processor
- starting work on I/O Device
Event not based on time, performer after checking all time event which may influence performing those actions. All events are implemented in simulation.


# 4. What can I find in repository?


In the repository you can find code files that makes the project, &quot;podsumowanie.doc&quot; that is simple and general overview of task and &quot;project\_raport.doc&quot; that is final presentation of results.