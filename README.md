# SOI-WUT  
Projects done during SOI course (Operating System) at FEIT at WUT.  
  
Task 1 - add procedure in Minix - add system procedure that will return given process id index from process  table of the system  
  
Task 2 - process scheduling - add group attribute to processes - higher must be able to have longer time to work. Implement 2 procedures:  
do_changegroup - to allow for the change of the group of a process  
do_changeproc - to allow for the chenge in proportion between time given to process from group 0 and group 1  
  
Task 3 - Semaphores (processes synchronization I) - create 2 producents (p1 and p2) and 3 consumers thread. Each consumer matched  
to one buffer (queue). Producer P1 is matched to buffer A and B, producer P2 is matched to buffer B and C. Using semaphores  
provide soluttion that will be free data races.  
  
Task 4 - Monitors (processes synchronization II) - refactor task 3 to use monitors for processes synchronization.  
  
Task 5 - Memory management in Minix (draft) - add procedures and modify alloc.c in order to allow for worst fit memory hole choosing
