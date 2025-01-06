#include <stdio.h>

int main() {
    int bt[20], p[20], pri[20], wt[20], tat[20];
    int i, j, n, total = 0, totalT = 0, pos, temp;
    float avg_wt, avg_tat;

    // Step 1: Get the number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Step 2: Get burst time and priority for each process
    printf("\nEnter Burst Time and Priority:\n");
    for (i = 0; i < n; i++) {
        printf("Enter Burst time for p%d: ", i + 1);
        scanf("%d", &bt[i]);
        printf("Enter Priority for p%d: ", i + 1);
        scanf("%d", &pri[i]);
        p[i] = i + 1; // Process ID
    }

    // Step 3: Sort processes by priority (ascending order)
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (pri[j] < pri[pos]) {
                pos = j; // Find process with higher priority (lower value)
            }
        }
        // Swap priorities, burst times, and process IDs
        temp = pri[i];
        pri[i] = pri[pos];
        pri[pos] = temp;

        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    // Step 4: Calculate waiting time for each process
    wt[0] = 0; // Waiting time for the first process is 0
    for (i = 1; i < n; i++) {
        wt[i] = 0;
        for (j = 0; j < i; j++) {
            wt[i] += bt[j]; // Add burst times of all previous processes
        }
        total += wt[i]; // Accumulate total waiting time
    }

    // Step 5: Calculate the average waiting time
    avg_wt = (float)total / n;

    // Step 6: Calculate turnaround time for each process
    printf("\nProcess\t Burst Time\t Priority\t Waiting Time\t Turnaround Time\n");
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i]; // Turnaround time = Burst time + Waiting time
        totalT += tat[i];       // Accumulate total turnaround time
        printf("p%d\t\t %d\t\t %d\t\t %d\t\t\t %d\n", p[i], bt[i], pri[i], wt[i], tat[i]);
    }

    // Step 7: Calculate average turnaround time
    avg_tat = (float)totalT / n;

    // Step 8: Print average times
    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}
