Task Description
  A process is the collection of instructions that running on the CPU. A process has following properties: 
      • Process ID (such as 1, 2, 3..) 
      • Arrival time 
      • Priority 
      • Burst Time 
      
  Your task is to create a process scheduler simulator to calculate each given processes completion time, average 
  turnaround time and average waiting time. You must simulate following scheduling algorithms: 
      • First Come First Serve 
      • Shortest Job First 
      • Priority Scheduling 
  
  Scheduling algorithms must be selected via first command line parameter. A User should pass “FCFS” to run First 
  Come First Serve, “SJF” to run Shortest Job First, “PRIO” to run Priority Scheduling. Processes to simulate must be 
  read from a file given in second command line parameter. Each line must contain 1 process data (process id, arrival 
  time, priority, burst time) separated with a space, maximum of 10 processes should supported. This file must be read 
  into a 2D integer array (int processes[10][4]). 
      $ ./simulator SJF process.txt 


Output Format 
  Your program must produce output exactly following format: 
      • Process %d Completion Time: %d 
      • Average Turnaround Time: %.2f 
      • Average Waiting Time: %.2f 
      
  Example Output For 3 Processes: 
  Process 2 Completion Time: 4 
  Process 3 Completion Time: 7 
  Process 1 Completion Time: 8 
  Average Turnaround Time: 5.10 
  Average Waiting Time: 2.70 

  
Bonus 
  • Using a Makefile build (+5 points)
