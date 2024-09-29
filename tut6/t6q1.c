#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

#define NUM_THREADS 10

void * runner(void * param){
	
	intptr_t i=(intptr_t)param;		
	printf("Thread %ld ",(intptr_t)param);
	printf("with the id : %ld \n",(long)pthread_self());
		
		
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
		
	pthread_t tid[NUM_THREADS];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	for(int i=0;i<NUM_THREADS;i++){
	   pthread_create(&tid[i],&attr,runner,(void*)((intptr_t)i+1));
	}
	
	for(int i=0;i<NUM_THREADS;i++){
	   pthread_join(tid[i],NULL);
	}
	
	
	return 0;
}