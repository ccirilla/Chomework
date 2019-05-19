#include <func.h>

int  main(void)
{
	char buf[128] = {0};
	int fds[2] = {0};
	int ret = pipe(fds);
	ERROR_CHECK(ret,-1,"pipe");
	if(!fork())
	{
		close(fds[0]);
		strcpy(buf,"Hello");
		write(fds[1],buf,strlen(buf));
		close(fds[1]);
		exit(0);
	}else
	{
		close(fds[1]);
		while(waitpid(-1,NULL,WNOHANG)<=0)
			sleep(1);
		read(fds[0],buf,sizeof(buf));
		printf("%s\n",buf);
		close(fds[0]);
		return 0;
	}
}
