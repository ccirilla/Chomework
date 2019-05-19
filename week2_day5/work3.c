#include <func.h>
#define N 20000000
typedef struct{
	int num;
	pthread_mutex_t mutex;
}data;

void * threadFunc(void *args)
{
	data *p = (data*)args;
	for(int i=0;i<N;i++)
	{
		pthread_mutex_lock(&p->mutex);
		p->num++;
		pthread_mutex_unlock(&p->mutex);
	}
	pthread_exit(0);
}

int main()
{
	pthread_t pthid[2];
	data info ;
	info.num = 0;
	pthread_mutex_init(&info.mutex,NULL);
	for(int i =0;i<2;i++)
	{
		int ret	= pthread_create(pthid+i,NULL,threadFunc,(void*)&info);
		THREAD_ERROR_CHECK(ret,"pthread_create" );
	}
	for(int i =0;i<2;i++)
	{
		pthread_join(pthid[i],NULL);
	}
	pthread_mutex_destroy(&info.mutex);
	printf("I am main thread result = %d\n",info.num);
	return 0;
}
	
