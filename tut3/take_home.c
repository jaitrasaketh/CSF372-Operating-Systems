#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>



int fact(int n){
	
	int p=1;
	for(int i=1;i<=n;i++)
	   p*=i;


   return p;
}


int main(int argc, char * argv[]){

       pid_t first,second,third;
       
       int p[2];
       pipe(p);
       
       int num1=atoi(argv[1]);
       int num2=atoi(argv[2]);
       int num3=atoi(argv[3]);
       
       first=fork();
       if(first==0)
       {
       close(p[0]);
       int result=fact(num1);
         write(p[1],&result,sizeof(int));
         close(p[1]);
         
         
         exit(0);
       }// first child
       
       second=fork();
          if(second==0){
             close(p[0]);
             int result=fact(num2);
             write(p[1],&result,sizeof(int));
             close(p[1]);
             
             exit(0);
          } // second child
          
      third=fork();
            if(third==0)
            {
              close(p[0]);
             int result=fact(num3);
             write(p[1],&result,sizeof(int));
             close(p[1]);
             
             exit(0);
            }// third child    
         
           wait(NULL);
           wait(NULL);
           wait(NULL);
               close(p[1]);
              
              int ans;
             for(int i=0;i<3;i++)
             {
                read(p[0],&ans,sizeof(int));
                printf("%d ",ans);
             }
             printf("\n");
              close (p[0]);
              
         
       
	return 0;       
}
       


