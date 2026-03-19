#include <stdio.h>

int main() {
    int n = 4;
    int at[] = {0, 2, 4, 6};
    int bt[] = {6, 4, 2, 3};
    int rt[] = {6, 4, 2, 3};   // remaining time
    int ct[4], tat[4], wt[4];
    int tq = 2;

    int time = 0, completed = 0;
    int queue[100], front = 0, rear = 0;
    int visited[4] = {0};

    // Add first process
    queue[rear++] = 0;
    visited[0] = 1;

    while (completed < n) {
        if (front == rear) {
            time++;
            for (int i = 0; i < n; i++) {
                if (at[i] <= time && visited[i] == 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int i = queue[front++];

        if (rt[i] > tq) {
            time += tq;
            rt[i] -= tq;
        } else {
            time += rt[i];
            rt[i] = 0;
            ct[i] = time;
            completed++;
        }

        // Add newly arrived processes
        for (int j = 0; j < n; j++) {
            if (at[j] <= time && visited[j] == 0) {
                queue[rear++] = j;
                visited[j] = 1;
            }
        }

        // If process is not finished, push again into queue
        if (rt[i] > 0) {
            queue[rear++] = i;
        }
    }

    // Calculate TAT and WT
    float total_wt = 0, total_tat = 0;

    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        total_wt += wt[i];
        total_tat += tat[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
