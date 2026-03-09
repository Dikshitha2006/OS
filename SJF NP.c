#include <stdio.h>

int main() {
    int n, i, j, time = 0, smallest;
    int at[20], bt[20], ct[20], tat[20], wt[20];
    int done[20] = {0};
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++){
        printf("\nProcess P%d\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    for(i = 0; i < n; i++){
        smallest = -1;

        for(j = 0; j < n; j++){
            if(at[j] <= time && done[j] == 0){
                if(smallest == -1 || bt[j] < bt[smallest])
                    smallest = j;
            }
        }

        if(smallest == -1){
            time++;
            i--;
            continue;
        }

        time += bt[smallest];
        ct[smallest] = time;
        done[smallest] = 1;
    }

    for(i = 0; i < n; i++){
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", avg_tat/n);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt/n);

    return 0;
}
