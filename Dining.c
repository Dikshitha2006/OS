#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define MAX 10

sem_t chopstick[MAX];
sem_t room;

int n, hungry, pos[MAX];

void eat_one() {
    printf("\nAllow one philosopher to eat at any time\n");

    for (int i = 0; i < hungry; i++) {
        printf("P %d is waiting\n", pos[i]);
    }

    for (int i = 0; i < hungry; i++) {
        int p = pos[i] - 1;

        sem_wait(&room);
        sem_wait(&chopstick[p]);
        sem_wait(&chopstick[(p + 1) % n]);

        printf("P %d is granted to eat\n", pos[i]);
        printf("P %d has finished eating\n", pos[i]);

        sem_post(&chopstick[p]);
        sem_post(&chopstick[(p + 1) % n]);
        sem_post(&room);
    }
}

void eat_two() {
    printf("\nAllow two philosophers to eat at a time\n");

    for (int i = 0; i < hungry; i++) {
        printf("P %d is waiting\n", pos[i]);
    }

    for (int i = 0; i < hungry; i++) {
        int p = pos[i] - 1;

        if (sem_trywait(&room) == 0) {
            if (sem_trywait(&chopstick[p]) == 0 &&
                sem_trywait(&chopstick[(p + 1) % n]) == 0) {

                printf("P %d is granted to eat\n", pos[i]);
                printf("P %d has finished eating\n", pos[i]);

                sem_post(&chopstick[p]);
                sem_post(&chopstick[(p + 1) % n]);
                sem_post(&room);
            } else {
                printf("P %d is waiting\n", pos[i]);
            }
        }
    }
}

int main() {
    int choice;

    printf("Enter the total number of philosophers: ");
    scanf("%d", &n);

    printf("How many are hungry: ");
    scanf("%d", &hungry);

    for (int i = 0; i < hungry; i++) {
        printf("Enter philosopher %d position (1 to %d): ", i + 1, n);
        scanf("%d", &pos[i]);
    }

    // Initialize semaphores
    sem_init(&room, 0, n - 1);

    for (int i = 0; i < n; i++) {
        sem_init(&chopstick[i], 0, 1);
    }

    while (1) {
        printf("\n1. One can eat at a time");
        printf("\n2. Two can eat at a time");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                eat_one();
                break;
            case 2:
                eat_two();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}

