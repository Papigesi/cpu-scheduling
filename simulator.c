#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 10

int compare_arrival(const void *a, const void *b) {
    int arrivalA = ((int*)a)[1];
    int arrivalB = ((int*)b)[1];

    if (arrivalA == arrivalB) {
        return ((int*)a)[0] - ((int*)b)[0]; // PID'ye göre sıralama
    }
    return arrivalA - arrivalB; // Arrival time'a göre sıralama
}

void read_processes(const char *filename, int processes[MAX_PROCESSES][4], int *n) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    *n = 0; // Reset process count
    while (fscanf(file, "%d %d %d %d", 
                  &processes[*n][0], 
                  &processes[*n][1], 
                  &processes[*n][2], 
                  &processes[*n][3]) != EOF) {
        (*n)++;
        if (*n >= MAX_PROCESSES) {
            printf("Maximum process limit exceeded.\n");
            break;
        }
    }
    qsort(processes, *n, sizeof(processes[0]), compare_arrival);
    fclose(file);
}

// FCFS (First Come First Serve) Algorithm
void fcfs(int processes[MAX_PROCESSES][4], int n) {
    int time = 0, completion_times[MAX_PROCESSES];
    int turnaround_time, waiting_time;
    int total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++) {
        if (time < processes[i][1]) {
            time = processes[i][1]; // Fill idle time
        }
        time += processes[i][3]; // Burst time kadar ilerle
        completion_times[i] = time;

        turnaround_time = completion_times[i] - processes[i][1];
        waiting_time = turnaround_time - processes[i][3];
        total_tat += turnaround_time;
        total_wt += waiting_time;

        printf("Process %d Completion Time: %d\n", processes[i][0], completion_times[i]);
    }

    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
}

// Priority Algorithm (non-preemptive)
void prio(int processes[MAX_PROCESSES][4], int n) {
    int completed = 0, time = 0, visited[MAX_PROCESSES] = {0};
    int completion_times[MAX_PROCESSES];
    int turnaround_time, waiting_time;
    int total_tat = 0, total_wt = 0;

    while (completed < n) {
        int min_priority = __INT_MAX__, idx = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && processes[i][1] <= time && processes[i][2] < min_priority) {
                min_priority = processes[i][2];
                idx = i;
            }
        }

        if (idx == -1) {
            time++; // Advance time if no process is ready
            continue;
        }

        time += processes[idx][3];
        completion_times[idx] = time;
        visited[idx] = 1;
        completed++;

        turnaround_time = completion_times[idx] - processes[idx][1];
        waiting_time = turnaround_time - processes[idx][3];
        total_tat += turnaround_time;
        total_wt += waiting_time;

        printf("Process %d Completion Time: %d\n", processes[idx][0], completion_times[idx]);
    }

    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
}

// SJF (Shortest Job First) Algorithm
void sjf(int processes[MAX_PROCESSES][4], int n) {
    int completed = 0, time = 0, visited[MAX_PROCESSES] = {0};
    int completion_times[MAX_PROCESSES];
    int turnaround_time, waiting_time;
    int total_tat = 0, total_wt = 0;

    while (completed < n) {
        int shortest_burst = __INT_MAX__, idx = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && processes[i][1] <= time && processes[i][3] < shortest_burst) {
                shortest_burst = processes[i][3];
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += processes[idx][3];
        completion_times[idx] = time;
        visited[idx] = 1;
        completed++;

        turnaround_time = completion_times[idx] - processes[idx][1];
        waiting_time = turnaround_time - processes[idx][3];
        total_tat += turnaround_time;
        total_wt += waiting_time;

        printf("Process %d Completion Time: %d\n", processes[idx][0], completion_times[idx]);
    }

    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s [FCFS|PRIO|SJF] <filename>\n", argv[0]);
        return 1;
    }

    char *algorithm = argv[1];
    char *filename = argv[2];

    int processes[MAX_PROCESSES][4];
    int n;

    // Read file
    read_processes(filename, processes, &n);

    // Choose an algorithm and run
    if (strcmp(algorithm, "FCFS") == 0) {
        fcfs(processes, n);
    } else if (strcmp(algorithm, "PRIO") == 0) {
        prio(processes, n);
    } else if (strcmp(algorithm, "SJF") == 0) {
        sjf(processes, n);
    } else {
        printf("Invalid scheduling algorithm! Your input: %s --- You should choose: FCFS, PRIO or SJF\n", algorithm);
        return 1;
    }

    return 0;
}
