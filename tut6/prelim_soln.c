       #define _GNU_SOURCE
       #include <unistd.h>

#include <pthread.h>
#include <stdio.h>


void * runner(void * arg){

	printf("LINUX is %ld \n ", (long)gettid());
	printf("POSIX is %ld", (long)pthread_self());
	
	pthread_exit(0);
	
}

int main(int argc, char * argv[]){
	
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	pthread_create(&tid,&attr,runner,NULL);
	
	
	pthread_join(tid,NULL);

	return 0;
}

