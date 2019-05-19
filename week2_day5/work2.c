#include <func.h>

void cleanup(void *p)
{
	printf("I am cleanup \n");
	free((char*)p);
	return ;
}

void * threadFunc(void *s)
{
	printf("I am child thread\n");
	char *p = (char*)malloc(100);
	pthread_cleanup_push(cleanup,p);
	read(0,p,100);
	pthread_cleanup_pop(1);
	pthread_exit(0);
}

int main()
{
	pthread_t pthid;
	int ret	= pthread_create(&pthid,NULL,threadFunc,NULL);
	THREAD_ERROR_CHECK(ret,"pthread_create" );
	usleep(1000);
	pthread_cancel(pthid);
	pthread_join(pthid,(void**)&ret);
	printf("I am main thread ret = %d\n",ret);
	return 0;
}
	
