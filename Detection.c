#include <stdio.h>

#define P 5
#define R 3
int main()
{

    int allocation[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 3},
        {2, 1, 1},
        {0, 0, 2}
    };

    int request[P][R] = {
        {0, 0, 0},
        {2, 0, 2},
        {0, 0, 1},
        {1, 0, 0},
        {0, 0, 2}
    };


    int available[R] = {0, 0, 0};

    int work[R];
    int finish[P];

    int i, j;


    for (j = 0; j < R; j++)
    {
        work[j] = available[j];
    }


    for (i = 0; i < P; i++)
    {
        int zero = 1;

        for (j = 0; j < R; j++)
        {
            if (allocation[i][j] != 0)
            {
                zero = 0;
                break;
            }
        }

        if (zero)
            finish[i] = 1;
        else
            finish[i] = 0;
    }

    int found;

    do
    {
        found = 0;

        for (i = 0; i < P; i++)
        {

            if (finish[i] == 0)
            {
                int possible = 1;

                for (j = 0; j < R; j++)
                {
                    if (request[i][j] > work[j])
                    {
                        possible = 0;
                        break;
                    }
                }


                if (possible)
                {
                    printf("Process P%d can complete.\n", i);

                    for (j = 0; j < R; j++)
                    {
                        work[j] += allocation[i][j];
                    }

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

    } while (found);

    int deadlock = 0;

    for (i = 0; i < P; i++)
    {
        if (finish[i] == 0)
        {
            deadlock = 1;
            printf("Process P%d is deadlocked.\n", i);
        }
    }

    if (deadlock)
        printf("\nSystem is in Deadlock State.\n");
    else
        printf("\nSystem is NOT in Deadlock State.\n");

    return 0;
}
