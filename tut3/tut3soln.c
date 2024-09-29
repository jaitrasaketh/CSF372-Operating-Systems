#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char * argv[]){

    int p[2];
    pipe(p);
    
    pid_t fork_ret=fork();
    if(fork_ret==0)
    {
       int buf_w[]={1,2,3,4};
       //write(p[1], buf_w,4*sizeof(int));
       close(p[1]);
    }
    else
    {
       wait(NULL);
       int buf_r[4];
       //read(p[0],buf_r,4*sizeof(int));
       int sum=0;
       for(int i=0;i<4;i++)
          sum+=buf_r[i];
          
       printf("%d \n",sum);  
       close(p[0]); 
    
    
    
    
    }
    return 0;
    }
    
    


 
