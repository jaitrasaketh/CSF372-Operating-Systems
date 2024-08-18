#include <stdio.h>
#include <stdlib.h>

int fact(int n){

    int p=1;
    for(int i=1;i<=n;i++)
       p*=i;
   return p;
}

int main(int argc,char *argv[]){
    int n=atoi(argv[1]);
    printf(" Factorial of %d is %d \n",n,fact(n));
    
    return 0;
    }

