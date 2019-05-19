#include <func.h>
int main()
{
	sigset_t at;
	sigemptyset(&at);
	sigaddset(&at,SIGINT);
	sigset_t bt ;
	sigprocmask(SIG_BLOCK,&at,NULL);
	printf("程序开始，有种GAY我\n");
	sleep(5);
	sigpending(&bt);
	if(sigismember(&bt,SIGINT))
		printf("2号信号 is spending\n");
	else
		printf("2号信号 is not spending\n");
	printf("process will be killed!\n");
	sigprocmask(SIG_UNBLOCK,&at,NULL);
	return 0;
}


