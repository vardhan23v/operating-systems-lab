# Part A - Program 5: Signal Handler for SIGINT, SIGTERM, SIGHUP, SIGALRM, SIGUSR1

## 📝 Official Exam Question
**Write a C program that registers a signal handler for SIGINT, SIGTERM, SIGHUP, SIGALRM, and SIGUSR1. The handler should receive each signal and perform some operation.**

---

## 🎯 Aim & Objective
Write a C program that registers a unified custom signal handler for five POSIX signals: `SIGINT`, `SIGTERM`, `SIGHUP`, `SIGALRM`, and `SIGUSR1`. The program prints its Process ID (`PID`), sets an alarm timer for 20 seconds, and enters an infinite sleep loop waiting to catch signals sent from the keyboard or a second terminal via the `kill` command.

---

## 📦 Required System Calls & Headers

| Header | System Call / Function | Purpose |
|---|---|---|
| `<signal.h>` | `signal(signum, handler)` | Attaches the custom handler function to the specified signal |
| `<signal.h>` | `SIGINT`, `SIGTERM`, `SIGHUP`, `SIGALRM`, `SIGUSR1` | POSIX signal macros representing asynchronous notifications |
| `<unistd.h>` | `alarm(seconds)` | Sends a `SIGALRM` signal to the invoking process after elapsed real time |
| `<unistd.h>` | `getpid()` | Retrieves PID of current process for sending signals via CLI |
| `<unistd.h>` | `sleep(seconds)` | Suspends thread execution until time expires or a signal arrives |

---

## 📂 Files in this Experiment

- [`main.c`](./main.c) - Signal registration and handler dispatch program

---

## 🛠 Compilation & Execution Instructions

### Terminal 1 (Running the program)
```bash
# 1. Compile the program
gcc main.c -o main

# 2. Run the process
./main
Process Id of program running = 430
Waiting for signal
```

### Terminal 2 (Sending signals to Terminal 1)
Using the PID shown in Terminal 1 (e.g., `430`):
```bash
kill -SIGINT 430
kill -SIGHUP 430
kill -SIGUSR1 430
kill -SIGALRM 430
kill -SIGTERM 430
```

---

## 🔍 Code Walkthrough

1. **Signal Registration (`signal`):**
   - In `main()`, `signal(SIGNUM, signalhandler)` registers our custom function `signalhandler` to replace the default kernel actions.
2. **`alarm(20)`:**
   - Starts an asynchronous kernel timer for 20 seconds. If no external signals interfere, the kernel delivers `SIGALRM` after 20 seconds.
3. **Signal Handler Execution (`signalhandler`):**
   - When a registered signal occurs, execution jumps immediately into `signalhandler(int sig)`.
   - Matches the signal number and prints corresponding diagnostic messages:
     - `SIGINT`: "Caught an Interrupt Signal" (can also be triggered by `Ctrl+C`).
     - `SIGHUP`: "Caught a Hangup Signal".
     - `SIGUSR1`: "Caught a User Signal" (custom user-defined signal).
     - `SIGALRM`: "Caught an Alarm Signal".
     - `SIGTERM`: "Caught a Terminate Signal", which performs clean shutdown via `exit(0)`.

---

## 🧪 Expected Output

### Terminal 1 Output
```text
$ gcc main.c
$ ./a.out
Process Id of program running = 430
Waiting for signal
Caught an Interrupt Signal
Waiting for signal
Caught a Hangup Signal
Waiting for signal
Caught a User Signal
Waiting for signal
Caught an Alarm Signal
Waiting for signal
Caught a Terminate Signal
```

### Terminal 2 Input
```text
kill -SIGINT 430
kill -SIGHUP 430
kill -SIGUSR1 430
kill -SIGALRM 430
kill -SIGTERM 430
```

---

## 💡 Viva Questions & Key Takeaways

1. **What is a Signal in an Operating System?**
   - A signal is an asynchronous software interrupt delivered by the OS kernel to a process to notify it of a specific event (e.g., timer expiration, hardware exception, termination request).
2. **Which two signals cannot be caught, blocked, or ignored?**
   - `SIGKILL` (signal 9) and `SIGSTOP` (signal 19). They are unconditionally handled by the kernel to allow infallible process termination and job suspension.
3. **What is the difference between `SIGTERM` and `SIGKILL`?**
   - `SIGTERM` (signal 15) is a polite termination request that allows a process to save state, close files, and clean up resources. `SIGKILL` (signal 9) immediately and forcibly terminates the process without cleanup.
