# Part A - Program 7: Semaphores using Binary Semaphores

## 📝 Official Exam Question
**Write a C program to demonstrate Semaphores using binary semaphores.**

---

## 🎯 Aim & Objective
Write a multithreaded C program using POSIX Semaphores (`semaphore.h`) to demonstrate process synchronization and mutual exclusion using a **Binary Semaphore**. Three threads execute concurrently, using `sem_wait()` to enter and `sem_post()` to leave the critical section one thread at a time.

---

## 📦 Required System Calls & Headers

| Header | POSIX Function | Purpose |
|---|---|---|
| `<semaphore.h>` | `sem_t` | Type definition for POSIX semaphore |
| `<semaphore.h>` | `sem_init(&sem, pshared, value)` | Initializes unnamed semaphore. `pshared=0` (threads), `value=1` (binary) |
| `<semaphore.h>` | `sem_wait(&sem)` | Decrements semaphore. If value <= 0, caller blocks (P operation / wait) |
| `<semaphore.h>` | `sem_post(&sem)` | Increments semaphore and unblocks waiting thread (V operation / signal) |
| `<semaphore.h>` | `sem_destroy(&sem)` | Destroys the unnamed semaphore |
| `<pthread.h>` | `pthread_create()`, `pthread_join()` | POSIX thread management functions |

---

## 📂 Files in this Experiment

- [`main.c`](./main.c) - Binary semaphore synchronization implementation

---

## 🛠 Compilation & Execution Instructions

```bash
# 1. Compile with POSIX threads & realtime library (on Linux)
gcc main.c -lpthread -o main

# 2. Run the executable
./main
```

> **macOS Compatibility Note:**
> POSIX unnamed semaphores (`sem_init`) are supported natively on all standard Linux systems (Ubuntu, Debian, CentOS, WSL), which are standard in college lab environments. On macOS (Darwin kernel), `sem_init` is marked deprecated in favor of named semaphores (`sem_open`). To test on macOS without warnings, run inside a Linux Docker container or Linux VM.

---

## 🔍 Code Walkthrough

1. **Initialization (`sem_init(&semaphore, 0, 1)`):**
   - The first argument points to the `sem_t` object.
   - The second argument `pshared = 0` indicates the semaphore is shared only between threads of the calling process (not between multiple separate processes).
   - The third argument `value = 1` sets the initial counter to 1, creating a **Binary Semaphore** (acts as a mutual exclusion lock).
2. **`sem_wait(&semaphore)` (P operation):**
   - Atomically decrements the semaphore counter. If the value becomes 0, the thread proceeds into the critical section. Subsequent threads will see `<= 0` and are suspended in a FIFO wait queue.
3. **`sem_post(&semaphore)` (V operation):**
   - Atomically increments the semaphore counter. If threads are blocked in the wait queue, one is awakened and granted entry.
4. **Thread Join and Destruction:**
   - `pthread_join` waits for all three worker threads to exit, followed by `sem_destroy` to release kernel semaphore structures.

---

## 🧪 Expected Output

```text
$ gcc main.c -lpthread
$ ./a.out
Thread 1: Waiting to enter critical section..
Thread 1: Entered critical section.
Thread 2: Waiting to enter critical section..
Thread 3: Waiting to enter critical section..
Thread 1: Leaving critical section.
Thread 2: Entered critical section.
Thread 2: Leaving critical section.
Thread 3: Entered critical section.
Thread 3: Leaving critical section.
All threads have finished execution.
```

---

## 💡 Viva Questions & Key Takeaways

1. **What is a Semaphore? Who invented it?**
   - A semaphore is an integer variable used for signaling and synchronizing concurrent processes/threads. It was invented by Edsger Dijkstra in 1965.
2. **What are the atomic operations defined on a semaphore?**
   - **`wait()` (also called `P()` or `down()`):** Decrements the semaphore value. If value is negative/zero, process blocks.
   - **`signal()` (also called `V()` or `up()`):** Increments the semaphore value. If processes are waiting, one is awakened.
3. **What is the difference between a Counting Semaphore and a Binary Semaphore?**
   - A **Binary Semaphore** has an integer value that can only range between 0 and 1, functioning like a mutex lock.
   - A **Counting Semaphore** can take any non-negative integer value, typically used to control access to a resource pool with a finite number of identical instances.
