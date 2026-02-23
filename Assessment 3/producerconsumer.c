#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int N = 5;
int out = -1;
int in = -1;
int count = 0; 
int totalProduced = 0;
int totalConsumed = 0; 
int consumeBlocks = 0;
int produceBlocks = 0; 
int* arr; 

void display() {
    printf("Total Produced : %d\n", totalProduced);
    printf("Total Consumed : %d\n", totalConsumed); 
    printf("Total Blocks : %d\n", consumeBlocks + produceBlocks); 
    if (totalConsumed == totalProduced) {
        printf("Synchronised!\n");
    } 
    else {
        printf("Mismatch!\n"); 
    }
}

void display_buffer() {
    if (count == 0) {
        printf("Empty Buffer!\n"); 
        return; 
    }
    printf("Buffer Elements : "); 
    int index = out;
    for (int i = 0; i < count; i++) {
        printf("%d ", arr[index]);
        index = (index + 1) % N; 
    }
    printf("\n"); 
}

void produce(int n) {
    if (count == N) {
        produceBlocks += 1;
        printf("Produce Blocked.\n"); 
        return;
    } 
    in = (in + 1) % N; 
    if (out == -1) {
        out += 1; 
    }
    arr[in] = n; 
    count += 1; 
    totalProduced += 1;
    printf("%d Produced!\n", n); 
}

void consume() {
    if (count == 0) {
        consumeBlocks += 1;
        printf("Consume Blocked.\n"); 
        return; 
    }
    printf("%d Consumed!\n", arr[out]); 
    arr[out] = -1; 
    out = (out + 1) % N;
    count -= 1;
    totalConsumed += 1; 
    if (count == 0) {
        out = -1;
        in = -1; 
    }
}

int main(void) {
    arr = (int *)calloc(N, sizeof(int));
    // Driver code not written. 
    printf("Enter a sequence of P (Produce) and C (Consume) to process : \n"); 
    char* sequence = (char *)malloc(100 * sizeof(char)); 
    scanf("%s", sequence); 
    int p_val = 1; // produce value. We'll increment it arbitrarily to signify different productions. 
    for (int i = 0; i < strlen(sequence); i++) {
        if (toupper(sequence[i]) == 'P') {
            produce(p_val); 
            p_val += 1; 
        }
        else {
            consume(); 
        }
        display_buffer();
    }
    display(); 
    return 0; 
}