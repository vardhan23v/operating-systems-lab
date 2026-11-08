# Experiment B1: First-Come, First-Served (FCFS) CPU Scheduling

## 🎯 Aim & Objective
Write a C program to implement the **First-Come, First-Served (FCFS)** non-preemptive CPU scheduling algorithm. Given `n` processes and their respective CPU Burst Times (assuming all arrive at time 0 in order `P1, P2, ... Pn`), calculate:
1. Waiting Time ($WT$) for each process
2. Turnaround Time ($TAT$) for each process
3. Total and Average Waiting Time ($AWT$)
4. Total and Average Turnaround Time ($ATAT$)
5. Visual Gantt Chart timeline

---

## 📐 Formulas & Concepts

- **Waiting Time ($WT_i$):**
  $$WT_0 = 0$$
  $$WT_i = WT_{i-1} + BT_{i-1} = \sum_{k=0}^{i-1} BT_k$$
- **Turnaround Time ($TAT_i$):**
  $$TAT_i = BT_i + WT_i$$
- **Average Waiting Time ($AWT$):**
  $$AWT = \frac{\sum WT_i}{n}$$
- **Average Turnaround Time ($ATAT$):**
  $$ATAT = \frac{\sum TAT_i}{n}$$

---

## 📂 Files in this Experiment

- [`main.c`](./main.c) - FCFS scheduling implementation in C

---

## 🛠 Compilation & Execution Instructions

```bash
# 1. Compile the program
gcc main.c -o main

# 2. Run the executable
./main
```

---

## 🔍 Code Walkthrough

1. **Process Structure Definition:**
   ```c
   struct Process {
       int pid, bt, wt, tat;
   };
   ```
2. **Sequential Queue Scheduling:**
   - Because FCFS is non-preemptive and ordered strictly by process index (arrival), Process 1 executes immediately at $t = 0$.
   - Process `i` starts execution exactly when process `i-1` finishes.
3. **Accumulator and Averages:**
   - Sums total waiting time and turnaround time, calculating double-precision averages formatted to 2 decimal places.

---

## 🧪 Expected Output

```text
$ gcc main.c
$ ./a.out
Enter number of processes: 4
Enter burst time for P1: 3
Enter burst time for P2: 4
Enter burst time for P3: 2
Enter burst time for P4: 5

 Process BT	 WT	 TAT	
 1	 3	 0	 3 
 2	 4	 3	 7 
 3	 2	 7	 9 
 4	 5	 9	 14 

Total Waiting Time = 19.00
Average Waiting Time = 4.75
Total Turn Around Time = 33.00
Average Turn Around Time = 8.25
```

### Visual Gantt Chart

```text
+-------+-------+-----+---------+
|  P1   |  P2   | P3  |   P4    |
+-------+-------+-----+---------+
0       3       7     9        14
```

---

## 💡 Viva Questions & Key Takeaways

1. **What is the Convoy Effect in FCFS?**
   - The Convoy Effect occurs when a CPU-intensive process with a very long burst time executes first, forcing all subsequent short or I/O-bound processes to wait, drastically increasing average waiting time.
2. **Is FCFS preemptive or non-preemptive?**
   - FCFS is strictly **non-preemptive**. Once the CPU has been allocated to a process, it keeps the CPU until it terminates or requests I/O.
3. **What is Turnaround Time vs Waiting Time?**
   - **Turnaround Time ($TAT$):** Total elapsed time from process submission to process completion ($TAT = \text{Completion Time} - \text{Arrival Time}$).
   - **Waiting Time ($WT$):** Total amount of time a process spends waiting in the ready queue ($WT = TAT - BT$).
