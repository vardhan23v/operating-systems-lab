# Part A - Program 3: Create Five Child Processes using `fork()`

## 📝 Official Exam Question
**Write the program to create five Child Processes using system call fork() and display their ids.**

---

## 🎯 Aim & Objective
Write a C program to create exactly five child processes sequentially using the `fork()` system call, print the child process ID (`PID`) and parent process ID (`PPID`) from both parent and child contexts, and ensure the parent waits for all five children to finish before terminating.

---

## 📦 Required System Calls & Headers

| Header | System Call / Function | Purpose |
|---|---|---|
| `<unistd.h>` | `fork()` | Clones the calling process creating an exact child process |
| `<unistd.h>` | `getpid()` | Returns the PID of the calling process |
| `<unistd.h>` | `getppid()` | Returns the parent PID of the calling process |
| `<sys/wait.h>` | `wait(NULL)` | Suspends parent execution until a child process terminates |
| `<stdlib.h>` | `exit(0)` | Terminates child execution and returns exit status to parent |

---

## 📂 Files in this Experiment

- [`main.c`](./main.c) - Forking and process synchronization implementation

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

1. **Loop Iteration (`i = 1` to `5`):**
   - `fflush(stdout)`: Crucial before calling `fork()`. Any pending characters in the stdio user buffer would otherwise be cloned into the child's address space, producing duplicate print outputs.
2. **`fork()` Return Values:**
   - `< 0`: Process creation failed (e.g., system process table exhausted).
   - `== 0`: Inside the newly created **Child Process**. Prints child PID (`getpid()`) and parent PID (`getppid()`), then calls `exit(0)`.
   - `> 0`: Inside the **Parent Process**. The return value is the newly spawned child's PID. The parent prints this info and proceeds to the next iteration.
3. **`wait(NULL)` Loop:**
   - The parent calls `wait(NULL)` 5 times, preventing child processes from lingering as **Zombie processes** in the process table.
4. **Final Termination:**
   - Once all 5 children have exited and their exit statuses collected, the parent displays its final PID and cleanly exits.

---

## 🧪 Expected Output

```text
$ gcc main.c
$ ./a.out
Parent Created Child 1 with pid 414
Child 1 with id 414 and Parent Process id 413
Parent Created Child 2 with pid 415
Child 2 with id 415 and Parent Process id 413
Parent Created Child 3 with pid 416
Child 3 with id 416 and Parent Process id 413
Parent Created Child 4 with pid 417
Child 4 with id 417 and Parent Process id 413
Parent Created Child 5 with pid 418
Child 5 with id 418 and Parent Process id 413
Parent pid 413 after finishing all Child execution
```

*(Note: The actual PID numbers will vary depending on your system's current process table allocations).*

---

## 💡 Viva Questions & Key Takeaways

1. **What does `fork()` return to the child process and to the parent process?**
   - Returns `0` to the child process, and returns the child's `PID` to the parent process. Returns `-1` if creation fails.
2. **What is a Zombie Process? How is it prevented here?**
   - A zombie process is a process that has completed execution via `exit()`, but still has an entry in the OS process table because its parent has not yet read its exit status. Calling `wait(NULL)` reaps the child's status and removes the zombie.
3. **What is an Orphan Process?**
   - An orphan process occurs when a parent terminates before its child. The orphan is automatically adopted by `init` (PID 1) or `systemd`.
