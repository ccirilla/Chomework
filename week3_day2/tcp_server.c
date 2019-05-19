#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,3);
	int socketFd;
	socketFd=socket(AF_INET,SOCK_STREAM,0);
	ERROR_CHECK(socketFd,-1,"socket");
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);//点分十进制转为32位的网络字节序
	int ret;
	ret=bind(socketFd,(struct sockaddr*)&ser,sizeof(ser));
	ERROR_CHECK(ret,-1,"bind");
	listen(socketFd,10);//缓冲区的大小，一瞬间能够放入的客户端连接信息
	struct sockaddr_in client;
	bzero(&client,sizeof(client));
	int addrlen=sizeof(client);
	char buf[128]={0};
	char name[5][20] = {"0"};
	char sendbuf[150];
	bzero(name,100);
	int new_fd[5]={0};
	int k = 0;
	fd_set rdset;//定义一个集合
	fd_set needMonitorSet;
	FD_ZERO(&needMonitorSet);
	FD_SET(socketFd,&needMonitorSet);
	while(1)
	{
		memcpy(&rdset,&needMonitorSet,sizeof(fd_set));
		ret=select(11,&rdset,NULL,NULL,NULL);
		if(FD_ISSET(socketFd,&rdset))
		{
			new_fd[k]=accept(socketFd,(struct sockaddr*)&client,&addrlen);
			ERROR_CHECK(new_fd[k],-1,"accept");
		//	printf("client ip=%s,port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
			ret=recv(new_fd[k],name[k],20,0);//对端断开，recv得到零
			printf("name: %s have connected\n\n",name[k]);
			ERROR_CHECK(ret,-1,"recv");
			FD_SET(new_fd[k],&needMonitorSet);
			k++;
		}
		for(int i =0;i<5;i++)
		{
			if(FD_ISSET(new_fd[i],&rdset))//判断new_fd是否就绪，如果就绪就读取内容并打印
			{
				bzero(buf,sizeof(buf));
				bzero(sendbuf,sizeof(sendbuf));
				ret=recv(new_fd[i],buf,sizeof(buf),0);//对端断开，recv得到零
				ERROR_CHECK(ret,-1,"recv");
				if(0==ret)
				{
					printf("byebye\n");
					FD_CLR(new_fd[i],&needMonitorSet);
					close(new_fd[i]);
					continue;
				}
				sprintf(sendbuf,"%s : %s",name[i],buf);
				for(int j =0;j<5;j++)
				{
					if(i!=j)
					{
						send(new_fd[j],sendbuf,strlen(sendbuf),0);
					}
				}
			}
		}
	}
	close(socketFd);
	return 0;
}
