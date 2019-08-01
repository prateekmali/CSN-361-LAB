/**
* @file         Q2-2.c
* @brief        Q2-2
* @detail       Orphan Process
* @author       Prateek
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    printf("Parent PID : %d",getpid());
    int k = fork();
    if(k == 0){
        printf("Child PID : %d",getpid());
        sleep(100); //child went to sleep
    }
    else
    {
        exit(0); //parent process terminated

    }
    return 0;
}