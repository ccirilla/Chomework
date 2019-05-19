#include "func.h"

int tcp_init(int * Psocket_fd,char *ip,char *port)
{
	int socket_fd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family = AF_INET;
	ser.sin_port = htons(atoi(port));
	ser.sin_addr.s_addr = inet_addr(ip);
	int ret = bind(socket_fd,(struct sockaddr*)&ser,sizeof(ser));
	ERROR_CHECK(ret,-1,"bind");
	listen(socket_fd,100);
	*Psocket_fd = socket_fd;
	return 0;
}	
