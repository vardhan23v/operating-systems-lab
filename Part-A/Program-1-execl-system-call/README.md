# Part A - Program 1: `execl()` System Call

## 📝 Official Exam Question
**Write a C program using the `execl()` system call that:**
- **i.** Reads the name of a shell script from the keyboard.
- **ii.** Executes that script using `/bin/sh`.
- **iii.** Displays an appropriate error message if the script cannot be found or executed.
- **iv.** The shell script should prompt the user to enter three numbers, find and display the greatest of the three numbers.

---

## 🎯 Aim & Objective
Demonstrate process image replacement using the `execl()` POSIX system call:
1. Read the name of a shell script from standard input (`stdin`).
2. Verify that the specified script exists and has read permissions using the `access()` system call.
3. Replace the calling process image with `/bin/sh` via `execl()` to execute the script.
4. Display an appropriate error message using `perror()` if the script cannot be found or executed.
5. Provide a companion shell script (`largest.sh`) that prompts the user to enter 3 numbers, determines the greatest among them, and prints the result.

---

## 📦 Required System Calls & Headers

| Header | System Call / Function | Purpose |
|---|---|---|
| `<unistd.h>` | `execl()` | Replaces current process image with `/bin/sh` executing the script |
| `<unistd.h>` | `access()` | Checks file accessibility for existence (`F_OK`) and read permission (`R_OK`) |
| `<stdio.h>` | `printf()`, `scanf()`, `perror()` | Standard input/output and system error reporting |
| `<stdlib.h>` | `exit()` | Process termination status |

---

## 📂 Files in this Experiment

- [`main.c`](./main.c) - C program utilizing `access()` and `execl()`
- [`largest.sh`](./largest.sh) - Bash shell script to find the greatest of three numbers

---

## 🛠 Compilation & Execution Instructions

```bash
# 1. Ensure the shell script has executable permissions
chmod +x largest.sh

# 2. Compile the C source code
gcc main.c -o main

# 3. Case A: Run with valid script
./main
Enter shell script name: largest.sh
Enter 3 numbers: 3 4 2
4 is the greatest

# 4. Case B: Run with non-existent script
./main
Enter shell script name: large.sh
Error: cannot open script: No such file or directory
```

---

## 🔍 Code Walkthrough

### C Host Program (`main.c`)
- `access(sname, R_OK)`: Tests if the file exists and is readable by the real user ID. If it returns `-1`, `perror("Error: cannot open script")` outputs the specific system error (e.g., `No such file or directory`).
- `execl("/bin/sh", "sh", sname, (char *)NULL)`: Replaces the current process address space with `/bin/sh`. The arguments passed to `/bin/sh` are `arg0 = "sh"`, `arg1 = sname`, terminated with `(char *)NULL`.
- If `execl()` succeeds, it never returns. If it returns `-1`, execution failed, and `perror()` prints the diagnostic.

### Companion Script (`largest.sh`)
- `read -p "Enter 3 numbers: " a b c`: Reads three integer values into variables `a`, `b`, and `c`.
- `[ $a -ge $b ] && [ $a -ge $c ]`: Conditional check using `-ge` (greater than or equal to).
- Prints the largest number using `echo`.

---

## 🧪 Expected Output

```text
$ gcc main.c
$ ./a.out
Enter shell script name: largest.sh
Enter 3 numbers: 3 4 2
4 is the greatest

$ ./a.out
Enter shell script name: large.sh
Error: cannot open script: No such file or directory
```

---

## 💡 Viva Questions & Key Takeaways

1. **What is the purpose of the `exec()` family of system calls?**
   - The `exec()` family replaces the current process image (code, data, heap, and stack) with a new process image loaded from an executable file. The Process ID (`PID`) remains unchanged.
2. **Why does code after `execl()` not execute under normal conditions?**
   - Because once `execl()` succeeds, the entire memory image of the calling process is overwritten by the new program. Control only returns to the caller if an error occurs during the call.
3. **What is the difference between `execl()` and `execv()`?**
   - `execl()` takes command-line arguments as a comma-separated list terminated by `NULL`, whereas `execv()` takes arguments as an array (vector) of pointers to null-terminated strings (`char *argv[]`).
