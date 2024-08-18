#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){ // format for command line arguments. argc--> number of arguments; argv--> array storing all the arguments

    int n=atoi(argv[1]); // function to convert string to int
  
    printf("Entered number is : %d",n);
    printf("\n");
    for(int i=0;i<n;i++)
      { printf("Hello World! ");
        printf("\n");
        }
       
       
    return 0;



}
