#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
   
   
    pid_t first_child, second_child;
    
    int p[2];
    pipe(p);
    
    first_child=fork();
    if(first_child==0){
     
     dup2(p[1],STDOUT_FILENO); // shifts the write descriptor to output of the process

     close(p[0]);  // close the read end because it only needs to write
     
     execlp("ls","ls",NULL,NULL);
     
    
    } // first child
    
    else// parent
    {
       second_child=fork();
       if(second_child==0){
       
       dup2(p[0],STDIN_FILENO); // shifts the read descroptor to thie input of thisn process
       close(p[1]); // closer the write end because it only needs to read



       execlp("wc","wc","-l",NULL);
       
       } // second child
       
       // parent process
       
       close(p[0]);
       close(p[1]);
    
    
    }
    
    
   return 0;
}
