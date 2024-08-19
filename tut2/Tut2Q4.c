#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){ 

 pid_t p=fork();
  if(p==0){
  printf("Loading ... \n");
   execlp("cp","cp","input.txt","output.txt",(char *) NULL);
   
   }
    
  else{
  
  wait(NULL);
  printf("\n");
  printf("We just finished executing the child process \n");
  printf("\n");
  execlp("cat","cat","output.txt",(char *) NULL); 

 }  
 

  
  return 0;
  
}
