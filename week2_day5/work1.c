#include <func.h>
void * threadFunc(void *p)
{
	printf("I am child thread : i = %d\n",(int)p);
	pthread_exit((void*)2);
}

int main()
{
	pthread_t pthid;
	int ret	= pthread_create(&pthid,NULL,threadFunc,(void*)1);
	THREAD_ERROR_CHECK(ret,"pthread_create" );
	pthread_join(pthid,(void**)&ret);
	printf("I am main thread ret = %d\n",ret);
	return 0;
}
	
