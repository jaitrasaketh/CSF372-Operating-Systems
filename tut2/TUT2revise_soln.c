#include <unistd.h>
#include<stdio.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
   
   pid_t fork_ret=fork();
    if(fork_ret == 0)
    {
        printf("PID of the child process : %d \n",getpid());
        printf("PID of the parent(of the child) process : %d \n",getppid());
        
        
   	//execlp("cat","cat",argv[1],NULL);
   	
   	
   	execlp("cp","cp","input.txt","output.txt",NULL);
    	
    
       
        /*pid_t fork_ret2=fork();
        if(fork_ret2 == 0){
        
          printf("We're in the grandchild process! %d \n",getpid());
          printf("The pid of granchild's parent(child) is %d \n",getppid());
          
        }
        else
        {
        waitpid(fork_ret2,0,0);
        printf("The pid of the child(parent to granchild) is \n",getpid());
        //printf("The pid of the granchild(child's child) is \n ",fork_ret2);
        
        
    }*/
    }
    else{
    wait(NULL);
    printf("PID of the parent process : %d \n",getpid());
    printf("The pid of its child process is : %d \n",fork_ret);
    printf("The pid of the parent (of the parent) process is :%d \n",getppid());
    //execlp("ls","ls",NULL,NULL);
    
    execlp("cat","cat","output.txt",NULL);
    }



    
    

return 0;
}
