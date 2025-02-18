# CPU Scheduling Simulation

This project simulates CPU scheduling for a set of seven processes, considering multiple scheduling algorithms. The program simulates a CPU schedule for a period of 200 time units and outputs key performance metrics, such as the Gantt chart, average waiting time, and average turnaround time.

## Problem Statement:
Given the following set of processes with Arrival Times, Burst Times, and Priorities, the task is to simulate the CPU scheduling for each of the following algorithms:

### Processes:
| Process | Arrival Time | Burst Time | Priority | Come Back After |
|---------|--------------|------------|----------|-----------------|
| P1      | 0            | 10         | 2        | 10              |
| P2      | 3            | 1          | 8        | 4               |
| P3      | 2            | 3          | 14       | 6               |
| P4      | 3            | 4          | 7        | 8               |
| P5      | 1            | 6          | 5        | 3               |
| P6      | 0            | 7          | 4        | 6               |
| P7      | 1            | 8          | 6        | 9               |

### Scheduling Algorithms to Simulate:
1. **First Come First Served (FCFS)**
2. **Shortest Job First (SJF)**
3. **Shortest Remaining Time First (SRTF)**
4. **Round Robin (RR), with a time quantum (q) = 5**
5. **Preemptive Priority Scheduling, with aging** - Where the priority is decremented by 1 if the process remains in the ready queue for 5 time units.
6. **Non-preemptive Priority Scheduling, with aging** - Where the priority is decremented by 1 if the process remains in the ready queue for 5 time units.

## Features:
- Simulates CPU scheduling for a period of 200 time units.
- Calculates and displays the Gantt chart for each scheduling algorithm.
- Computes average waiting time and average turnaround time for each algorithm.

## Requirements:
- Python (or any other programming language you choose).
- Libraries for plotting the Gantt chart (e.g., `matplotlib` for Python).
- Data structures to manage processes and simulate the scheduling algorithms.

## Author
Ali Shaikh Qasem.
