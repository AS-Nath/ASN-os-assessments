#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double customlog(int n) {
    if (n != 0) {
        return log10(n); 
    }
    return 0.0; 
}

int main(void) {
    int n;
    printf("Enter the number of processes : "); 
    scanf("%d", &n); 
    int* arr = (int *)calloc(n, sizeof(int)); 
    int* bt = (int *)calloc(n, sizeof(int)); 
    int* ct = (int *)calloc(n, sizeof(int));
    int* tt = (int *)calloc(n, sizeof(int));
    int* wt = (int *)calloc(n, sizeof(int));
    int* rt = (int *)calloc(n, sizeof(int));
    printf("Enter Process IDs : \n");
    for (int i = 0; i < n; i++) scanf("%d", arr + i); 
    printf("Enter Burst Times : \n"); 
    for (int i = 0; i < n; i++) scanf("%d", bt + i); 
    // Sort by bt, then prefix sums of bt go to ct. 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-1; j++) {
            if (bt[j] > bt[j + 1]) {
                int t = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = t;
                t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t; 
            }
        }
    }
    // Prefix sum evaluation
    ct[0] = bt[0];
    for (int i = 0; i < n; i++) ct[i] = bt[i] + ct[i - 1];
    //TT
    for (int i = 0; i < n; i++) tt[i] = ct[i];
    //WT
    for (int i = 0; i < n; i++) wt[i] = tt[i] - bt[i]; 
    //RT
    for (int i = 0; i < n; i++) rt[i] = ct[i] - bt[i];
    printf("ID | BT | CT | TT | WT | RT\n"); 
    for (int i = 0; i < n; i++) {
        int len = ((int)customlog(arr[i]) + 1); 
        printf("%d", arr[i]); 
        for (int i = 0; i < (3 - len); i++) printf(" "); 
        printf("| "); 
        len = ((int)customlog(bt[i]) + 1); 
        printf("%d", bt[i]); 
        for (int i = 0; i < (3 - len); i++) printf(" "); 
        printf("| "); 
        len = ((int)customlog(ct[i]) + 1); 
        printf("%d", ct[i]); 
        for (int i = 0; i < (3 - len); i++) printf(" "); 
        printf("| "); 
        len = ((int)customlog(tt[i]) + 1); 
        printf("%d", tt[i]); 
        for (int i = 0; i < (3 - len); i++) printf(" "); 
        printf("| "); 
        len = ((int)customlog(wt[i]) + 1); 
        printf("%d", wt[i]); 
        for (int i = 0; i < (3 - len); i++) printf(" "); 
        printf("| "); 
        len = ((int)customlog(rt[i]) + 1); 
        printf("%d", rt[i]); 
        for (int i = 0; i < (3 - len); i++) printf(" "); 
        printf("\n"); 
    }
    return 0; 
}