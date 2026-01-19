#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    printf("Enter number of processes : "); 
    scanf("%d", &n); 
    int* arr = (int *)calloc(n, sizeof(int)); 
    int* bt = (int *)calloc(n, sizeof(int)); 
    int* ct = (int *)calloc(n, sizeof(int)); 
    int* tt = (int *)calloc(n, sizeof(int)); 
    int* wt = (int *)calloc(n, sizeof(int)); 
    int* rt = (int *)calloc(n, sizeof(int)); 
    printf("Enter PIDs : \n"); 
    for (int i = 0; i < n; i++) {
        scanf("%d", arr + i); 
    }
    printf("Enter Burst Times : "); 
    for (int i = 0; i < n; i++) {
        scanf("%d", bt + i); 
    }
    // CT 
    ct[0] = bt[0]; 
    for (int i = 1; i < n; i++) {
        ct[i] = ct[i - 1] + bt[i]; 
    }
    // TT
    for (int i = 0; i < n; i++) {
        tt[i] = ct[i]; 
    } 
    // WT
    for (int i = 0; i < n; i++) {
        wt[i] = tt[i] - bt[i]; 
    }
    // RT
    for (int i = 0; i < n; i++) {
        rt[i] = ct[i] - bt[i];
    }
    for (int i = 0; i < n; i++) {
        printf("PID %d | Burst Time %d | Completion Time %d | Turnaround Time %d | Wait Time %d | Response time %d\n", arr[i], bt[i], ct[i], tt[i], wt[i], rt[i]); 
    }
}