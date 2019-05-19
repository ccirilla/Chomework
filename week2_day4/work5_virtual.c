#include <func.h>
time_t start,end;
void sighFunc(int sighid)
{
	time(&end);
	printf("程序已经运行了 %3ld s    %s\n",end-start,ctime(&end)+10);
}
int main()
{
	time(&start);
	signal(SIGVTALRM,sighFunc);
	struct itimerval tm;
	tm.it_value.tv_sec = 3;
	tm.it_value.tv_usec= 0;
	tm.it_interval.tv_sec = 2;
	tm.it_interval.tv_usec= 0;
	setitimer(ITIMER_VIRTUAL,&tm,NULL);
	sleep(5);
	while(1);
}

