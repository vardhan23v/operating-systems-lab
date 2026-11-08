# Experiment A6: Critical Section Using Mutex Lock

## 🎯 Aim & Objective
Write a multithreaded C program using POSIX Threads (`pthread`) to demonstrate the Critical Section problem and its resolution using a **Mutex Lock** (`pthread_mutex_t`). Three threads concurrently attempt to increment a shared global counter, ensuring Mutual Exclusion so that only one thread executes inside the critical region at any time.

---

## 📦 Required System Calls & Headers

| Header | POSIX Function | Purpose |
|---|---|---|
| `<pthread.h>` | `pthread_create()` | Spawns a new concurrent execution thread |
| `<pthread.h>` | `pthread_join()` | Blocks caller until the target thread terminates |
| `<pthread.h>` | `pthread_mutex_init()` | Initializes the mutual exclusion lock |
| `<pthread.h>` | `pthread_mutex_lock()` | Acquires the lock (blocks if held by another thread) |
| `<pthread.h>` | `pthread_mutex_unlock()` | Releases the lock, allowing waiting threads to proceed |
| `<pthread.h>` | `pthread_mutex_destroy()` | Cleans up and deallocates mutex resources |

---

## 📂 Files in this Experiment

- [`main.c`](./main.c) - Mutex-synchronized multithreaded counter implementation

---

## 🛠 Compilation & Execution Instructions

```bash
# 1. Compile with POSIX threads library
gcc main.c -lpthread -o main

# 2. Run the executable
./main
```

---

## 🔍 Code Walkthrough

1. **Race Condition Prevention:**
   - `shared_counter++` in assembly consists of three separate machine instructions: (1) load variable to register, (2) increment register, (3) store back to memory. Without synchronization, concurrent context switches lead to lost updates.
2. **Mutex Lock (`pthread_mutex_lock(&mutex)`):**
   - Thread 1 locks the mutex. If Thread 2 or Thread 3 tries to enter, they are put into a waiting sleep queue by the thread scheduler.
3. **Critical Section:**
   - Safely increments `shared_counter` and simulates work using `sleep(1)`.
4. **Mutex Unlock (`pthread_mutex_unlock(&mutex)`):**
   - Releases the lock, waking up the next waiting thread.
5. **Thread Joining & Cleanup:**
   - `main()` calls `pthread_join()` for all 3 threads, ensuring everyone has completed before reading the final value (`3`) and destroying the mutex.

---

## 🧪 Expected Output

```text
$ gcc main.c -lpthread
$ ./a.out
Thread 1: Waiting to enter critical section..
Thread 1: Entered critical section.
Thread 1: Incremented counter to 1
Thread 2: Waiting to enter critical section..
Thread 3: Waiting to enter critical section..
Thread 1: Exiting critical section.
Thread 2: Entered critical section.
Thread 2: Incremented counter to 2
Thread 2: Exiting critical section.
Thread 3: Entered critical section.
Thread 3: Incremented counter to 3
Thread 3: Exiting critical section.
Final value of shared counter: 3
```

---

## 💡 Viva Questions & Key Takeaways

1. **What is a Critical Section in operating systems?**
   - A critical section is a section of code that accesses shared resources (such as common variables or files) that must not be concurrently accessed by more than one process or thread.
2. **What three conditions must any valid solution to the critical-section problem satisfy?**
   - **Mutual Exclusion:** Only one process can execute in its critical section at a time.
   - **Progress:** If no process is in its critical section and others want to enter, selection cannot be postponed indefinitely.
   - **Bounded Waiting:** There must be a limit on the number of times other processes are allowed to enter their critical sections after a process has made a request to enter.
3. **What is the difference between a Mutex and a Binary Semaphore?**
   - A Mutex has the concept of **ownership**: only the thread that locked the mutex can unlock it. A semaphore has no ownership; any thread can signal (`sem_post`) or wait (`sem_wait`).
