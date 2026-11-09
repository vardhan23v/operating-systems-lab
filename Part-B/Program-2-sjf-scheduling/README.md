# Part B - Program 2: Shortest Job First (SJF) Scheduling Algorithm

## 📝 Official Exam Question
**Write a C program to implement Shortest Job First Scheduling algorithm to determine total waiting time, average waiting time, total turn around time and average turnaround time.**

---

## 🎯 Aim & Objective
Write a C program to implement the **Shortest Job First (SJF)** non-preemptive CPU scheduling algorithm. Given `n` processes arriving simultaneously at time 0:
1. Sort processes in ascending order of their CPU burst times.
2. Break ties deterministically by preserving arrival/PID order (`P1 < P2 < ... < Pn`).
3. Compute Waiting Time ($WT$), Turnaround Time ($TAT$), Average Waiting Time ($AWT$), and Average Turnaround Time ($ATAT$).
4. Illustrate the execution order with a Gantt chart.

---

## 📐 Formulas & Concepts

- **Sorting Criterion:**
  $$\text{Sort } P \text{ such that } BT_i \le BT_{i+1}$$
  $$\text{Tie-breaker: If } BT_i = BT_j \text{ and } i < j, \text{ schedule } P_i \text{ before } P_j$$
- **Waiting Time ($WT_i$):**
  $$WT_0 = 0$$
  $$WT_i = WT_{i-1} + BT_{i-1}$$
- **Turnaround Time ($TAT_i$):**
  $$TAT_i = WT_i + BT_i$$

---

## 📂 Files in this Experiment

- [`main.c`](./main.c) - SJF non-preemptive scheduling implementation

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

1. **Selection Sort by Burst Time (`min` selection):**
   ```c
   if (p[j].bt < p[min].bt ||
      (p[j].bt == p[min].bt && p[j].pid < p[min].pid))
   {
       min = j;
   }
   ```
   - Scans the unscheduled processes for the smallest CPU burst time.
   - If two processes have identical burst times, it preserves FCFS / PID tie-breaking.
2. **Sequential Metrics Calculation:**
   - Once sorted, the calculation mirrors non-preemptive scheduling with $WT_0 = 0$.
3. **Optimality:**
   - SJF is provably optimal for minimizing average waiting time among all non-preemptive algorithms when all jobs are available at time 0.

---

## 🧪 Expected Output

```text
$ gcc main.c
$ ./a.out
Enter no of process: 3
Enter burst time for p1 : 6
Enter burst time for p2 : 7
Enter burst time for p3 : 2

Process BT	 WT	 TAT
3	 2	 0	 2
1	 6	 2	 8
2	 7	 8	 15

Total Waiting Time = 10.00
Total Turn Around Time = 25.00
Average Waiting Time = 3.33
Average Turn Around Time = 8.33
```

### Visual Gantt Chart

```text
+-----+---------------+-----------------+
| P3  |      P1       |       P2        |
+-----+---------------+-----------------+
0     2               8                15
```

---

## 💡 Viva Questions & Key Takeaways

1. **Why is SJF considered optimal?**
   - By scheduling the shortest job first, the fast-finishing jobs leave the waiting queue quickly, decreasing the cumulative waiting time and minimizing the mathematical mean ($AWT$).
2. **What is the major disadvantage of SJF in real-world operating systems?**
   - **Difficulty in predicting burst time:** The OS cannot know the exact next CPU burst duration in advance (it can only estimate using exponential moving averages).
   - **Starvation:** Long processes may wait indefinitely if short processes arrive continuously.
3. **What is the preemptive version of SJF called?**
   - Shortest Remaining Time First (SRTF).
