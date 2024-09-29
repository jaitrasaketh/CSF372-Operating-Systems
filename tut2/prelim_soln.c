#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char* argv[]){
   pid_t fork_ret=fork();
   if(fork_ret == 0){
     printf("We're in the child process ! \n");
     char * argv[]={"ls",NULL,NULL};
     execv("/bin/ls",argv);
     
     printf("\n We got the list of the files in this directory now!\n");
    }
   wait(NULL);
   printf("We're in the parent process now!");
   return 0;
   
   
   
   
   



}