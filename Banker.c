#include <stdio.h>
#include <stdbool.h>

#define P 5
#define R 3

void calculateNeed(int need[P][R], int max[P][R], int allot[P][R])
{
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];
}


bool isSafe(int processes[], int avail[], int max[][R], int allot[][R])
{
    int need[P][R];
    calculateNeed(need, max, allot);

    bool finish[P] = {false};
    int safeSeq[P];
    int work[R];


    for (int i = 0; i < R; i++)
        work[i] = avail[i];

    int count = 0;

    while (count < P)
    {
        bool found = false;

        for (int p = 0; p < P; p++)
        {

            if (finish[p] == false)
            {
                int j;


                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;


                if (j == R)
                {

                    for (int k = 0; k < R; k++)
                        work[k] += allot[p][k];

                    safeSeq[count++] = p;
                    finish[p] = true;

                    found = true;
                }
            }
        }


        if (found == false)
        {
            printf("System is NOT in safe state\n");
            return false;
        }
    }


    printf("System is in SAFE state.\nSafe sequence is: ");

    for (int i = 0; i < P; i++)
        printf("P%d ", safeSeq[i]);

    printf("\n");

    return true;
}


void requestResources(int process, int request[],
                      int avail[], int max[][R], int allot[][R])
{
    int need[P][R];
    calculateNeed(need, max, allot);

    printf("\nChecking request for P%d: (%d %d %d)\n",
           process, request[0], request[1], request[2]);

    for (int i = 0; i < R; i++)
    {
        if (request[i] > need[process][i])
        {
            printf("Error: Process exceeded maximum claim.\n");
            return;
        }
    }

    for (int i = 0; i < R; i++)
    {
        if (request[i] > avail[i])
        {
            printf("Resources not available. Process must wait.\n");
            return;
        }
    }

    for (int i = 0; i < R; i++)
    {
        avail[i] -= request[i];
        allot[process][i] += request[i];
        need[process][i] -= request[i];
    }

    int processes[] = {0, 1, 2, 3, 4};


    if (isSafe(processes, avail, max, allot))
    {
        printf("Request can be granted.\n");
    }
    else
    {
        printf("Request cannot be granted. Restoring old state.\n");

        for (int i = 0; i < R; i++)
        {
            avail[i] += request[i];
            allot[process][i] -= request[i];
        }
    }
}

int main()
{
    int processes[] = {0, 1, 2, 3, 4};

    int avail[R] = {3, 3, 2};

    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int allot[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    printf("Initial Safety Check:\n");
    isSafe(processes, avail, max, allot);

    int request[R] = {1, 0, 2};

    requestResources(1, request, avail, max, allot);

    return 0;
}
