#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 

int main(void) {
    pid_t pid = fork(); 
    if (pid > 0) {
        printf("Parent process (PID == %d) is dead.\n", getpid()); 
        exit(0); 
    }
    else {
        printf("Child (PID == %d) is running.\n", getpid()); 
        sleep(1); 
        printf("Child is an orphan. Parent PID == %d", getppid()); 
        exit(0); 
    }
    return 0; 
}