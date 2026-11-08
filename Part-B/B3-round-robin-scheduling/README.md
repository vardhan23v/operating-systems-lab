# Experiment B3: Round Robin (RR) CPU Scheduling

## 🎯 Aim & Objective
Write a C program to implement the preemptive **Round Robin (RR)** CPU scheduling algorithm. Given `n` processes, their respective CPU burst times, and a fixed **Time Quantum** (`tq`), simulate round-robin cyclic execution and calculate:
1. Turnaround Time ($TAT$ or `tt`) for each process
2. Waiting Time ($WT$) for each process
3. Total and Average Waiting Time ($AWT$)
4. Total and Average Turnaround Time ($ATAT$)
5. Step-by-step Gantt chart showing preemption slices

---

## 📐 Formulas & Concepts

- **Remaining Burst Time:**
  $$\text{remBT}[i] \leftarrow \text{remBT}[i] - \min(\text{remBT}[i], tq)$$
- **Global Elapsed Time ($T$):**
  $$T \leftarrow T + \min(\text{remBT}[i], tq)$$
- **Completion / Turnaround Time:**
  When a process finishes ($\text{remBT}[i] = 0$):
  $$TAT_i = T_{\text{completion}}$$
- **Waiting Time:**
  $$WT_i = TAT_i - BT_i$$

---

## 📂 Files in this Experiment

- [`main.c`](./main.c) - Round Robin scheduling simulation in C

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

1. **State Tracking:**
   - `remBT[n]`: Array initialized with each process's initial burst time.
   - `time`: Monotonically increasing clock tracking system elapsed time.
2. **Round Robin Execution Loop:**
   - Iterates cyclically across process indices `0` to `n-1`.
   - `flag = 1`: Reset each pass. If any process still has `remBT[i] > 0`, `flag` is set to `0` so the loop continues.
   - **Case 1 (`remBT[i] > tq`):** The process consumes its entire quantum `tq`, `time` advances by `tq`, and `remBT[i]` is reduced. The process is preempted.
   - **Case 2 (`remBT[i] <= tq`):** The process finishes within the slice. `time` advances by the remainder `remBT[i]`, `remBT[i]` becomes 0, and the completion timestamp is recorded as turnaround time `p[i].tt`. Waiting time is immediately computed as `p[i].tt - p[i].bt`.

---

## 🧪 Expected Output

```text
$ gcc main.c
$ ./a.out
Enter the number of processes: 4
Enter burst time for p1 : 3
Enter burst time for p2 : 4
Enter burst time for p3 : 2
Enter burst time for p4 : 5
Enter the time quantum: 2

Process BT	 WT	 TAT 
 1	 3	 6	 9 
 2	 4	 7	 11 
 3	 2	 4	 6 
 4	 5	 9	 14 

Total Waiting Time: 26 ms
Average Waiting Time: 6.50 ms
Total Turn Around Time: 40 ms
Average Turn Around Time: 10.00 ms
```

### Visual Gantt Chart

```text
+----+----+----+----+----+----+----+----+
| P1 | P2 | P3 | P4 | P1 | P2 | P4 | P4 |
+----+----+----+----+----+----+----+----+
0    2    4    6    8    9   11   13   14
```

- **Slices Breakdown:**
  - `[0 - 2]`: $P_1$ runs for 2 ms (1 ms remains)
  - `[2 - 4]`: $P_2$ runs for 2 ms (2 ms remains)
  - `[4 - 6]`: $P_3$ runs for 2 ms (0 ms remains, **finishes at 6**)
  - `[6 - 8]`: $P_4$ runs for 2 ms (3 ms remains)
  - `[8 - 9]`: $P_1$ runs for 1 ms (0 ms remains, **finishes at 9**)
  - `[9 - 11]`: $P_2$ runs for 2 ms (0 ms remains, **finishes at 11**)
  - `[11 - 13]`: $P_4$ runs for 2 ms (1 ms remains)
  - `[13 - 14]`: $P_4$ runs for 1 ms (0 ms remains, **finishes at 14**)

---

## 💡 Viva Questions & Key Takeaways

1. **How does time quantum size affect Round Robin performance?**
   - **Very large quantum ($tq \to \infty$):** RR degrades into FCFS.
   - **Very small quantum ($tq \to 0$):** High scheduling overhead due to frequent context switches and CPU cache thrashing.
   - **Rule of thumb:** Around 80% of CPU bursts should be shorter than the time quantum.
2. **Does Round Robin suffer from starvation?**
   - No. Because every process in the ready queue is granted a quantum in cyclic order, starvation is impossible.
3. **What data structure is typically used for Round Robin scheduling?**
   - A First-In, First-Out (FIFO) circular queue.
