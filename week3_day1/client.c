#include <func.h>

int tcp_connect(char *ip,int port)
{
	int cfd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in seraddr;
	bzero(&seraddr,sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(port);
	seraddr.sin_addr.s_addr = inet_addr(ip);
	int ret = connect(cfd,(struct sockaddr*)&seraddr,sizeof(seraddr));
	if(ret == -1)
	{
		perror("connect");
		exit(-1);
	}
	return cfd;
}

int main(int argc, char *argv[])
{
	ARGS_CHECK(argc,3);
	int cfd = tcp_connect(argv[1],atoi(argv[2]));
	int ret ;
	char buf[256] = {0};
	fd_set rdset;
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(STDIN_FILENO,&rdset);
		FD_SET(cfd,&rdset);
		ret = select(cfd+1,&rdset,NULL,NULL,NULL);
		if(ret>0)
		{
			if(FD_ISSET(cfd,&rdset))
			{
				bzero(buf,sizeof(buf));
				ret = recv(cfd,buf,sizeof(buf),0);
				printf("%s\n",buf);
				if(ret == 0)
					break;
			}
			if(FD_ISSET(STDIN_FILENO,&rdset))
			{
				 bzero(buf,sizeof(buf));
				 ret=read(0,buf,sizeof(buf));
				 if(ret == 0)
					 break;
				 send(cfd,buf,strlen(buf)-1,0);
			}
		}
	}
	printf("bye  bye ~~~\n");
	close(cfd);
	return 0;
}

