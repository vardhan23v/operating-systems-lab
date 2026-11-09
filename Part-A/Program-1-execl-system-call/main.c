#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Part A - Program 1: execl() system call
 *
 * Exam Question:
 * Write a C program using the execl() system call that:
 * i. Reads the name of a shell script from the keyboard.
 * ii. Executes that script using /bin/sh.
 * iii. Displays an appropriate error message if the script cannot be found or executed.
 * iv. The shell script should prompt the user to enter three numbers, find and display the greatest of the three numbers.
 */

int main() {
    char sname[100];

    printf("Enter shell script name: ");
    if (scanf("%99s", sname) != 1) {
        fprintf(stderr, "Error reading script name\n");
        return 1;
    }

    /* the script must exist and be readable */
    if (access(sname, R_OK) == -1) {
        perror("Error: cannot open script");
        return 1;
    }

    /* execute the script using /bin/sh */
    if (execl("/bin/sh", "sh", sname, (char *)NULL) == -1) {
        perror("Error: cannot execute script");
        return 1;
    }

    return 0;
}
