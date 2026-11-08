# Experiment B4: Producer-Consumer Problem Simulation

## 🎯 Aim & Objective
Write a C program to simulate the classic **Producer-Consumer Problem** (Bounded Buffer Problem). The program maintains a fixed-capacity circular buffer and allows interactive, menu-driven testing of buffer bounds:
1. Producer adds items until the buffer is full (`it == bs`).
2. Consumer removes items until the buffer is empty (`it == 0`).
3. Circular pointers (`in` and `out`) advance using modular arithmetic `(index + 1) % bs`.

---

## 📦 Problem Architecture & Semaphores

In full multi-threaded concurrency, the bounded-buffer problem is solved with three semaphores:
- **`mutex` (binary semaphore initialized to 1):** Guarantees mutual exclusion when accessing the shared buffer.
- **`empty` (counting semaphore initialized to `bs`):** Tracks available empty slots.
- **`full` (counting semaphore initialized to `0`):** Tracks populated slots available for consumption.

This laboratory program models the state synchronization and boundary checks of the bounded buffer interactively.

---

## 📂 Files in this Experiment

- [`main.c`](./main.c) - Interactive bounded buffer producer-consumer implementation

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

1. **Variables:**
   - `bs`: Buffer capacity.
   - `buff[bs]`: Array representing the fixed-size circular memory buffer.
   - `it`: Item counter ($0 \le it \le bs$).
   - `in`: Write pointer index where the next produced item is inserted.
   - `out`: Read pointer index where the next consumed item is extracted.
2. **Producer Logic (Option 1):**
   - If `it == bs`: Displays `"Buffer is full"` and refuses insertion.
   - Otherwise: Reads item `pro`, saves to `buff[in]`, advances `in = (in + 1) % bs`, and increments `it++`.
3. **Consumer Logic (Option 2):**
   - If `it == 0`: Displays `"Buffer empty"` and refuses consumption.
   - Otherwise: Extracts `con = buff[out]`, advances `out = (out + 1) % bs`, and decrements `it--`.

---

## 🧪 Expected Output

```text
$ gcc main.c
$ ./a.out
Enter the buffer size:2

1.Producer
2.Consume
3.Exit
Enter the choice1
Enter the value2

1.Producer
2.Consume
3.Exit
Enter the choice1
Enter the value3

1.Producer
2.Consume
3.Exit
Enter the choice1
Buffer is full

1.Producer
2.Consume
3.Exit
Enter the choice2
Consumed item : 2

1.Producer
2.Consume
3.Exit
Enter the choice2
Consumed item : 3

1.Producer
2.Consume
3.Exit
Enter the choice2
Buffer empty

1.Producer
2.Consume
3.Exit
Enter the choice3
```

---

## 💡 Viva Questions & Key Takeaways

1. **What is the Producer-Consumer problem?**
   - A fundamental synchronization problem where one or more producers generate data items and place them into a shared buffer, while one or more consumers remove items from the buffer.
2. **What race conditions can arise without synchronization?**
   - **Buffer Overflow:** A producer writes into a full buffer, overwriting unread data.
   - **Buffer Underflow:** A consumer reads from an empty buffer or reads stale data twice.
   - **Data Corruption:** Both producer and consumer update pointers simultaneously without mutual exclusion.
3. **Why is modular arithmetic `(in + 1) % bs` used?**
   - To implement a **circular queue**, so that after reaching the last index `bs - 1`, the next element wraps around to index `0`, reusing released memory slots efficiently without shifting elements.
