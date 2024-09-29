#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

#define N 3 // size of array and no of threads

typedef struct {
	int X;
	int Y;
	int Z;
}point;

void *distance(void * param){

   point* points=(point*)param;
   
   printf("%ld \n", (intptr_t)((points->X * points->X) + (points->Y * points->Y) + (points->Z * points->Z)));
   
   pthread_exit(0);




}
int main(int argc, char *argv[]){
	
	point points[3];
	points[0].X=1;
	points[0].Y=2;
	points[0].Z=3;
	
	points[1].X=4;
	points[1].Y=5;
	points[1].Z=6;
	
	points[2].X=7;
	points[2].Y=8;
	points[2].Z=9;
	
	pthread_t tid[N];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	for(int i=0;i<N;i++)
	{
		pthread_create(&tid[i],&attr,distance,(void*)&points[i]);	  // $points[i] is of the type point* __	
	}
	for(int i=0;i<N;i++){
	pthread_join(tid[i],NULL);
	}
	

	return 0;
}
