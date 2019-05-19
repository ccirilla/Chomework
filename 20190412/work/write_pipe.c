#include<func.h>

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,3);
	int fdw = open(argv[1],O_WRONLY);
	int fdr = open(argv[2],O_RDONLY);
	ERROR_CHECK(fdr,-1,"open");
	ERROR_CHECK(fdw,-1,"open1");
	char buf[512]={"0"};
	printf("read fdw = %d,fdr = %d\n",fdw,fdr);
	fd_set rdset;
	struct timeval t;
	int ret;
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(STDIN_FILENO,&rdset);
		FD_SET(fdr,&rdset);
		ret = select(fdr+1,&rdset,NULL,NULL,&t);
		t.tv_sec = 5;
		if(ret>0)
		{
			if(FD_ISSET(fdr,&rdset))
			{
				memset(buf,0,sizeof(buf));
				ret =read(fdr,buf,sizeof(buf));
				if(ret == 0)
				{
					printf("不玩了，溜了溜了！\n");
					break;
				}
				printf("%s\n",buf);
			}
			if(FD_ISSET(STDIN_FILENO,&rdset))
			{
				memset(buf,0,sizeof(buf));
				ret =	read(0,buf,sizeof(buf));
				if(ret == 0)
				{
					printf("不玩了，溜了溜了！\n");
					break;
				}
				write(fdw,buf,strlen(buf)-1);
			}
		}else
			printf("急啥子呦\n");
	}
	close(fdr);
	close(fdw);
	return 0;
}


