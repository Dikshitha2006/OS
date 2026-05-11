#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10


void calculateNeed(int need[MAX_P][MAX_R],
                   int max[MAX_P][MAX_R],
                   int allot[MAX_P][MAX_R],
                   int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}

void printMatrix(int mat[MAX_P][MAX_R], int n, int m, char name[])
{
    printf("\n%s Matrix:\n", name);

    for (int i = 0; i < n; i++)
    {
        printf("P%d : ", i);

        for (int j = 0; j < m; j++)
        {
            printf("%d ", mat[i][j]);
        }

        printf("\n");
    }
}

bool isSafe(int processes[],
            int avail[],
            int max[MAX_P][MAX_R],
            int allot[MAX_P][MAX_R],
            int n, int m)
{
    int need[MAX_P][MAX_R];

    calculateNeed(need, max, allot, n, m);

    bool finish[MAX_P] = {false};

    int safeSeq[MAX_P];

    int work[MAX_R];

    for (int i = 0; i < m; i++)
    {
        work[i] = avail[i];
    }

    int count = 0;

    while (count < n)
    {
        bool found = false;

        for (int p = 0; p < n; p++)
        {
            if (finish[p] == false)
            {
                int j;

                for (j = 0; j < m; j++)
                {
                    if (need[p][j] > work[j])
                        break;
                }

                if (j == m)
                {
                    for (int k = 0; k < m; k++)
                    {
                        work[k] += allot[p][k];
                    }

                    safeSeq[count++] = p;

                    finish[p] = true;

                    found = true;
                }
            }
        }

        if (found == false)
        {
            printf("\nSystem is NOT in safe state.\n");
            return false;
        }
    }

    printf("\nSystem is in SAFE state.");
    printf("\nSafe Sequence: ");

    for (int i = 0; i < n; i++)
    {
        printf("P%d ", safeSeq[i]);
    }

    printf("\n");

    return true;
}

void requestResources(int process,
                      int request[],
                      int avail[],
                      int max[MAX_P][MAX_R],
                      int allot[MAX_P][MAX_R],
                      int n, int m)
{
    int need[MAX_P][MAX_R];

    calculateNeed(need, max, allot, n, m);

    for (int i = 0; i < m; i++)
    {
        if (request[i] > need[process][i])
        {
            printf("\nERROR: Process exceeded maximum claim.\n");
            return;
        }
    }

    for (int i = 0; i < m; i++)
    {
        if (request[i] > avail[i])
        {
            printf("\nResources are not available. Process must wait.\n");
            return;
        }
    }
    for (int i = 0; i < m; i++)
    {
        avail[i] -= request[i];
        allot[process][i] += request[i];
        need[process][i] -= request[i];
    }

    int processes[MAX_P];

    for (int i = 0; i < n; i++)
    {
        processes[i] = i;
    }

    printf("\nAfter allocating request to P%d:\n", process);

    if (isSafe(processes, avail, max, allot, n, m))
    {
        printf("Request CAN be granted.\n");
    }
    else
    {
        printf("Request CANNOT be granted.\n");

        for (int i = 0; i < m; i++)
        {
            avail[i] += request[i];
            allot[process][i] -= request[i];
        }
    }
}

int main()
{
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int processes[MAX_P];

    for (int i = 0; i < n; i++)
    {
        processes[i] = i;
    }

    int max[MAX_P][MAX_R];
    int allot[MAX_P][MAX_R];
    int need[MAX_P][MAX_R];
    int avail[MAX_R];

    printf("\nEnter Allocation Matrix:\n");

    for (int i = 0; i < n; i++)
    {
        printf("For P%d:\n", i);

        for (int j = 0; j < m; j++)
        {
            scanf("%d", &allot[i][j]);
        }
    }
    printf("\nEnter Max Matrix:\n");

    for (int i = 0; i < n; i++)
    {
        printf("For P%d:\n", i);

        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");

    for (int i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }

    calculateNeed(need, max, allot, n, m);

    printMatrix(need, n, m, "Need");

    printf("\n--- Initial Safety Check ---\n");

    isSafe(processes, avail, max, allot, n, m);

    int reqCount;

    printf("\nEnter number of resource requests: ");
    scanf("%d", &reqCount);

    for (int r = 0; r < reqCount; r++)
    {
        int process;
        int request[MAX_R];

        printf("\nEnter process number for request %d: ", r + 1);
        scanf("%d", &process);

        printf("Enter request vector:\n");

        for (int i = 0; i < m; i++)
        {
            scanf("%d", &request[i]);
        }

        requestResources(process, request,
                         avail, max, allot,
                         n, m);
    }

    return 0;
}
