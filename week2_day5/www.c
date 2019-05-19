#include <func.h>
#define N 10
typedef void*(*threadFunc)(void*);
typedef struct{
	int num;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}data;


void* settiket(void *args)
{
	printf("jinlaile\n");
	data *p = (data*)args;
	pthread_mutex_lock(&p->mutex);
	pthread_cond_wait(&p->cond,&p->mutex);
	printf("add 20 tiikets NOW SELL BEGIN\n");
	p->num = 10;
	printf("%d\n",p->num);
	pthread_mutex_unlock(&p->mutex);
	pthread_exit(0);
}

int main()
{
	pthread_t pthid;
	data info ;
	info.num = 100;
	pthread_mutex_init(&info.mutex,NULL);
	pthread_cond_init(&info.cond,NULL);
		int ret	= pthread_create(&pthid,NULL,settiket,(void*)&info);
		THREAD_ERROR_CHECK(ret,"pthread_create" );
		sleep(1);
		pthread_cond_signal(&info.cond);
		usleep(1);
		pthread_mutex_lock(&info.mutex);
		pthread_join(pthid,NULL);
	pthread_mutex_destroy(&info.mutex);
	pthread_cond_destroy(&info.cond);
	printf("SELL BE END\n");
	return 0;
}
	
