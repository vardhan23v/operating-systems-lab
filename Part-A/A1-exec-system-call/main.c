#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Experiment No. A1: exec() system call
 *
 * Aim:
 * Write a C program using exec() system call:
 * a) Read the name of the shell script from the keyboard
 * b) Execute that script using /bin/sh
 * c) Display an appropriate error message if the script cannot be found or executed
 * d) The shell script should prompt the user to enter 3 numbers, find and display the greatest of 3 numbers
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
