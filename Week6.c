#include <stdio.h>

int main() {
    int n, i, j;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], wt[n], tat[n], temp;

    // Input burst times
    for(i = 0; i < n; i++) {
        printf("Enter Burst Time for Process %d: ", i+1);
        scanf("%d", &bt[i]);
    }

    // Sorting burst times (Ascending)
    for(i = 0; i < n; i++) {
        for(j = i + 1; j < n; j++) {
            if(bt[i] > bt[j]) {
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
            }
        }
    }

    // Calculate Waiting Time
    wt[0] = 0;
    for(i = 1; i < n; i++) {
        wt[i] = bt[i-1] + wt[i-1];
    }

    // Calculate Turnaround Time
    for(i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }

    float avg_wt = 0, avg_tat = 0;

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for(i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
        printf("P%d\t%d\t\t%d\t\t%d\n", i+1, bt[i], wt[i], tat[i]);
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}
