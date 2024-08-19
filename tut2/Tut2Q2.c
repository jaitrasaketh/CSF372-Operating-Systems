#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){ 

  pid_t p=fork();
  if(p==0){
    
    pid_t p2=fork();
    if(p2==0)
    {
       printf("This is the grandchild process \n");
       printf("The pid of the grandchild process is : %d\n",getpid());
       printf("The pid of the child(which is parent of grandchild) process is : %d\n",getppid());
       }
       else
       {
          wait(NULL);
          printf("\n");
          printf("We just waited for the grandchild to execute\n");
          printf("The process id of the grandchild is : %d \n",p2);
          printf("This is the child process \n");
          printf("The pid of the child process is : %d\n",getpid());
          printf("The pid of the parent process is : %d\n",getppid());
       }
       
       
       }
    
  else{
  
  wait(NULL);
  printf("\n");
  printf("We just waited for the child process to execute \n");
  printf("This is the parent process \n");
  printf("The process id of the child is  : %d \n",p);
  printf("The process id of the parent is : %d \n",getpid());
  printf("The process id of the parent's parent is : %d \n",getppid());
 }  
  
  return 0;
  
}
