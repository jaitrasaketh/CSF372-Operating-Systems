#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
     
     pid_t p= fork();
     if(p==0){
     printf("This is the child process with the pid : %d \n",getpid());
     execl("/bin/ls", "ls", (char *)NULL);  // Corrected the execl call
     /* 
       execl(const char* path,const char * arg0, const char* arg1 ....)
       in the above usage path is -->/bin/ls
       arg0 is generally used to represent the same file's executable name by convention , which is ls here
       arg1 which is -1 here is the first argument
       arg 2 which is char* NULL here is a sentinel value used to represent end of arguments
      */
     
     }
     else
     {
     wait(NULL);
     printf("This is the parent process with the pid : %d and my child's pid is : %d \n",getpid(),p);
     
     }
     
 return 0;    
}     
     
     
