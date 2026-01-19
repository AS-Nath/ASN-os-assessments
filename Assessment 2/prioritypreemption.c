#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

double customlog(int n) {
    if (n != 0) return log10(n);
    return 0.0;
}

int main(void) {
    int n;
    printf("Enter the number of processes : ");
    scanf("%d", &n);
    int* arr = (int*)calloc(n, sizeof(int));
    int* at  = (int*)calloc(n, sizeof(int));
    int* bt  = (int*)calloc(n, sizeof(int));
    int* pr  = (int*)calloc(n, sizeof(int));
    int* rem = (int*)calloc(n, sizeof(int));
    int* ct  = (int*)calloc(n, sizeof(int));
    int* tt  = (int*)calloc(n, sizeof(int));
    int* wt  = (int*)calloc(n, sizeof(int));
    int* rt  = (int*)calloc(n, sizeof(int));
    printf("Enter Process IDs : \n");
    for (int i = 0; i < n; i++) scanf("%d", arr + i);
    printf("Enter Arrival Times : \n");
    for (int i = 0; i < n; i++) scanf("%d", at + i);
    printf("Enter Burst Times : \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", bt + i);
        rem[i] = bt[i];
        rt[i] = -1;
    }
    printf("Enter Priorities (lower value = higher priority) : \n");
    for (int i = 0; i < n; i++) scanf("%d", pr + i);
    int completed = 0;
    int time = 0;
    while (completed < n) {
        int index = -1;
        int minpriority = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rem[i] > 0) {
                if (pr[i] < minpriority) {
                    minpriority = pr[i];
                    index = i;
                }
                else if (pr[i] == minpriority) {
                    if (at[i] < at[index]) {
                        index = i;
                    }
                }
            }
        }
        // CPU idle
        if (index == -1) {
            time++;
            continue;
        }
        // Response Time
        if (rt[index] == -1) {
            rt[index] = time - at[index];
        }
        // Execute for 1 unit (pre-emptive)
        rem[index]--;
        time++;
        if (rem[index] == 0) {
            ct[index] = time;
            completed++;
        }
    }
    // Turnaround & Waiting Times
    for (int i = 0; i < n; i++) {
        tt[i] = ct[i] - at[i];
        wt[i] = tt[i] - bt[i];
    }
    printf("ID | AT | BT | PR | CT | TT | WT | RT\n");
    for (int i = 0; i < n; i++) {
        int len;
        len = (int)customlog(arr[i]) + 1;
        printf("%d", arr[i]);
        for (int j = 0; j < (3 - len); j++) printf(" ");
        printf("| ");
        len = (int)customlog(at[i]) + 1;
        printf("%d", at[i]);
        for (int j = 0; j < (3 - len); j++) printf(" ");
        printf("| ");

        len = (int)customlog(bt[i]) + 1;
        printf("%d", bt[i]);
        for (int j = 0; j < (3 - len); j++) printf(" ");
        printf("| ");
        len = (int)customlog(pr[i]) + 1;
        printf("%d", pr[i]);
        for (int j = 0; j < (3 - len); j++) printf(" ");
        printf("| ");
        len = (int)customlog(ct[i]) + 1;
        printf("%d", ct[i]);
        for (int j = 0; j < (3 - len); j++) printf(" ");
        printf("| ");
        len = (int)customlog(tt[i]) + 1;
        printf("%d", tt[i]);
        for (int j = 0; j < (3 - len); j++) printf(" ");
        printf("| ");
        len = (int)customlog(wt[i]) + 1;
        printf("%d", wt[i]);
        for (int j = 0; j < (3 - len); j++) printf(" ");
        printf("| ");
        len = (int)customlog(rt[i]) + 1;
        printf("%d", rt[i]);
        printf("\n");
    }
    return 0;
}