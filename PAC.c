#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int buffer[SIZE];
int top = -1;
int item = 0;

void produce() {
    if (top == SIZE - 1) {
        printf("Buffer is full!\n");
    } else {
        item++;
        buffer[++top] = item;
        printf("Producer has produced: Item %d\n", item);
    }
}

void consume() {
    if (top == -1) {
        printf("Buffer is empty!\n");
    } else {
        printf("Consumer has consumed: Item %d\n", buffer[top]);
        top--;
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nEnter\n1. Producer\n2. Consumer\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                produce();
                break;

            case 2:
                consume();
                break;

            case 3:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

