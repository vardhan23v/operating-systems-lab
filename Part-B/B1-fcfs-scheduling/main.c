#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * Experiment No. B1: FCFS scheduling
 *
 * Aim:
 * Write a C program to implement First Come First Serve scheduling algorithm
 * to determine total waiting time and average waiting time, total turn around
 * time and average turn around time.
 */

struct Process
{
    int pid, bt, wt, tat;
};

int main()
{
    int n, i;
    double awt = 0, atat = 0;

    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (n <= 0)
    {
        printf("Number of processes must be positive\n");
        return 1;
    }

    struct Process P[n];

    for (i = 0; i < n; i++)
    {
        P[i].pid = i + 1;
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &P[i].bt);
    }

    /* First process has 0 waiting time */
    P[0].wt = 0;
    P[0].tat = P[0].bt + P[0].wt;

    /* Calculate waiting time and turnaround time for subsequent processes */
    for (i = 1; i < n; i++)
    {
        P[i].wt = P[i - 1].wt + P[i - 1].bt;
        P[i].tat = P[i].bt + P[i].wt;
    }

    printf("\n Process BT\t WT\t TAT\t");
    for (i = 0; i < n; i++)
    {
        printf("\n %d\t %d\t %d\t %d ", P[i].pid, P[i].bt, P[i].wt, P[i].tat);
    }

    for (i = 0; i < n; i++)
    {
        awt += P[i].wt;
        atat += P[i].tat;
    }

    printf("\n\nTotal Waiting Time = %.2f\n", awt);
    printf("Average Waiting Time = %.2f\n", awt / n);
    printf("Total Turn Around Time = %.2f\n", atat);
    printf("Average Turn Around Time = %.2f\n", atat / n);

    return 0;
}
