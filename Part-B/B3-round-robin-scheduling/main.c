#include <stdio.h>
#include <stdlib.h>

/**
 * Experiment No. B3: Round Robin scheduling
 *
 * Aim:
 * Write a C program to implement Round Robin scheduling algorithm to determine
 * total waiting time, total turn around time, average waiting time,
 * average turn around time.
 */

struct Process
{
    int pid, bt, wt, tt;
};

int main()
{
    int i, n, tq, time = 0, totwt = 0, tottt = 0, flag = 0;
    float avgwt, avgtt;

    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (n <= 0)
    {
        printf("Number of processes must be positive\n");
        return 1;
    }

    struct Process p[n];
    int remBT[n];

    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Enter burst time for p%d : ", i + 1);
        scanf("%d", &p[i].bt);
        remBT[i] = p[i].bt;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &tq);

    if (tq <= 0)
    {
        printf("Time quantum must be positive\n");
        return 1;
    }

    /* Round Robin simulation loop */
    while (flag == 0)
    {
        flag = 1;
        for (i = 0; i < n; i++)
        {
            if (remBT[i] > 0)
            {
                flag = 0; /* There are still unfinished processes */
                if (remBT[i] > tq)
                {
                    time = time + tq;
                    remBT[i] = remBT[i] - tq;
                }
                else
                {
                    time = time + remBT[i];
                    remBT[i] = 0;
                    p[i].tt = time;               /* Turnaround time is total elapsed time until completion */
                    p[i].wt = p[i].tt - p[i].bt;  /* Waiting time = Turnaround time - Burst time */
                }
            }
        }
    }

    printf("\nProcess BT\t WT\t TAT ");
    for (i = 0; i < n; i++)
    {
        printf("\n %d\t %d\t %d\t %d ", p[i].pid, p[i].bt, p[i].wt, p[i].tt);
        totwt = totwt + p[i].wt;
        tottt = tottt + p[i].tt;
    }

    avgwt = (float)totwt / n;
    avgtt = (float)tottt / n;

    printf("\nTotal Waiting Time: %d ms\nAverage Waiting Time: %.2f ms\n",
           totwt, avgwt);
    printf("Total Turn Around Time: %d ms\nAverage Turn Around Time: %.2f ms\n",
           tottt, avgtt);

    return 0;
}
