#include <stdio.h>
#define MAX 10

typedef struct {
    int id;
    int arrival;
    int C;
    int D;
    int remaining;
    int completed;
} Process;

void check_feasibility(Process p[], int n) {
    float U = 0.0;

    for (int i = 0; i < n; i++) {
        U += (float)p[i].C / p[i].D;
    }
    printf("\nCPU Utilization: %.2f\n", U);

    if (U > 1.0)
        printf("Scheduling not feasible (deadlines may be missed)\n\n");
    else
        printf("Scheduling feasible\n\n");
}
void edf_schedule(Process p[], int n) {
    int t = 0, completed_count = 0;
    printf("Execution Timeline:\n\n");
    while (completed_count < n) {
        int idx = -1;
        int earliest_deadline = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= t && p[i].completed == 0) {
                if (p[i].D < earliest_deadline) {
                    earliest_deadline = p[i].D;
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            printf("Time %d: Idle\n", t);
            t++;
            continue;
        }

        printf("Time %d: Executing P%d\n", t, p[idx].id);
        p[idx].remaining--;
        if (p[idx].remaining == 0) {
            p[idx].completed = 1;
            completed_count++;
            printf("P%d completed at time %d\n", p[idx].id, t + 1);
        }
        t++;
    }
}

int main() {
    int n;
    Process p[MAX];
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess P%d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);
        printf("Execution Time (C): ");
        scanf("%d", &p[i].C);
        printf("Deadline (D): ");
        scanf("%d", &p[i].D);
        p[i].remaining = p[i].C;
        p[i].completed = 0;
    }
    check_feasibility(p, n);
    edf_schedule(p, n);

    return 0;
}


