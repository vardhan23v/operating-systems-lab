# Operating Systems Laboratory: Comprehensive Walkthrough & Theory Guide

This guide provides an end-to-end technical walkthrough of the core POSIX system programming concepts, synchronization primitives, scheduling algorithms, and deadlock avoidance techniques covered in the **Operating Systems Laboratory**.

---

## Table of Contents
1. [Architecture of POSIX System Calls](#1-architecture-of-posix-system-calls)
2. [Process Management: `fork()`, `exec()`, and `wait()`](#2-process-management-fork-exec-and-wait)
3. [File System Internals: Descriptors & Low-Level I/O](#3-file-system-internals-descriptors--low-level-io)
4. [Asynchronous Signal Handling](#4-asynchronous-signal-handling)
5. [Process Synchronization: Mutex vs Semaphores](#5-process-synchronization-mutex-vs-semaphores)
6. [CPU Scheduling Theory & Mathematical Comparison](#6-cpu-scheduling-theory--mathematical-comparison)
7. [Deadlock Avoidance: Banker's Safety Algorithm](#7-deadlock-avoidance-bankers-safety-algorithm)
8. [Debugging, Profiling & Common System Programming Pitfalls](#8-debugging-profiling--common-system-programming-pitfalls)

---

## 1. Architecture of POSIX System Calls

### User Mode vs Kernel Mode
Modern CPUs enforce privilege rings to protect critical hardware resources and memory spaces:
- **User Mode (Ring 3):** User programs run with limited privileges. Direct hardware access, arbitrary memory manipulation, and direct hardware I/O instructions are disabled.
- **Kernel Mode (Ring 0):** The OS kernel runs with full hardware privileges, having direct access to physical memory, interrupt controllers, and CPU registers.

```
+-----------------------------------------------------------+
|                     User Application                      |
|                  (e.g., main.c, read())                   |
+-----------------------------+-----------------------------+
                              |
                     System Call Invocation
                   (Trap / Syscall Instruction)
                              |
==============================v==============================
                    KERNEL BOUNDARY (Ring 0)
==============================+==============================
                              |
                    System Call Dispatcher
                      (sys_call_table[])
                              |
        +---------------------+---------------------+
        |                     |                     |
     sys_read              sys_write             sys_fork
        |                     |                     |
   VFS / Inode           Terminal Driver       Process Table
```

### The System Call Lifecycle
1. The user program invokes a C wrapper function (e.g., `read()`).
2. The wrapper copies system call parameters into designated hardware registers (`rdi`, `rsi`, `rdx` on x86-64).
3. The CPU executes a special machine instruction (`syscall` on x86-64 or `svc` on ARM64), raising a software interrupt that traps execution into Kernel Mode.
4. The kernel saves the user process state (registers, program counter), checks access permissions, and looks up the routine in `sys_call_table`.
5. The kernel routine executes and writes the return status into the accumulator register (`rax` or `x0`).
6. The CPU executes `sysret` / `eret` to transition back to User Mode, restoring user program registers.

---

## 2. Process Management: `fork()`, `exec()`, and `wait()`

### Process Creation with `fork()`
When a process executes `pid = fork()`, the OS creates a near-identical clone of the calling process:
- **Address Space:** The child inherits an exact duplicate of the parent's text, data, BSS, heap, and stack segments.
- **Copy-On-Write (COW):** Rather than copying all physical memory pages immediately, the kernel marks the virtual memory pages as read-only. A physical copy is made only when either parent or child attempts to write to a page.
- **File Descriptors:** Open file descriptors are shared between parent and child, pointing to the same open file table entries.
- **Return Values:**
  - In parent: returns the child PID ($> 0$).
  - In child: returns $0$.
  - On error: returns $-1$.

### Why `fflush(stdout)` is Essential Before `fork()`
Standard C library functions (`printf`) use user-space buffers. If output has been written but not yet flushed (no newline or buffer not full):
```c
printf("Parent message"); // buffered in user-space
fork();                   // clones user-space buffer into child!
// Both parent and child will flush the duplicate message on exit!
```
Always call `fflush(stdout)` immediately before `fork()` to ensure the user-space buffer is clean.

### Replacing Process Images with `exec()`
The `exec()` system call family replaces the current process address space with a new program image loaded from an executable:
- The existing code, stack, and heap segments are completely unmapped and replaced.
- The **Process ID (PID) does NOT change**.
- Open file descriptors remain open across `exec()` unless configured with `FD_CLOEXEC`.
- If `exec()` succeeds, execution begins at the entry point of the new binary; it **never returns** to the calling code.

### Process States: Zombie vs Orphan
```
                      +-------------------+
                      |      Running      |
                      +---------+---------+
                                |
                   exit(0)      |  Parent terminates first
              +-----------------+-----------------+
              |                                   |
              v                                   v
    +-------------------+               +-------------------+
    |      Zombie       |               |      Orphan       |
    | (Child terminated,|               | (Parent died,     |
    |  parent hasn't    |               |  adopted by PID 1 |
    |  called wait())   |               |  init / systemd)  |
    +---------+---------+               +-------------------+
              |
         wait(NULL)
              |
              v
    +-------------------+
    | Process Table     |
    | Slot Reclaimed    |
    +-------------------+
```

---

## 3. File System Internals: Descriptors & Low-Level I/O

POSIX processes manage I/O through integer handles called **File Descriptors (FD)**:

| FD Value | Symbolic Constant | Default Stream |
|:---:|---|---|
| `0` | `STDIN_FILENO` | Standard Input (Keyboard) |
| `1` | `STDOUT_FILENO` | Standard Output (Terminal Display) |
| `2` | `STDERR_FILENO` | Standard Error (Terminal Display) |

### The Three Kernel Tables for Open Files
1. **Per-Process File Descriptor Table:** Indexed by the integer FD (`0, 1, 2, ...`). Contains pointers into the System-Wide Open File Table.
2. **System-Wide Open File Table:** Tracks current file offset, access mode (`O_RDONLY`, `O_WRONLY`), and reference count.
3. **VFS Inode Table:** Holds actual file metadata (permissions, file size, block disk pointers) stored on disk.

```
Process A                        Open File Table                   Inode Table
FD Table
+----+                      +-----------------------+         +------------------+
| 0  |                      | File Offset: 1024     |         | File: readme.txt |
| 1  |                      | Status Flags: O_RDONLY+-------->| Size: 4096 bytes |
| 2  |                      | Ref Count: 2          |         | Inode #: 98124   |
| 3  +--------------------->+-----------------------+         +------------------+
+----+                                  ^
                                        |
Process B                               |
FD Table                                |
+----+                                  |
| 3  +----------------------------------+
+----+
```

---

## 4. Asynchronous Signal Handling

Signals are software interrupts delivered by the operating system kernel:

### Standard Signals
- **`SIGINT` (Signal 2):** Terminal interrupt. Triggered by typing `Ctrl+C`. Default action: terminate.
- **`SIGTERM` (Signal 15):** Generic termination signal sent by `kill`. Can be intercepted to allow graceful cleanup.
- **`SIGHUP` (Signal 1):** Hangup detected on controlling terminal or death of controlling process. Often used by daemons to reload configuration.
- **`SIGALRM` (Signal 14):** Real-time timer alarm generated by the kernel when the timer set by `alarm(seconds)` expires.
- **`SIGUSR1` (Signal 10):** User-defined condition 1, available for application-defined signaling.

### Signal Delivery Sequence
1. **Generation:** An event creates a signal (hardware exception, CLI `kill`, or system call `alarm()`).
2. **Pending:** The kernel records the pending signal in the process's task structure mask.
3. **Delivery:** When the process next transitions from Kernel Mode to User Mode, the kernel checks pending signals.
4. **Handling:** If a custom handler is registered via `signal(sig, handler)`, the kernel pivots the process stack pointer and transfers control directly to the handler function.

---

## 5. Process Synchronization: Mutex vs Semaphores

When multiple concurrent execution threads access shared memory variables, race conditions occur unless mutual exclusion is enforced.

### Mutex (`pthread_mutex_t`)
- **Ownership:** A mutex has an owner—only the specific thread that called `pthread_mutex_lock()` is legally permitted to call `pthread_mutex_unlock()`.
- **Purpose:** Strictly designed for **Mutual Exclusion** over a shared critical section.
- **Deadlock risk:** If a thread terminates while holding a mutex, other waiting threads block indefinitely.

### Semaphore (`sem_t`)
- **No Ownership:** Any thread can execute `sem_post()` (V operation) to wake up a thread blocked on `sem_wait()` (P operation).
- **Types:**
  - **Binary Semaphore ($S \in \{0, 1\}$):** Functions similarly to a mutex, initialized to 1.
  - **Counting Semaphore ($S \ge 0$):** Used for resource counting (e.g., bounded-buffer tracking).

### Comparison Matrix

| Feature | Mutex (`pthread_mutex_t`) | Binary Semaphore (`sem_t`) | Counting Semaphore (`sem_t`) |
|---|---|---|---|
| **Initial Value** | Unlocked | $1$ | $N$ (Resource count) |
| **Value Range** | Locked / Unlocked | $0$ or $1$ | $0$ to $N$ |
| **Ownership** | Enforced (only locking thread unlocks) | None (any thread can post) | None |
| **Primary Use Case** | Critical section mutual exclusion | Signaling & mutual exclusion | Managing pools of identical resources |
| **API** | `pthread_mutex_lock / unlock` | `sem_wait / sem_post` | `sem_wait / sem_post` |

---

## 6. CPU Scheduling Theory & Mathematical Comparison

### Metrics
- **Burst Time ($BT$):** Time required by the process for CPU execution.
- **Arrival Time ($AT$):** Time at which process enters ready queue (assumed 0 in our experiments).
- **Completion Time ($CT$):** Timestamp when process finishes execution.
- **Turnaround Time ($TAT$):** $TAT = CT - AT$
- **Waiting Time ($WT$):** $WT = TAT - BT$

### Algorithm Comparison

| Algorithm | Preemption | Strategy | Advantages | Disadvantages |
|---|---|---|---|---|
| **FCFS** | Non-preemptive | First-Come, First-Served | Simple, zero scheduling overhead | Suffers from Convoy Effect; high average waiting time |
| **SJF** | Non-preemptive | Shortest burst time first | Provably minimal average waiting time | Requires knowing future burst durations; starves long jobs |
| **Round Robin** | Preemptive | Cyclic time quantum slicing | Fair, starvation-free, responsive for interactive systems | Context switch overhead if quantum is too small |

---

## 7. Deadlock Avoidance: Banker's Safety Algorithm

A system is in a **Safe State** if there exists at least one sequence $\langle P_1, P_2, \dots, P_n \rangle$ such that for each $P_i$, the maximum resources $P_i$ can request can be satisfied by current available resources plus resources already held by all preceding processes $P_j$ ($j < i$).

### The 4 Coffman Conditions
Deadlock can occur if and only if all four conditions hold simultaneously:
1. **Mutual Exclusion:** At least one resource must be held in a non-shareable mode.
2. **Hold and Wait:** A process must be holding at least one resource and requesting additional resources currently held by others.
3. **No Preemption:** Resources cannot be forcibly preempted from a process; they can only be released voluntarily.
4. **Circular Wait:** A closed chain of processes exists, where each process holds resources needed by the next.

### Mathematical Invariants in Banker's Algorithm
$$\text{Allocation}[i][j] \le \text{MAX}[i][j]$$
$$\text{Need}[i][j] = \text{MAX}[i][j] - \text{Allocation}[i][j]$$
$$\sum_{i=1}^{p} \text{Allocation}[i][j] + \text{Available}[j] = \text{Total Resource Instances}[j]$$

---

## 8. Debugging, Profiling & Common System Programming Pitfalls

### Common Runtime Errors & Solutions

| Error Message / Symptom | Root Cause | Diagnosis & Fix |
|---|---|---|
| `undefined reference to 'pthread_create'` | Missing POSIX threads library at linkage | Append `-pthread` or `-lpthread` to compiler command: `gcc main.c -pthread` |
| `Segmentation fault (core dumped)` | Dereferencing NULL pointer, uninitialized pointer, or out-of-bounds array access | Compile with debug symbols and run with GDB: `gcc -g main.c && gdb ./a.out` |
| Output printed twice after `fork()` | Buffered characters in standard I/O buffer duplicated into child process memory | Insert `fflush(stdout);` immediately preceding every `fork()` call |
| Thread race condition / corrupted totals | Multiple threads modifying shared global variable without synchronization | Protect shared write operations using `pthread_mutex_lock(&mutex)` |
| `Function not implemented` on macOS `sem_init` | macOS Darwin kernel deprecated unnamed semaphores (`sem_init`) | Unnamed semaphores are Linux-standard. Use Linux/WSL for lab exams or test via Docker |

### Tracing System Calls
- On **Linux**:
  ```bash
  strace -f -e trace=open,read,write,fork,execve ./main
  ```
- On **macOS**:
  ```bash
  sudo dtruss ./main
  ```
