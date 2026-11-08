#include <stdio.h>
#include <stdlib.h>

/**
 * Experiment No. B4: Producer-Consumer using semaphores
 *
 * Aim:
 * Write a C program to simulate the producer-consumer problem using semaphores.
 */

int main() {
    int bs, ch, con, pro, it = 0, in = 0, out = 0;

    printf("Enter the buffer size:");
    if (scanf("%d", &bs) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (bs <= 0) {
        printf("Buffer size must be positive\n");
        return 1;
    }

    int buff[bs];

    while (1) {
        printf("\n1.Producer\n2.Consume\n3.Exit\n");
        printf("Enter the choice");
        if (scanf("%d", &ch) != 1) {
            printf("Invalid input\n");
            break;
        }

        switch (ch) {
            case 1:
                if (it == bs) {
                    printf("Buffer is full");
                }
                else {
                    printf("Enter the value");
                    scanf("%d", &pro);
                    buff[in] = pro;
                    in = (in + 1) % bs;
                    it++;
                }
                break;

            case 2:
                if (it == 0) {
                    printf("Buffer empty");
                }
                else {
                    con = buff[out];
                    printf("Consumed item : %d", con);
                    it--;
                    out = (out + 1) % bs;
                }
                break;

            case 3:
                exit(0);

            default:
                printf("Invalid choice");
        }
    }

    return 0;
}
