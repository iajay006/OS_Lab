#include <stdio.h>

struct Process {
    int pid, at, bt, priority, ct, tat, wt, completed;
};

int main() {
    int n = 4;
    struct Process p[4] = {
        {1, 0, 4, 9, 0, 0, 0, 0},
        {2, 1, 5, 11, 0, 0, 0, 0},
        {3, 2, 8, 19, 0, 0, 0, 0},
        {4, 3, 7, 3, 0, 0, 0, 0}
    };

    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1;
        int max_priority = -1;

        // Find highest priority process available at current time
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].completed == 0) {
                if (p[i].priority > max_priority) {
                    max_priority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].completed = 1;
            completed++;
        } else {
            time++; // CPU idle
        }
    }

    float total_tat = 0, total_wt = 0;

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].priority,
               p[i].ct, p[i].tat, p[i].wt);

        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);

    return 0;
}
