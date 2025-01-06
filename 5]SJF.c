#include <stdio.h>

int main() {
    int bt[20], p[20], wt[20], tat[20], i, j, n, total = 0, totalT = 0, pos, temp;
    float avg_wt, avg_tat;

    // Step 1: Input the number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Step 2: Input burst times
    printf("\nEnter Burst Time:\n");
    for (i = 0; i < n; i++) {
        printf("p%d: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1; // Assign process IDs
    }

    // Step 3: Sort burst times in ascending order
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (bt[j] < bt[pos]) {
                pos = j;
            }
        }
        // Swap burst times
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        // Swap process IDs
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    wt[0] = 0; // Waiting time for the first process is 0

    // Step 4: Calculate waiting times
    for (i = 1; i < n; i++) {
        wt[i] = 0;
        for (j = 0; j < i; j++) {
            wt[i] += bt[j]; // Sum of burst times of all previous processes
        }
        total += wt[i]; // Accumulate total waiting time
    }

    // Step 5: Calculate average waiting time
    avg_wt = (float)total / n;

    // Step 6: Print process details
    printf("\nProcess\t Burst Time \tWaiting Time\tTurnaround Time");
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i]; // Turnaround time
        totalT += tat[i];       // Accumulate total turnaround time
        printf("\np%d\t\t %d\t\t %d\t\t\t%d", p[i], bt[i], wt[i], tat[i]);
    }

    // Step 7: Calculate average turnaround time
    avg_tat = (float)totalT / n;

    // Step 8: Display averages
    printf("\n\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}
