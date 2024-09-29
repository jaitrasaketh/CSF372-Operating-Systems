#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char * argv[]){
     int p[2];
     pipe(p);
     pid_t fork_ret= fork();
     if(fork_ret==0){
      // child process the writer
      write(p[1],"Message written in ze child process",36);
       
     }
     else{
     // parent process the reader
      wait(NULL);  // waits till its written int the child process
      int n;
      char buf[37];
     while( (n=read(p[0],buf,4))>0)
         printf("This is printed in the parent process : %s \n",buf);
      

     if (n != 0)
exit(2);
printf("Finished reading\n");
     
     }
     return 0;
     }
     
