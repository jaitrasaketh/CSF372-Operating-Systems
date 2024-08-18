#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
   int num1=atoi(argv[1]);
   int num2=atoi(argv[2]);
   char op=argv[3][0];  // extracts first character of 3rd string in the string array
   
   switch(op)
   {
   case '+': printf("Sum is %d \n",num1+num2);break;
   case '-': printf("Difference is %d \n",num1-num2);break;
   case '*': printf("Product is %d \n",num1*num2);break;
   case '/': printf("Quotient is %d \n",num1/num2);break;
  }
    return 0;
}
