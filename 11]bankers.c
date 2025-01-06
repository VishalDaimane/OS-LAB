#include <stdio.h>

int main() {
    int p, c, count = 0, i, j;
    int alc[5][3], max[5][3], need[5][3], safe[5], available[3], done[5];

    // Input the number of processes and resources
    printf("Enter the number of processes and resources: ");
    scanf("%d %d", &p, &c);

    // Input the allocation matrix
    printf("Enter the allocation matrix for resources of all processes (%dx%d matrix):\n", p, c);
    for (i = 0; i < p; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &alc[i][j]);
        }
    }

    // Input the maximum resource requirements for each process
    printf("Enter the max resource requirements for each process (%dx%d matrix):\n", p, c);
    for (i = 0; i < p; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input the available resources
    printf("Enter the available resources: ");
    for (i = 0; i < c; i++) {
        scanf("%d", &available[i]);
    }

    // Compute the need matrix (Need = Max - Allocation)
    printf("\nNeed resources matrix is:\n");
    for (i = 0; i < p; i++) {
        for (j = 0; j < c; j++) {
            need[i][j] = max[i][j] - alc[i][j];
            printf("%d\t", need[i][j]);
        }
        printf("\n");
    }

    // Initialize the done array to track whether a process has completed
    for (i = 0; i < p; i++) {
        done[i] = 0;
    }

    // Safety algorithm to find the safe sequence
    while (count < p) {
        int found = 0; // Tracks if a process was executed in the current iteration

        for (i = 0; i < p; i++) {
            if (done[i] == 0) { // Check if the process is not already completed
                for (j = 0; j < c; j++) {
                    if (need[i][j] > available[j]) {
                        break; // If need is greater than available, skip the process
                    }
                }

                // If all needs are satisfied, execute the process
                if (j == c) {
                    safe[count] = i; // Add the process to the safe sequence
                    done[i] = 1;     // Mark the process as done
                    found = 1;       // A process was successfully executed

                    // Release resources held by the process
                    for (j = 0; j < c; j++) {
                        available[j] += alc[i][j];
                    }
                    count++;
                }
            }
        }

        if (!found) { // If no process could be executed, no safe sequence exists
            printf("Safe sequence does not exist\n");
            return 1;
        }
    }

    // Print the results
    printf("\nAvailable resources after completion:\n");
    for (i = 0; i < c; i++) {
        printf("%d\t", available[i]);
    }

    printf("\nSafe sequence is:\n");
    for (i = 0; i < p; i++) {
        printf("p%d\t", safe[i] + 1); // Add 1 to make it user-friendly (p1, p2, ...)
    }
    printf("\n");

    return 0;
}
