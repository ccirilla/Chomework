#include <func.h>

int tcp_init(char *ip,int port)
{
	int sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1)
	{
		perror("socket");
		exit(-1);
	}
	struct sockaddr_in my_addr;
	bzero(&my_addr,sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(port);
	my_addr.sin_addr.s_addr = inet_addr(ip);
	int ret = bind(sfd,(struct sockaddr*) &my_addr,sizeof(my_addr));
	if(ret == -1)
	{
		perror("bind");
		exit(-1);
	}
	listen(sfd,10);
	return sfd;
}

int tcp_accept(int sfd)
{
	struct sockaddr_in clientaddr;
	socklen_t a = sizeof(clientaddr);
	int new_sfd = accept(sfd,(struct sockaddr*) &clientaddr,&a);
	if(new_sfd == -1)
	{
		perror("accept");
		exit(-1);
	}
	printf("connect suceseful \nThe client ip: %s    The client port : %d\n",
			inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
	return new_sfd;
}

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,3);
	int old_sfd = tcp_init(argv[1],atoi(argv[2]));
	int sfd = tcp_accept(old_sfd);
	int ret;
	char buf[256] = {0};
	fd_set rdset;
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(STDIN_FILENO,&rdset);
		FD_SET(sfd,&rdset);
		ret = select(sfd+1,&rdset,NULL,NULL,NULL);
		if(ret>0)
		{
			if(FD_ISSET(sfd,&rdset))
			{
				bzero(buf,sizeof(buf));
				ret = recv(sfd,buf,sizeof(buf),0);
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
				 send(sfd,buf,strlen(buf)-1,0);
			}
		}
	}
	printf("BYE ~~BYE\n");
	close(sfd);
	close(old_sfd);
	return 0;
}
