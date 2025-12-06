#include <stdio.h>
#include <stdlib.h>

int bankers();
int safe_state(int use_temp, int start);
int resource_request(int num, int array[]);
int in_array(int num, int array[]);
int verify(int lower_bound, int upper_bound);

int n = 5;
int m = 3;
int available[3] = {3, 3, 2};
int max[5][3] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}};
int allocation[5][3] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}};
int need[5][3] = {
    {7, 4, 3},
    {1, 2, 2},
    {6, 0, 0},
    {0, 1, 1},
    {4, 3, 1}};
int temp_available[3];
int temp_allocation[5][3];
int temp_need[5][3];
int temp_max[5][3];

int main()
{
    // printing inital values
    printf("n = %d # Number of processes\n", n);
    printf("m = %d # Number of resource types\n\n", m);
    printf("# Available Vector (initially total resources available)\nAvailable = [");
    for (int i = 0; i < 3; i++)
    {
        if (i == 2)
        {
            printf("%d]\n\n", available[i]);
        }
        else
        {
            printf("%d, ", available[i]);
        }
    }
    printf("# Maximum Matrix\nMax = [\n");
    for (int i = 0; i < 5; i++)
    {
        printf("    [");
        for (int j = 0; j < 3; j++)
        {
            if (i != 4)
            {
                if (j == 2)
                {
                    printf("%d],\n", max[i][j]);
                }
                else
                {
                    printf("%d, ", max[i][j]);
                }
            }
            else
            {
                if (j == 2)
                {
                    printf("%d]\n]\n\n", max[i][j]);
                }
                else
                {
                    printf("%d, ", max[i][j]);
                }
            }
        }
    }
    printf("# Allocation Matrix\nAllocation = [\n");
    for (int i = 0; i < 5; i++)
    {
        printf("    [");
        for (int j = 0; j < 3; j++)
        {
            if (i != 4)
            {
                if (j == 2)
                {
                    printf("%d],\n", allocation[i][j]);
                }
                else
                {
                    printf("%d, ", allocation[i][j]);
                }
            }
            else
            {
                if (j == 2)
                {
                    printf("%d]\n]\n\n", allocation[i][j]);
                }
                else
                {
                    printf("%d, ", allocation[i][j]);
                }
            }
        }
    }
    printf("# Need Matrix (Max - Allocation)\nNeed = [\n");
    for (int i = 0; i < 5; i++)
    {
        printf("    [");
        for (int j = 0; j < 3; j++)
        {
            if (i != 4)
            {
                if (j == 2)
                {
                    printf("%d],\n", need[i][j]);
                }
                else
                {
                    printf("%d, ", need[i][j]);
                }
            }
            else
            {
                if (j == 2)
                {
                    printf("%d]\n]\n\n", need[i][j]);
                }
                else
                {
                    printf("%d, ", need[i][j]);
                }
            }
        }
    }
    // done printing initial values
    // running bankers algo
    bankers();

    return 0;
}

int bankers()
{
    // bankers algo
    while (1)
    {
        printf("Banker's Algorithm Test Menu:\n");
        printf("1. Check for safe sequence\n");
        printf("2. User-defined resource request\n");
        printf("3. Exit\n");

        // getting choice
        int choice = verify(1, 3);

        // checks for safe state
        if (choice == 1)
        {
            printf("\nTest case 1: Run safe test:\n");
            safe_state(0, 0);
        }

        // runs resource request
        else if (choice == 2)
        {
            int choice2 = verify(0, 4);
            printf("Enter the resource request for process %d (format: r1 r2 r3): ", choice2);
            int r1;
            int r2;
            int r3;
            scanf("%d %d %d", &r1, &r2, &r3);
            printf("# Process %d requests resources [%d, %d, %d]\n", choice2, r1, r2, r3);
            printf("request = [%d, %d, %d]\n", r1, r2, r3);
            int request[3] = {r1, r2, r3};
            printf("request_resources(%d, request)\n", choice2);
            resource_request(choice2, request);
        }

        // exits the program
        else
        {
            printf("Exiting...\n");
            return 2;
        }
    }
}

