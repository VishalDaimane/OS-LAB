#include <stdio.h>
#include <stdbool.h>
#define MAX_PROCESSES 100

// Structure to represent each process
struct process {
    int pid;             // Process ID
    int arrival_time;    // Arrival time
    int burst_time;      // Burst time
    int remaining_time;  // Remaining time
    int completion_time; // Completion time
};

// Main function
int main() {
    int n, current_time = 0, completed = 0, shortest_index = -1;
    struct process processes[MAX_PROCESSES];
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0; // Initialize completion time
    }

    // Process scheduling loop
    while (completed < n) {
        shortest_index = -1;

        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && processes[i].arrival_time <= current_time) {
                if (shortest_index == -1 || processes[i].remaining_time < processes[shortest_index].remaining_time) {
                    shortest_index = i;
                }
            }
        }

        // If no process is ready, increment time
        if (shortest_index == -1) {
            current_time++;
            continue;
        }

        // Process the selected process
        processes[shortest_index].remaining_time--;
        current_time++;

        // If the process is completed
        if (processes[shortest_index].remaining_time == 0) {
            completed++;
            processes[shortest_index].completion_time = current_time;
        }
    }

    // Display results
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        int turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        int waiting_time = turnaround_time - processes[i].burst_time;

        total_waiting_time += waiting_time;
        total_turnaround_time += turnaround_time;

        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, waiting_time, turnaround_time);
    }

    // Calculate averages
    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n;

    printf("\nAverage Waiting Time = %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time = %.2f\n", avg_turnaround_time);

    return 0;
}
