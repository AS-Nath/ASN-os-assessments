#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_safe(int n, int m, int* work, int** allocation, int** need) {
    bool* finish = (bool*)calloc(n, sizeof(bool));
    while (true) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool can_run = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        can_run = false;
                        break;
                    }
                }
                if (can_run) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    executed++;
                }
            }
        } 
        if (executed == 0) {
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            return false;
        }
    } 
    return true;
}

int main(void) {
    int n, m; 
    printf("Enter number of processes and resources : ");
    scanf("%d %d", &n, &m);
    int* available = (int*)calloc(m, sizeof(int));
    printf("Enter Available vector :\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }
    int** max = (int**)calloc(n, sizeof(int*));
    int** allocation = (int**)calloc(n, sizeof(int*));
    int** need = (int**)calloc(n, sizeof(int*)); 
    printf("Enter Max matrix :\n");
    for (int i = 0; i < n; i++) {
        max[i] = (int*)calloc(m, sizeof(int));
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    } 
    printf("Enter Allocation matrix :\n");
    for (int i = 0; i < n; i++) {
        allocation[i] = (int*)calloc(m, sizeof(int));
        need[i] = (int*)calloc(m, sizeof(int)); 
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    int pid;
    printf("Enter process ID making request : ");
    scanf("%d", &pid);
    int* request = (int*)calloc(m, sizeof(int));
    printf("Enter request vector :\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &request[j]);
    } 
    for (int j = 0; j < m; j++) {
        if (request[j] > need[pid][j]) {
            printf("Error: Request exceeds process need.\n");
            return 0;
        }
    }
    for (int j = 0; j < m; j++) {
        if (request[j] > available[j]) {
            printf("Resources not available. Process must wait.\n");
            return 0;
        }
    }
    for (int j = 0; j < m; j++) {
        available[j] -= request[j];
        allocation[pid][j] += request[j];
        need[pid][j] -= request[j];
    }
    int* work = (int*)calloc(m, sizeof(int));
    for (int j = 0; j < m; j++)
        work[j] = available[j];

    if (is_safe(n, m, work, allocation, need)) {
        printf("Request can be granted. System is in safe state.\n");
    }
    else { 
        printf("Request cannot be granted. System would be unsafe.\n");
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
1
1 0 2
*/