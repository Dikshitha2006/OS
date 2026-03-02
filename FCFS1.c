#include <stdio.h>

int main() {
    int n, i;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n], rt[n];
    float total_tat = 0, total_wt = 0;

    // Input Arrival Time and Burst Time
    for(i = 0; i < n; i++) {
        printf("\nProcess P%d\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    int time = 0;

    // FCFS Scheduling
    for(i = 0; i < n; i++) {

        // If CPU is idle
        if(time < at[i]) {
            time = at[i];
        }

        rt[i] = time - at[i]; // Response Time
        time += bt[i];
        ct[i] = time; // Completion Time
        tat[i] = ct[i] - at[i]; // Turnaround Time
        wt[i] = tat[i] - bt[i]; // Waiting Time

        total_tat += tat[i];
        total_wt += wt[i];
    }

    // Output Table
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat/n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt/n);

    return 0;
}
