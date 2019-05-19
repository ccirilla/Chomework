#include <func.h>

int main(int argc ,char *argv[])
{
	ARGS_CHECK(argc,3);
	int cfd = socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family = AF_INET;
	ser.sin_port = htons(atoi(argv[2]));
	ser.sin_addr.s_addr = inet_addr(argv[1]);
	int ret =sendto(cfd,"1",1,0,(struct sockaddr*)&ser,sizeof(ser));
	ERROR_CHECK(ret,-1,"connect");
	char buf[128];
	socklen_t longth = sizeof(ser);
	int epfd = epoll_create(1);
	ERROR_CHECK(epfd,-1,"epoll_create");
	struct epoll_event event,evs[2];
	event.events = EPOLLIN;
	event.data.fd = STDIN_FILENO;
    ret = epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
	event.data.fd = cfd;
    ret = epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&event);
	while(1)
	{
		int readnum = epoll_wait(epfd,evs,2,-1);
		for(int i =0;i<readnum;i++)
		{
			if(evs[i].data.fd == cfd)
			{
				bzero(buf,sizeof(buf));
				ret = recvfrom(cfd,buf,sizeof(buf),0,
						(struct sockaddr*)&ser,&longth);
				if(ret == 0)
					goto end;
				printf("%s",buf);
				fflush(stdout);
			}
			if(evs[i].data.fd == STDIN_FILENO)
			{
				bzero(buf,sizeof(buf));
				ret = read(STDIN_FILENO,buf,sizeof(buf));
				if(ret == 0)
					goto end;
				sendto(cfd,buf,strlen(buf),0,(struct sockaddr*)&ser,sizeof(ser));
			}
		}
	}
end:
	close(cfd);
	close(epfd);
	return 0;
}







