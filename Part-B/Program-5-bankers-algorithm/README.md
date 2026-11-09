# Part B - Program 5: Banker’s Deadlock Avoidance Algorithm

## 📝 Official Exam Question
**Write a C program to demonstrate Bankers Deadlock avoidance algorithm.**

---

## 🎯 Aim & Objective
Write a C program to implement the **Banker’s Algorithm** (Safety Algorithm) for deadlock avoidance in multi-resource systems. Given the maximum demand matrix (`MAX`), current resource allocation matrix (`Allocation`), and available resource vector (`Available`):
1. Compute the **Need Matrix**: $\text{Need}[i][j] = \text{MAX}[i][j] - \text{Allocation}[i][j]$.
2. Determine if the system is in a **Safe State** or **Unsafe State**.
3. If safe, find and display the complete **Safe Sequence** of process execution.

---

## 📐 Formulas & Concepts

- **Need Matrix Calculation:**
  $$\text{Need}[i][j] = \text{MAX}[i][j] - \text{Allocation}[i][j]$$
- **Safety Criterion (Work & Finish vectors):**
  - $\text{Work} = \text{Available}$
  - $\text{Finish}[i] = \text{false}$ for all $i$
  - Find an index $i$ such that:
    1. $\text{Finish}[i] == \text{false}$
    2. $\text{Need}[i][j] \le \text{Work}[j]$ for all resource types $j$
  - If such $i$ exists:
    - $\text{Work}[j] \leftarrow \text{Work}[j] + \text{Allocation}[i][j]$
    - $\text{Finish}[i] \leftarrow \text{true}$
    - Append $P_i$ to Safe Sequence
  - If all $\text{Finish}[i] == \text{true}$, system is in a **Safe State**. Otherwise, system is in an **Unsafe State**.

---

## 📂 Files in this Experiment

- [`main.c`](./main.c) - Banker's algorithm implementation in C

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

1. **Input Representation:**
   - `p`: Total processes (e.g. 5)
   - `r`: Total resource types (e.g. 4)
   - Matrices: `max[p][r]`, `alloc[p][r]`, `avail[r]`
2. **Need Matrix Computation:**
   - For every process $i$ and resource $j$, `need[i][j] = max[i][j] - alloc[i][j]`.
   - Initializes `finish[i] = 0`.
3. **Safety Evaluation Pass:**
   - A multi-pass while loop checks each unallocated process (`finish[i] == 0`).
   - If its remaining needs can be met by currently available resources (`need[i][j] <= avail[j]`), it is marked as satisfiable:
     - Available resources are incremented by the resources this process releases upon termination: `avail[k] += alloc[i][k]`.
     - The process index is appended to `safeseq[count++]`.
     - `finish[i] = 1`.
4. **Deadlock / Unsafe Detection:**
   - If an entire pass completes without satisfying at least one new process (`found == 0`), the system cannot guarantee safe execution without risking deadlock and terminates declaring `"System is in unsafe state"`.

---

## 🧪 Expected Output

```text
$ gcc main.c
$ ./a.out
Enter the number of processes:5
Enter the number of resources:4
Enter the MAX matrix:
0 0 1 2
1 7 5 0
2 3 5 6
0 6 5 2
0 6 5 6
Enter the Allocation matrix:
0 0 1 2
1 0 0 0
1 3 5 4
0 6 3 2
0 0 1 4
Enter the Available matrix:
1 5 2 0
The Need matrix:
0	0	0	0	
0	7	5	0	
1	0	0	2	
0	0	2	0	
0	6	4	2	
System is in safe state
Safe Sequence is: P1	 P3	 P4	 P5	 P2	
```

---

## 💡 Viva Questions & Key Takeaways

1. **Why is it called the "Banker's Algorithm"?**
   - Because it mimics a bank that never allocates cash in a way that it can no longer satisfy the credit limits of all its customers.
2. **What is the difference between Deadlock Prevention and Deadlock Avoidance?**
   - **Deadlock Prevention:** Restricts how resource requests are made to structurally ensure that at least one of the 4 Coffman conditions cannot hold.
   - **Deadlock Avoidance:** Allows dynamic requests, but the OS analyzes prospective allocations before granting them to ensure the system remains in a safe state.
3. **Is an unsafe state always a deadlock?**
   - No. An unsafe state is not necessarily a deadlock, but rather a state from which the OS cannot guarantee that a deadlock will not occur. All deadlocks are unsafe, but not all unsafe states result in deadlocks.
