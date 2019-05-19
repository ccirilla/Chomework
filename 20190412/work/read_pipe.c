#include<func.h>

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,3);
	int fdr = open(argv[1],O_RDONLY);
	int fdw = open(argv[2],O_WRONLY);
	ERROR_CHECK(fdr,-1,"open");
	ERROR_CHECK(fdw,-1,"open1");
	char buf[512]={"0"};
	printf("来啊，快活呀\n");
	fd_set rdset;
	int ret;
	struct timeval t;
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(STDIN_FILENO,&rdset);
		FD_SET(fdr,&rdset);
		t.tv_sec = 5;
		ret = select(fdr+1,&rdset,NULL,NULL,&t);
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
				ret=read(0,buf,sizeof(buf));
				if(ret == 0)
				{
					printf("不玩了，溜了溜了！\n");
					break;
				}
				write(fdw,buf,strlen(buf)-1);
			}
		}else
			printf("能不能快点嘛···\n");
	}
	close(fdr);
	close(fdw);
	return 0;
}


