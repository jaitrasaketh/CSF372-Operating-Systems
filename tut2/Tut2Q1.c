#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){ 

  pid_t p=fork();
  if(p==0){
    printf("This is the child process \n");
    printf("The pid of the child process is : %d\n",getpid());
    printf("The pid of the parent process is : %d\n",getppid());
    }
  else{
  
  //wait(NULL);
  
  printf("This is the parent process \n");
  printf("The process id of the child is  : %d \n",p);
  printf("The process id of the parent is : %d \n",getpid());
  printf("The process id of the parent's parent is : %d \n",getppid());
 }  
  
  return 0;
  
}
