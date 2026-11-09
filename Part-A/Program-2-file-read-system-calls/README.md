# Part A - Program 2: Read Contents of a File using Unix System Calls

## 📝 Official Exam Question
**Write a C program that uses the appropriate Unix system calls to read the contents of a file and display it on the terminal. The program should prompt the user to enter the filename as input from the keyboard.**

---

## 🎯 Aim & Objective
Write a C program that uses low-level POSIX/Unix system calls (`open`, `read`, `write`, `close`) to read the contents of a file and display them on standard output (terminal). The program prompts the user to enter the filename from standard input.

---

## 📦 Required System Calls & Headers

| Header | System Call / Function | Purpose |
|---|---|---|
| `<fcntl.h>` | `open(path, O_RDONLY)` | Opens the file descriptor in read-only mode |
| `<unistd.h>` | `read(fd, buf, count)` | Reads raw bytes from file descriptor into memory buffer |
| `<unistd.h>` | `write(fd, buf, count)` | Writes raw bytes directly to terminal (`STDOUT_FILENO`) |
| `<unistd.h>` | `close(fd)` | Releases the file descriptor back to the OS table |
| `<stdio.h>` | `fflush(stdout)`, `perror()` | Flushes user-space buffered streams and prints error strings |

---

## 📂 Files in this Experiment

- [`main.c`](./main.c) - Low-level I/O system call implementation
- [`contents.txt`](./contents.txt) - Sample input file containing `Hello World`

---

## 🛠 Compilation & Execution Instructions

```bash
# 1. Compile the program
gcc main.c -o main

# 2. Case A: Read existing file
./main
Enter filename: contents.txt
file contents:
Hello World

# 3. Case B: Attempt reading non-existent file
./main
Enter filename: cont.txt
Error: No such file or directory
```

---

## 🔍 Code Walkthrough

1. **`open(fname, O_RDONLY)`:**
   - Requests the kernel to locate the file inode, verify read permissions, and return the lowest unused integer file descriptor (`fd >= 3`).
   - If the file is not found, it returns `-1` and sets `errno`.
2. **`fflush(stdout)`:**
   - Standard C I/O (`printf`) is buffered in user space. Before switching to low-level unbuffered system calls (`write`), `fflush(stdout)` clears the standard I/O buffer to prevent interleaved or out-of-order text rendering.
3. **`read(fd, buffer, sizeof(buffer))` in a loop:**
   - Reads up to `sizeof(buffer)` bytes at a time.
   - Returns number of bytes read (`> 0`), `0` on End of File (EOF), or `-1` on error.
4. **`write(STDOUT_FILENO, buffer, n)`:**
   - Emits exactly `n` bytes directly to file descriptor 1 (`STDOUT_FILENO`).
5. **`close(fd)`:**
   - Closes the descriptor, flushing kernel state and preventing descriptor leaks.

---

## 🧪 Expected Output

```text
$ gcc main.c
$ ./a.out
Enter filename: contents.txt
file contents:
Hello World

$ ./a.out
Enter filename: cont.txt
Error: No such file or directory
```

---

## 💡 Viva Questions & Key Takeaways

1. **What is the difference between system calls (`read`, `write`, `open`) and standard library functions (`fread`, `fwrite`, `fopen`)?**
   - System calls transition execution from User Mode to Kernel Mode via software interrupts/traps and operate without user-space buffering. Standard library functions are built on top of system calls and maintain user-space buffers (via `FILE *`) for efficiency.
2. **What does `read()` return at End of File (EOF)?**
   - It returns `0`.
3. **What are file descriptors 0, 1, and 2?**
   - `0` is Standard Input (`STDIN_FILENO`), `1` is Standard Output (`STDOUT_FILENO`), and `2` is Standard Error (`STDERR_FILENO`).
