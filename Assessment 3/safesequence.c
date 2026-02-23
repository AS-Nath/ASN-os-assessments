#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(void) {
    int n; // processes 
    int m; // resources
    printf("Enter number of processes and resources : "); 
    scanf("%d %d", &n, &m); 
    printf("Enter # of instances available for each resource : \n"); 
    int* available = (int *)malloc(m * sizeof(int)); 
    int* work = (int *)malloc(m * sizeof(int)); 
    for (int i = 0; i < m; i++) {
        scanf("%d", available + i); 
        work[i] = available[i];
    }
    printf("Enter maximum allocations for each resource for each process : \n"); 
    int** max = (int **)calloc(n, sizeof(int *)); 
    int** allocation = (int **)calloc(n, sizeof(int *)); 
    int** need = (int **)calloc(n, sizeof(int *)); 
    for (int i = 0; i < n; i++) {
        max[i] = (int *)calloc(m, sizeof(int)); 
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]); 
        }
    }
    printf("Enter number of currently allocated resources for each process : \n"); 
    for (int i = 0; i < n; i++) {
        allocation[i] = (int *)calloc(m, sizeof(int)); 
        need[i] = (int *)calloc(m, sizeof(int)); 
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]); 
            need[i][j] = max[i][j] - allocation[i][j]; 
        }
    }
    bool* finish = (bool *)calloc(n, sizeof(bool)); 
    int* safesequence = NULL; 
    int safelen = 0; 
    // finish[i] == false and need <= work.  
    while (true) {
        int executed = 0; 
        for (int i = 0; i < n; i++) {
            if (finish[i] == false) {
                bool yes = true;
                for (int j = 0; j < m; j++) { 
                    if (need[i][j] > work[j]) {
                        yes = false;
                        break; 
                    }
                }
                if (!yes) {
                    continue; 
                }
                else {
                    executed += 1;
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j]; 
                    }
                    finish[i] = true; 
                    safesequence = realloc(safesequence, (safelen + 1) * sizeof(int)); 
                    safelen += 1; 
                    safesequence[safelen - 1] = i; 
                }
            }
            else {
                continue; 
            }
        }
        if (executed == 0) {
            bool all = true;
            for (int i = 0; i < n; i++) {
                if (finish[i] == false) {
                    all = false;
                    break;
                }
            }
            if (all) {
                printf("Safe Sequence : ");
                for (int i = 0; i < safelen; i++) {
                    printf("%d ", safesequence[i]); 
                } 
                printf("\n"); 
            }
            else {
                printf("No Safe Sequence Found.\n"); 
            }
            break;
        }
    }
    return 0; 
}
/*
5 3
3 3 2
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
*/