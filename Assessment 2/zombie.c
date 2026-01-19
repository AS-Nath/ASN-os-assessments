#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 

long long int factorial(long long int n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial(n - 1); 
}

int main(void) {
    pid_t pid = fork();
    if (pid > 0) {
        printf("Parent Executing. PID == %d\n", getpid()); 
        printf("Wasting time, evaluating factorial\n"); 
        printf("Value : %lld\n", factorial(15)); 
        sleep(1); 
        printf("Children became zombies. Parent will now reap them.\n"); 
        wait(NULL); 
        exit(0); 
    } 
    else {
        printf("Child (PID == %d) is a zombie as soon as this has printed.\n", getpid());
        exit(0);  
    }
    return 0;  
}