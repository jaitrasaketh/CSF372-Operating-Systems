#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){

  int fd[2]; // pipe can accept only an array of size 2 
  
  if(pipe(fd)<0)
  {
	  perror("Pipe not created !\n");
	  exit(-1);
  }
  
  pid_t p=fork();
  
  if(p==0)
  {
	     close(fd[1]);
	     char read_buffer[100];
	     read(fd[0],read_buffer,100);   //read from the read end of the pipe into the read buffer
	     printf("This statement is read in the child process : %s \n",read_buffer);
	     close(fd[0]);
	    
  }
  else{
	  close(fd[0]);
	  char write_buffer[100]="This statement is written in the parent process";
	  write(fd[1],write_buffer,strlen(write_buffer)+1);
	  close(fd[1]);
  }
  


  return 0;
  
}
  
