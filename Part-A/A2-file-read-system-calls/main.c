#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * Experiment No. A2: File read using system calls
 *
 * Aim:
 * Write a C program that uses appropriate unique system calls to read the
 * contents of the file and display it on the terminal. The program should
 * prompt the user to enter the filename as input from the keyboard.
 */

int main()
{
    char fname[100], buffer[100];
    int fd;
    ssize_t n;

    printf("Enter filename: ");
    if (scanf("%99s", fname) != 1) {
        fprintf(stderr, "Error reading filename\n");
        return 1;
    }

    fd = open(fname, O_RDONLY);
    if (fd == -1)
    {
        perror("Error");
        return 1;
    }

    printf("file contents:\n");
    /* flush stdio before using write() directly */
    fflush(stdout);

    /* keep reading until end of file */
    while ((n = read(fd, buffer, sizeof(buffer))) > 0)
    {
        if (write(STDOUT_FILENO, buffer, n) != n)
        {
            perror("Error");
            break;
        }
    }

    if (n == -1)
        perror("Error");

    close(fd);
    return 0;
}
