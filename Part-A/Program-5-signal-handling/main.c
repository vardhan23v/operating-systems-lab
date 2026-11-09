#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/**
 * Part A - Program 5: Signal handler for SIGINT, SIGTERM, SIGHUP, SIGALRM, and SIGUSR1
 *
 * Exam Question:
 * Write a C program that registers a signal handler for SIGINT, SIGTERM,
 * SIGHUP, SIGALRM, and SIGUSR1. The handler should receive each signal
 * and perform some operation.
 */

void signalhandler(int sig)
{
    if (sig == SIGINT)
    {
        printf("Caught an Interrupt Signal\n");
    }
    if (sig == SIGTERM)
    {
        printf("Caught a Terminate Signal\n");
        exit(0);
    }
    if (sig == SIGHUP) {
        printf("Caught a Hangup Signal\n");
    }
    if (sig == SIGUSR1)
    {
        printf("Caught a User Signal\n");
    }
    if (sig == SIGALRM)
    {
        printf("Caught an Alarm Signal\n");
    }
}

int main()
{
    /* Register custom signal handler for 5 different signals */
    signal(SIGINT, signalhandler);
    signal(SIGTERM, signalhandler);
    signal(SIGHUP, signalhandler);
    signal(SIGALRM, signalhandler);
    signal(SIGUSR1, signalhandler);

    /* Schedule SIGALRM to fire after 20 seconds */
    alarm(20);

    printf("Process Id of program running = %d\n", getpid());

    while (1)
    {
        printf("Waiting for signal\n");
        sleep(5);
    }

    return 0;
}
