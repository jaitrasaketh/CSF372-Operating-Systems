#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){ 

 pid_t p=fork();
  if(p==0){
   execlp("cat","cat","prelimsoln.c","Tut2Q1.c",(char *) NULL);
   // the below statements do not execute, as the program control transfers to the calling process, so everything else in this portion of the child processes's memory is wiped out
   printf("Hey");
   }
    
  else{
  
  wait(NULL);
  printf("\n");
  printf("We just finished executing the child process \n");
  printf("\n");
  execlp("ls","ls","-1",(char *) NULL); // lists the names of the files in the directory one line after the other
  
  // the below statement wont execute, as the program control after execution of execl family of functions transfers to the process thats being called, so everything else after this statement in the parent processes memory is wiped out
  printf("We just finished with executing the parent process \n");

 }  
 

  
  return 0;
  
}
