#include <func.h>
#define N 10
typedef void*(*threadFunc)(void*);
typedef struct{
	int num;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}data;

void * Sallwindows1(void *args)
{
	printf("111111111111111111\n");
	data *p = (data*)args;
	while(1)
	{
		pthread_mutex_lock(&p->mutex);
		if(p->num >0)
		{
			p->num--;
			printf("THE sellwindows 1111 selled  rest is : %d\n",p->num);
			if(p->num ==0)
			{
				pthread_cond_signal(&p->cond);
				sleep(1);
			}
			pthread_mutex_unlock(&p->mutex);
		}else
		{
			pthread_mutex_unlock(&p->mutex);
			break;
		}
//	usleep(5);
	}
	pthread_exit(0);
}

void * Sallwindows2(void *args)
{
	printf("22222222222222222222222\n");
	data *p = (data*)args;
	while(1)
	{
		pthread_mutex_lock(&p->mutex);
		if(p->num >0)
		{
			p->num--;
			printf("THE sellwindows 2222 selled  rest is : %d\n",p->num);
			if(p->num ==0)
			{
				pthread_cond_signal(&p->cond);
				sleep(1);
			}
			pthread_mutex_unlock(&p->mutex);
		}else
		{
			pthread_mutex_unlock(&p->mutex);
			break;
		}
//	usleep(5);
	}
	pthread_exit(0);
}

void* settiket(void *args)
{
	data *p = (data*)args;
	pthread_mutex_lock(&p->mutex);
	pthread_cond_wait(&p->cond,&p->mutex);
	printf("add 20 tiikets NOW SELL BEGIN\n");
	p->num = 10;
	pthread_mutex_unlock(&p->mutex);
	pthread_exit(0);
}

int main()
{
	pthread_t pthid[3];
	threadFunc f[3] ={Sallwindows1,Sallwindows2,settiket};
	data info ;
	info.num = 100;
	pthread_mutex_init(&info.mutex,NULL);
	pthread_cond_init(&info.cond,NULL);
	for(int i =0;i<3;i++)
	{
		int ret	= pthread_create(pthid+i,NULL,f[i],(void*)&info);
		THREAD_ERROR_CHECK(ret,"pthread_create" );
	}
	for(int i =0;i<3;i++)
	{
		pthread_join(pthid[i],NULL);
	}
	pthread_mutex_destroy(&info.mutex);
	pthread_cond_destroy(&info.cond);
	printf("SELL BE END\n");
	return 0;
}
	
