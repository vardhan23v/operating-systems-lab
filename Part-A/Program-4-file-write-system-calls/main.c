#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * Part A - Program 4: Open a file for writing until Ctrl+D using Unix system calls
 *
 * Exam Question:
 * Write a C program using Unix system calls to open a file for writing
 * (create it if it does not exist). The program should read text from the
 * keyboard and write it into file until Ctrl+D.
 */

int main()
{
    int fd;
    char buffer[1000], fname[100];

    printf("Enter the filename to be written \n");
    if (scanf("%99s", fname) != 1) {
        fprintf(stderr, "Error reading filename\n");
        return 1;
    }

    /* Open or create file with Read/Write permissions for owner, Read for others */
    fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
    {
        printf("Open error");
        return 0;
    }

    printf("Enter the contents to be written \n");

    while (1)
    {
        /* read raw bytes from standard input (file descriptor 0) */
        int n = read(0, buffer, sizeof(buffer));
        if (n > 0) {
            write(fd, buffer, n);
        }
        else if (n == 0) {
            /* Ctrl+D triggers EOF (0 bytes read) */
            break;
        }
        else {
            printf("Read error");
            close(fd);
            return 0;
        }
    }

    close(fd);
    printf("Contents written to %s\n", fname);
    return 0;
}
