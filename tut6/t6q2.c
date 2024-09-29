#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

#define N 3 // no of rows in pyramid and also no of threads

void * print_row(void * param){

   intptr_t R=(intptr_t)param;
   
   for (int i = 0; i < N-R; i++) {
        printf(" ");
    }
   for(int r=1;r<=R;r++)
   {
   	printf("* ");
   }
   printf("\n");
   
   pthread_exit(0);
}

int main(int argc, char* argv[]){
	pthread_t tid[N];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	for(int i=0;i<N;i++){
		pthread_create(&tid[i],&attr,print_row,(void *)((intptr_t)i+1)); // in fourth we pass a pointer
	
	}
	
	for(int i=0;i<N;i++){
		pthread_join(tid[i],NULL);
	
	}

	return 0;
}