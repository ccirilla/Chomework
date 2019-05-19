#include <func.h>

void changeBonBlock(int fd)
{
	int status = fcntl(fd,F_GETFL);
	status = status | O_NONBLOCK;
	fcntl(fd,F_SETFL,status);
}

int main(int argc ,char *argv[])
{
	ARGS_CHECK(argc,3);
	int sfd = socket(AF_INET,SOCK_STREAM,0);
	int reuse = 1;
	setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family = AF_INET;
	ser.sin_port = htons(atoi(argv[2]));
	ser.sin_addr.s_addr = inet_addr(argv[1]);
	int ret = bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
	ERROR_CHECK(ret,-1,"bind");
	listen(sfd,10);
	char buf[128];
	int new_sfd;
	int epfd = epoll_create(1);
	ERROR_CHECK(epfd,-1,"epoll_create");
	struct epoll_event event,evs[3];
	event.events = EPOLLIN;
	event.data.fd = STDIN_FILENO;
    ret = epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
	event.data.fd = sfd;
    ret = epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
	while(1)
	{
		int readnum = epoll_wait(epfd,evs,3,-1);
		for(int i =0;i<readnum;i++)
		{
			if(evs[i].data.fd == sfd)
			{
				new_sfd = accept(sfd,NULL,NULL);
				printf("connect sucessful!\n");
				event.events = EPOLLIN|EPOLLET;
				changeBonBlock(new_sfd);
				event.data.fd = new_sfd;
   			    ret = epoll_ctl(epfd,EPOLL_CTL_ADD,new_sfd,&event);
			}
			if(evs[i].data.fd == new_sfd)
			{
				while(1)
				{		
					bzero(buf,sizeof(buf));
					ret = recv(new_sfd,buf,5,0);
					if(ret == 0)
					{
						event.events = EPOLLIN|EPOLLET;
						event.data.fd = new_sfd;
   			    		epoll_ctl(epfd,EPOLL_CTL_DEL,new_sfd,&event);
						close(new_sfd);
						printf("BYE ~ BYE!\n");
						break;
					}else if(ret ==-1)
					{
						printf("\n");
						break;
					}else{
						printf("%s",buf);
					}
				}
			}
			if(evs[i].data.fd == STDIN_FILENO)
			{
				bzero(buf,sizeof(buf));
				ret = read(STDIN_FILENO,buf,sizeof(buf));
				if(ret == 0)
					goto end;
				send(new_sfd,buf,strlen(buf)-1,0);
			}
		}
	}
end:
	close(sfd);
	close(epfd);
	return 0;
}







