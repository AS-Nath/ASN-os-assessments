#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
    int n; // processes
    int m; // resources
    scanf("%d %d", &n, &m); 
    int* available = (int *)calloc(m, sizeof(int)); 
    int* work = (int *)calloc(m, sizeof(int)); 
    int** allocation = (int **)calloc(n, sizeof(int *)); 
    printf("Enter Resource Allocations for each process : \n"); 
    for (int i = 0; i < n; i++) {
        allocation[i] = (int *)calloc(m, sizeof(int)); 
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]); 
        }
    }
    int** requests = (int **)calloc(n, sizeof(int *));
    printf("Enter Resource Requests for each process : \n"); 
    for (int i = 0; i < n; i++) {
        requests[i] = (int *)calloc(m, sizeof(int)); 
        for (int j = 0; j < m; j++) {
            scanf("%d", &requests[i][j]); 
        }
    }
    printf("Enter # of Available Resources : \n"); 
    for (int i = 0; i < m; i++) {
        scanf("%d", available + i); 
        work[i] = available[i]; 
    }
    bool* finish = (bool *)calloc(n, sizeof(bool)); 
    while (true) {
        bool pending = true;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                bool flag = true; 
                for (int j = 0; j < m; j++) {
                    if (requests[i][j] > work[j]) {
                        flag = false;
                        break; 
                    }
                }
                if (!flag) {
                    continue; 
                }
                else {
                    pending = false; 
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j]; 
                    }
                    finish[i] = true; 
                }
            }
        } 
        if (pending) {
            bool flag = true;
            for (int i = 0; i < n; i++) {
                if (finish[i] == false) {
                    flag = false;
                    break; 
                }
            }
            if (!flag) {
                printf("Deadlocked Processes : ");
                for (int i = 0; i < n; i++) {
                    if (finish[i] == false) {
                        printf("%d ", i); 
                    }
                }
            }
            else {
                printf("No Deadlocks.");
            }
            printf("\n");
            break;
        }
    }
    return 0; 
}
/*
3 2
0 1
1 0
1 1
1 0
0 1
1 1
1 0

3 2
1 0
0 1
1 0
0 1
1 0
1 0
0 0
*/