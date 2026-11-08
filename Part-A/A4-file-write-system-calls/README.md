# Experiment A4: File Write Using System Calls

## 🎯 Aim & Objective
Write a C program using POSIX system calls to open a target file for writing (creating it if it does not already exist, or truncating it if it does). The program continuously reads input entered from the keyboard via file descriptor 0 (`stdin`) and writes it into the file until the user signals End of File (`Ctrl+D`).

---

## 📦 Required System Calls & Headers

| Header | System Call / Constant | Purpose |
|---|---|---|
| `<fcntl.h>` | `open()`, `O_CREAT`, `O_WRONLY`, `O_TRUNC` | Creates/opens the file with write permissions and truncates old content |
| `<fcntl.h>` | `0644` | File mode: read/write for owner (`rw-`), read-only for group/others (`r--`) |
| `<unistd.h>` | `read(0, buffer, size)` | Reads data from standard input (`fd = 0`) |
| `<unistd.h>` | `write(fd, buffer, n)` | Writes `n` bytes directly to the opened file |
| `<unistd.h>` | `close(fd)` | Flushes kernel dirty blocks and closes descriptor |

---

## 📂 Files in this Experiment

- [`main.c`](./main.c) - Low-level file creation and writing implementation

---

## 🛠 Compilation & Execution Instructions

```bash
# 1. Compile the program
gcc main.c -o main

# 2. Run the executable
./main
Enter the filename to be written
contents.txt
Enter the contents to be written
hello world
<press Enter, then press Ctrl+D>
Contents written to contents.txt

# 3. Verify file contents
cat contents.txt
hello world
```

---

## 🔍 Code Walkthrough

1. **`open(fname, O_CREAT | O_WRONLY | O_TRUNC, 0644)`:**
   - `O_CREAT`: If the file doesn't exist, create it with permissions specified in mode `0644` (modified by umask).
   - `O_WRONLY`: Open file strictly for writing.
   - `O_TRUNC`: If the file already exists, discard all previous contents (truncate length to 0).
2. **`read(0, buffer, sizeof(buffer))` in loop:**
   - Reads directly from file descriptor 0 (`stdin`).
   - When the user presses `Ctrl+D` at the beginning of a line in the terminal, the terminal driver sends an EOF marker, causing `read()` to return `0`.
3. **Loop Exit and Closure:**
   - On receiving `0`, the loop breaks.
   - `close(fd)` synchronizes file system state and closes the handle.

---

## 🧪 Expected Output

```text
$ gcc main.c
$ ./a.out
Enter the filename to be written 
contents.txt
Enter the contents to be written 
hello world
Contents written to contents.txt

$ cat contents.txt
hello world
```

---

## 💡 Viva Questions & Key Takeaways

1. **What is the meaning of the octal permission `0644` in `open()`?**
   - The leading `0` indicates octal notation. `6` (`4+2`) gives Read & Write to the file owner; `4` gives Read-only to group members; `4` gives Read-only to all other users.
2. **How does standard input detect `Ctrl+D`?**
   - In canonical terminal mode, pressing `Ctrl+D` transmits whatever is in the input queue or immediately signals EOF if the buffer is empty, causing `read(0, ...)` to return `0`.
3. **What is the difference between `O_TRUNC` and `O_APPEND`?**
   - `O_TRUNC` resets file length to 0 upon opening, overwriting old data. `O_APPEND` places the file offset at the end of the file before every write, preserving existing data.
