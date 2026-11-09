#include <stdio.h>
#include <stdlib.h>

/**
 * Part B - Program 5: Banker's deadlock avoidance algorithm
 *
 * Exam Question:
 * Write a C program to demonstrate Bankers Deadlock avoidance algorithm.
 */

int main()
{
    int p, r, count = 0, found = 0, i, j;

    printf("Enter the number of processes:");
    if (scanf("%d", &p) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    printf("Enter the number of resources:");
    if (scanf("%d", &r) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (p <= 0 || r <= 0)
    {
        printf("Number of processes and resources must be positive\n");
        return 1;
    }

    int max[p][r], alloc[p][r], avail[r], need[p][r], finish[p], safeseq[p];

    printf("Enter the MAX matrix:\n");
    for (i = 0; i < p; i++) {
        for (j = 0; j < r; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Allocation matrix:\n");
    for (i = 0; i < p; i++) {
        for (j = 0; j < r; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the Available matrix:\n");
    for (i = 0; i < r; i++) {
        scanf("%d", &avail[i]);
    }

    printf("The Need matrix:\n");
    for (i = 0; i < p; i++) {
        for (j = 0; j < r; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d\t", need[i][j]);
        }
        finish[i] = 0;
        printf("\n");
    }

    /* Safety Algorithm */
    while (count < p) {
        found = 0; /* new pass: nobody has been found yet */
        for (i = 0; i < p; i++) {
            if (finish[i] == 0) {
                for (j = 0; j < r; j++) {
                    if (need[i][j] > avail[j])
                        break;
                }

                if (j == r) {
                    for (int k = 0; k < r; k++) {
                        avail[k] += alloc[i][k];
                    }
                    safeseq[count++] = i;
                    found = 1;
                    finish[i] = 1;
                }
            }
        }

        if (found == 0) {
            printf("System is in unsafe state\n");
            return 0;
        }
    }

    printf("System is in safe state\n");
    printf("Safe Sequence is:");
    for (int k = 0; k < p; k++) {
        printf(" P%d\t", safeseq[k] + 1);
    }
    printf("\n");

    return 0;
}
