/**
* @file         Q1.c
* @brief        Q1
* @detail       This program is for printing PIDs of various childs and grandchilds
* @author       Prateek
*/

#include <stdio.h>
#include <unistd.h>

int main()

{

  int pid = -1, pid1 = -1, pid2 = -1, pid11 = -1, pid12 = -1, pid21 = -1, pid22 = -1;
  int ppppid = getpid();
  pid1 = fork(); // child1
  pid2 = fork(); //child2
  if(pid1>0 && pid2>0){ //parent
  printf("PID of First Child is %d.\n", pid1);
  printf("PID of Second Child is %d.\n", pid2);
  }
  else if(pid1==0 && pid2>0)
  { 
    pid11 = pid2;   // child1
    pid12 = fork();
    if(pid12 != 0){ // child1
      printf("PID of First Grandchild is %d.\n", pid11);
      printf("PID of Second Grandchild is %d.\n", pid12);
    }
  }

  else if(pid2==0 && pid1!=0){
    pid21 = fork();
    if(pid21 != 0){ //child2
    pid22 = fork();
    if(pid22 != 0){ //child2
    printf("PID of third Grandchild is %d.\n", pid21);
    printf("PID of fourth Grandchild is %d.\n", pid22);
    printf("PID of parent is %d.\n", ppppid);
    }

    }
  }
  }