int safe_state(int use_temp, int start)
{
    // checks safe state with a request
    if (use_temp == 1)
    {
        int safe_sequence[5] = {-1, -1, -1, -1, -1};
        int loops_without_success = 0;
        int position = start - 1;
        int pass = 1;
        int safe_position = 0;
        int func_available[3];
        for (int i = 0; i < 3; i++)
        {
            func_available[i] = temp_available[i];
        }

        // loops until it is only failing
        while (loops_without_success < 12)
        {
            // when everything is complete say safe and exit
            if (safe_position == 5)
            {
                printf("System is in a safe state.\nSafe Sequence: [");
                for (int i = 0; i < 5; i++)
                {
                    if (i == 4)
                    {
                        printf("%d]\n\n", safe_sequence[i]);
                    }
                    else
                    {
                        printf("%d, ", safe_sequence[i]);
                    }
                }
                return 1;
            }
            pass = 1;
            position = ((position + 1) % 5);

            // does the addition
            if (in_array(position, safe_sequence) == 0)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (func_available[i] < temp_need[position][i])
                    {
                        pass = 0;
                    }
                }
                if (pass == 1)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        func_available[i] = func_available[i] + temp_allocation[position][i];
                    }
                    safe_sequence[safe_position] = position;
                    safe_position = safe_position + 1;
                    loops_without_success = 0;
                }
                else
                {
                    loops_without_success = loops_without_success + 1;
                }
            }
            else
            {
                loops_without_success = loops_without_success + 1;
            }
        }

        printf("Over here ERROR!!\nError: System is in an unsafe state!\n\n");

        return 0;
    }

    // same thing as above but just the regular safe state
    else
    {
        int safe_sequence[5] = {-1, -1, -1, -1, -1};
        int loops_without_success = 0;
        int position = 4;
        int pass = 1;
        int safe_position = 0;
        int func_available[3];
        for (int i = 0; i < 3; i++)
        {
            func_available[i] = available[i];
        }

        while (loops_without_success < 12)
        {
            if (safe_position == 5)
            {
                printf("System is in a safe state.\nSafe Sequence: [");
                for (int i = 0; i < 5; i++)
                {
                    if (i == 4)
                    {
                        printf("%d]\n\n", safe_sequence[i]);
                    }
                    else
                    {
                        printf("%d, ", safe_sequence[i]);
                    }
                }
                return 1;
            }
            pass = 1;
            position = ((position + 1) % 5);

            if (in_array(position, safe_sequence) == 0)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (func_available[i] < need[position][i])
                    {
                        pass = 0;
                    }
                }
                if (pass == 1)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        func_available[i] = func_available[i] + allocation[position][i];
                    }
                    safe_sequence[safe_position] = position;
                    safe_position = safe_position + 1;
                    loops_without_success = 0;
                }
                else
                {
                    loops_without_success = loops_without_success + 1;
                }
            }
            else
            {
                loops_without_success = loops_without_success + 1;
            }
        }

        printf("Over Here ERROR!!\nError: System is in an unsafe state!\n\n");

        return 0;
    }
}

int resource_request(int num, int array[])
{

    // resource request
    printf("Output:\n");

    // makes sure they provide the correct resources and that it won't deadlock
    int meet_need = 0;
    int resources = 0;
    for (int i = 0; i < 3; i++)
    {
        if (array[i] > available[i])
        {
            resources = 1;
        }
        if (array[i] < need[num][i])
        {
            meet_need = 1;
        }
    }
    if (meet_need == 1)
    {
        printf("ERROR!!\nError: Request would lead to an unsafe state!\n\n");
    }
    if (resources == 1)
    {
        printf("ERROR!!\nError: Requested more resources than available!\n\n");
    }

    // makes variables to simulate the resource request
    if ((meet_need == 0) && (resources == 0))
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (i == num)
                {
                    temp_need[i][j] = 0;
                    temp_allocation[i][j] = 0;
                    temp_max[i][j] = 0;
                }
                else
                {
                    temp_need[i][j] = need[i][j];
                    temp_allocation[i][j] = allocation[i][j];
                    temp_max[i][j] = max[i][j];
                }
            }
        }
        for (int i = 0; i < 3; i++)
        {
            temp_available[i] = available[i] + allocation[num][i];
        }

        // calls safe state
        safe_state(1, num);
    }

    return 4;
}

int in_array(int num, int array[])
{
    // checks if an int is in an array
    for (int i = 0; i < 5; i++)
    {
        if (array[i] == num)
        {
            return 1;
        }
    }
    return 0;
}
int verify(int lower_bound, int upper_bound)
{
    // verify's input
    int choice = -2;
    while ((choice < lower_bound) || (choice > upper_bound))
    {
        printf("Enter your choice (%d-%d): ", lower_bound, upper_bound);
        if (scanf("%d", &choice) == 1)
        {
            if ((choice < lower_bound) || (choice > upper_bound))
            {
                printf("please enter an integer between %d and %d\n", lower_bound, upper_bound);
                while (getchar() != '\n' && !feof(stdin))
                    ;
            }
        }
        else
        {
            printf("please enter an integer between %d and %d\n", lower_bound, upper_bound);
            while (getchar() != '\n' && !feof(stdin))
                ;
        }
    }
    return choice;
}