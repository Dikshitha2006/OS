#include <stdio.h>

struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    int weight;
    int completed;
};

int main() {
    struct Process p[20];
    int n, i;
    int total_weight = 0;
    int completed = 0;
    int time_quantum;
    int time_slice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Time Quantum: ");
    scanf("%d", &time_quantum);

    for (i = 0; i < n; i++) {
        p[i].id = i + 1;

        printf("\nEnter arrival time for P%d: ", i + 1);
        scanf("%d", &p[i].arrival);

        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &p[i].burst);

        printf("Enter weight for P%d: ", i + 1);
        scanf("%d", &p[i].weight);

        p[i].remaining = p[i].burst;
        p[i].completed = 0;

        total_weight += p[i].weight;
    }

    printf("\nExecution Order:\n");

    while (completed < n) {
        int executed = 0;

        for (i = 0; i < n; i++) {
            if (p[i].completed == 0) {
                time_slice = (p[i].weight * time_quantum) / total_weight;

                if (time_slice <= 0)
                    time_slice = 1;

                if (time_slice > p[i].remaining)
                    time_slice = p[i].remaining;

                printf("P%d runs for %d units\n", p[i].id, time_slice);

                p[i].remaining -= time_slice;
                executed = 1;

                if (p[i].remaining <= 0) {
                    p[i].completed = 1;
                    completed++;
                    total_weight -= p[i].weight;
                    printf("P%d completed\n", p[i].id);
                }
            }
        }

        if (executed == 0)
            break;
    }

    return 0;
}
