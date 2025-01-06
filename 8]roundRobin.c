#include <stdio.h>

int main() {
    // Input number of processes
    int n;
    printf("Enter Total Number of Processes: ");
    scanf("%d", &n);

    // Declare necessary arrays and variables
    int wait_time = 0, ta_time = 0;  // Total waiting and turnaround time
    int arr_time[n], burst_time[n], temp_burst_time[n];
    int x = n;  // Number of processes remaining

    // Input process details (arrival time and burst time)
    for (int i = 0; i < n; i++) {
        printf("Enter Details of Process %d \n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &arr_time[i]);
        printf("Burst Time: ");
        scanf("%d", &burst_time[i]);
        temp_burst_time[i] = burst_time[i];  // Copy burst time for processing
    }

    // Input time quantum for Round Robin scheduling
    int time_slot;
    printf("Enter Time Slot: ");
    scanf("%d", &time_slot);

    // Initialize counters
    int total = 0, counter = 0, i = 0;

    // Print process details header
    printf("\nProcess ID\tBurst Time\tTurnaround Time\tWaiting Time\n");

    // Round Robin Scheduling
    while (x != 0) {
        // If the process can be completed within the time slot
        if (temp_burst_time[i] <= time_slot && temp_burst_time[i] > 0) {
            total += temp_burst_time[i];
            temp_burst_time[i] = 0;  // Process completed
            counter = 1;  // Mark process as completed
        }
        // If the process needs more time
        else if (temp_burst_time[i] > 0) {
            temp_burst_time[i] -= time_slot;
            total += time_slot;
        }

        // When a process is completed
        if (temp_burst_time[i] == 0 && counter == 1) {
            x--;  // Decrease remaining process count
            printf("Process %d\t\t%d\t\t%d\t\t\t%d\n", i + 1, burst_time[i],
                   total - arr_time[i], total - arr_time[i] - burst_time[i]);

            // Calculate waiting and turnaround times
            wait_time += total - arr_time[i] - burst_time[i];
            ta_time += total - arr_time[i];
            counter = 0;  // Reset counter for the next process
        }

        // Check if we have reached the end of the list of processes
        if (i == n - 1) {
            i = 0;  // Reset to the first process
        }
        // Move to the next process if it has arrived
        else if (arr_time[i + 1] <= total) {
            i++;
        }
        // Otherwise, reset to the first process
        else {
            i = 0;
        }
    }

    // Calculate and print the average waiting and turnaround times
    float average_wait_time = (float)wait_time / n;
    float average_turnaround_time = (float)ta_time / n;
    printf("\nAverage Waiting Time: %.2f", average_wait_time);
    printf("\nAverage Turnaround Time: %.2f\n", average_turnaround_time);

    return 0;
}
