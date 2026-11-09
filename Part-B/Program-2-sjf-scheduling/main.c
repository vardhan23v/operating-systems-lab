#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * Part B - Program 2: Shortest Job First (SJF) Scheduling algorithm
 *
 * Exam Question:
 * Write a C program to implement Shortest Job First Scheduling algorithm
 * to determine total waiting time, average waiting time, total turn around
 * time and average turnaround time.
 */

struct Process
{
    int pid, bt, wt, tat;
};

int main()
{
    int n, min;
    double awt = 0, atat = 0;

    printf("Enter no of process: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (n <= 0)
    {
        printf("Number of processes must be positive\n");
        return 1;
    }

    struct Process p[n], temp;

    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Enter burst time for p%d : ", i + 1);
        scanf("%d", &p[i].bt);
    }

    /* Selection sort to order processes by burst time (SJF) */
    for (int i = 0; i < n; i++)
    {
        min = i;
        for (int j = i + 1; j < n; j++)
        {
            /* equal burst times: keep arrival (pid) order */
            if (p[j].bt < p[min].bt ||
               (p[j].bt == p[min].bt && p[j].pid < p[min].pid))
            {
                min = j;
            }
        }
        temp = p[i];
        p[i] = p[min];
        p[min] = temp;
    }

    /* Calculate waiting time and turnaround time */
    p[0].wt = 0;
    p[0].tat = p[0].bt + p[0].wt;

    for (int i = 1; i < n; i++)
    {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
        p[i].tat = p[i].wt + p[i].bt;
    }

    printf("\nProcess BT\t WT\t TAT");
    for (int i = 0; i < n; i++)
    {
        printf("\n%d\t %d\t %d\t %d", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
    }

    for (int i = 0; i < n; i++)
    {
        awt += p[i].wt;
        atat += p[i].tat;
    }

    printf("\n\nTotal Waiting Time = %.2f\n", awt);
    printf("Total Turn Around Time = %.2f\n", atat);
    printf("Average Waiting Time = %.2f\n", awt / n);
    printf("Average Turn Around Time = %.2f\n", atat / n);

    return 0;
}
