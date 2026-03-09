#include <stdio.h>

int main() {
    int n, i, time = 0, smallest;
    int at[20], bt[20], bt_copy[20], ct[20], tat[20], wt[20];
    int completed = 0, min_bt;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++){
        printf("\nProcess P%d\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        bt_copy[i] = bt[i];
    }

    while(completed != n){
        smallest = -1;
        min_bt = 9999;

        for(i = 0; i < n; i++){
            if(at[i] <= time && bt[i] > 0 && bt[i] < min_bt){
                min_bt = bt[i];
                smallest = i;
            }
        }

        if(smallest == -1){
            time++;
            continue;
        }

        bt[smallest]--;
        time++;

        if(bt[smallest] == 0){
            completed++;
            ct[smallest] = time;
        }
    }

    for(i = 0; i < n; i++){
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt_copy[i];

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1, at[i], bt_copy[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", avg_tat/n);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt/n);

    return 0;
}
