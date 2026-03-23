#include <stdio.h>


struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};


void calculateFCFS(struct Process p[], int n, int startTime) {
    int currentTime = startTime;

    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].arrivalTime)
            currentTime = p[i].arrivalTime;

        p[i].completionTime = currentTime + p[i].burstTime;
        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;

        currentTime = p[i].completionTime;
    }
}


void display(struct Process p[], int n, char queueName[]) {
    printf("\n%s Queue:\n", queueName);
    printf("ID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               p[i].arrivalTime,
               p[i].burstTime,
               p[i].completionTime,
               p[i].turnaroundTime,
               p[i].waitingTime);
    }
}

int main() {
    int n, sysCount = 0, userCount = 0;

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    struct Process sys[n], user[n];

    for (int i = 0; i < n; i++) {
        int type;
        struct Process temp;

        printf("\nProcess %d:\n", i + 1);
        temp.id = i + 1;

        printf("Enter Arrival Time: ");
        scanf("%d", &temp.arrivalTime);

        printf("Enter Burst Time: ");
        scanf("%d", &temp.burstTime);

        printf("Enter Type (1 = System, 2 = User): ");
        scanf("%d", &type);

        if (type == 1) {
            sys[sysCount++] = temp;
        } else {
            user[userCount++] = temp;
        }
    }


    for (int i = 0; i < sysCount - 1; i++) {
        for (int j = i + 1; j < sysCount; j++) {
            if (sys[i].arrivalTime > sys[j].arrivalTime) {
                struct Process temp = sys[i];
                sys[i] = sys[j];
                sys[j] = temp;
            }
        }
    }


    for (int i = 0; i < userCount - 1; i++) {
        for (int j = i + 1; j < userCount; j++) {
            if (user[i].arrivalTime > user[j].arrivalTime) {
                struct Process temp = user[i];
                user[i] = user[j];
                user[j] = temp;
            }
        }
    }


    calculateFCFS(sys, sysCount, 0);


    int lastTime = 0;
    if (sysCount > 0)
        lastTime = sys[sysCount - 1].completionTime;


    calculateFCFS(user, userCount, lastTime);


    display(sys, sysCount, "System");
    display(user, userCount, "User");

    return 0;
}
