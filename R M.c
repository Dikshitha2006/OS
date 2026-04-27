#include <stdio.h>
#include <math.h>
#define MAX_TASKS 10


typedef struct {
    int id;
    int C;
    int T;
    int remaining_time;
    int next_arrival;
} Task;


void check_schedulability(Task tasks[], int n) {
    double U = 0.0;

    for (int i = 0; i < n; i++) {
        U += (double)tasks[i].C / tasks[i].T;
    }

    double bound = n * (pow(2, 1.0/n) - 1);

    printf("CPU Utilization: %.4f\n", U);
    printf("RMS Bound: %.4f\n", bound);

    if (U <= bound) {
        printf("Schedulable using RMS\n\n");
    } else {
        printf("Not guaranteed schedulable (need further analysis)\n\n");
    }
}


void sort_tasks(Task tasks[], int n) {
    Task temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (tasks[i].T > tasks[j].T) {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}


void rms_schedule(Task tasks[], int n, int simulation_time) {
    int time = 0;

    printf("Scheduling Timeline:\n\n");

    while (time < simulation_time) {
        int highest = -1;


        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_arrival) {
                tasks[i].remaining_time = tasks[i].C;
                tasks[i].next_arrival += tasks[i].T;
            }
        }


        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                highest = i;
                break;
            }
        }

        if (highest != -1) {
            printf("Time %d: Executing T%d\n", time, tasks[highest].id);
            tasks[highest].remaining_time--;
        } else {
            printf("Time %d: Idle\n", time);
        }

        time++;
    }
}

int main() {
    int n = 3;

    Task tasks[MAX_TASKS] = {
        {1, 1, 4, 0, 0},
        {2, 2, 5, 0, 0},
        {3, 1, 10, 0, 0}
    };

    check_schedulability(tasks, n);

    sort_tasks(tasks, n);

    rms_schedule(tasks, n, 20);

    return 0;
}



