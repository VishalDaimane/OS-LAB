#include <stdio.h>

int main() {
    int pid[15];      // Process IDs
    int bt[15];       // Burst times
    int wt[15];       // Waiting times
    int n;            // Number of processes
    float twt = 0.0;  // Total waiting time
    float tat = 0.0;  // Total turnaround time

    // Step 1: Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Step 2: Input process IDs
    printf("Enter process ID of all the processes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pid[i]);
    }

    // Step 2: Input burst times
    printf("Enter burst time of all the processes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    // Step 3: Calculate waiting times
    wt[0] = 0; // First process has 0 waiting time
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }

    // Print process table header
    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");

    // Step 4: Calculate and display results
    for (int i = 0; i < n; i++) {
        int turnaround_time = bt[i] + wt[i];
        printf("%d\t\t%d\t\t%d\t\t%d\n", pid[i], bt[i], wt[i], turnaround_time);

        // Accumulate total waiting and turnaround times
        twt += wt[i];
        tat += turnaround_time;
    }

    // Step 5: Calculate and print averages
    float awt = twt / n; // Average waiting time
    float att = tat / n; // Average turnaround time
    printf("\nAvg. waiting time = %.2f\n", awt);
    printf("Avg. turnaround time = %.2f\n", att);

    return 0;
}
