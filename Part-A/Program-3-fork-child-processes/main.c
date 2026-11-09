#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * Part A - Program 3: Create five child processes using fork()
 *
 * Exam Question:
 * Write the program to create five Child Processes using system call fork()
 * and display their ids.
 */

int main()
{
    int i;
    pid_t pid;

    for (i = 1; i <= 5; i++) {
        /* flush so the child does not copy unflushed output */
        fflush(stdout);

        pid = fork();

        if (pid < 0) {
            printf("Error ");
            return 1;
        } else if (pid == 0) {
            printf("Child %d with id %d and Parent Process id %d\n",
                   i, getpid(), getppid());
            exit(0);
        } else {
            printf("Parent Created Child %d with pid %d\n",
                   i, pid);
        }
    }

    for (i = 1; i <= 5; i++) {
        wait(NULL);
    }

    printf("Parent pid %d after finishing all Child execution\n",
           getpid());

    return 0;
}
