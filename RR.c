#include <stdio.h>

int main()
{
    int n, tq, i, time = 0, remain, flag = 0;
    int at[10], bt[10], rt[10], ct[10], tat[10], wt[10];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    remain = n;

    for(i = 0; i < n; i++)
    {
        printf("\nEnter Arrival Time for P%d: ", i+1);
        scanf("%d", &at[i]);

        printf("Enter Burst Time for P%d: ", i+1);
        scanf("%d", &bt[i]);

        rt[i] = bt[i];
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    while(remain != 0)
    {
        flag = 0;

        for(i = 0; i < n; i++)
        {
            if(at[i] <= time && rt[i] > 0)
            {
                flag = 1;

                if(rt[i] <= tq)
                {
                    time += rt[i];
                    rt[i] = 0;
                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];

                    avg_wt += wt[i];
                    avg_tat += tat[i];

                    remain--;
                }
                else
                {
                    rt[i] -= tq;
                    time += tq;
                }
            }
        }

        if(flag == 0)
            time++;
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f", avg_tat);

    return 0;
}

