/**
* @file         Q2-1.c
* @brief        Q2-1
* @detail       Zombie Process
* @author       Prateek
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    printf("Parent PID : %d",getpid());
    int k = fork();
    if(k != 0){
        sleep(100); //parent went to sleep
    }
    else
    {
        printf(" Child PID : %d",getpid());
        exit(0); //child process terminated
        
    }
    return 0;
}