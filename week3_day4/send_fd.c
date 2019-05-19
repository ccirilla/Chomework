#include "func.h"

int send_fd(int fd,int new_fd,int exit_flag)
{
	struct msghdr msg;
	bzero(&msg,sizeof(msg));
	int buf1 = exit_flag;
	char buf2[10] = {"world"};
	struct iovec iov[2];
	iov[0].iov_base = &buf1;
	iov[0].iov_len = sizeof(int);
	iov[1].iov_base = buf2;
	iov[1].iov_len = 5;
	msg.msg_iov = iov;
	msg.msg_iovlen = 2;
	int len = CMSG_LEN(sizeof(int));
	struct cmsghdr *cmsg = (struct cmsghdr *)calloc(1,len);
	cmsg->cmsg_len = len;
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	*(int*)CMSG_DATA(cmsg) = new_fd;
	msg.msg_control = cmsg;
	msg.msg_controllen = len;
	int ret;
	ret = sendmsg(fd,&msg,0);
	ERROR_CHECK(ret,-1,"sendmsg");
	return 0;
}

int recv_fd(int fd,int *new_fd,int *exit_flag)
{
	struct msghdr msg;
	bzero(&msg,sizeof(msg));
	int buf1;
	char buf2[10];
	struct iovec iov[2];
	iov[0].iov_base = &buf1;
	iov[0].iov_len = sizeof(int);
	iov[1].iov_base = buf2;
	iov[1].iov_len = 5;
	msg.msg_iov = iov;
	msg.msg_iovlen = 2;
	int len = CMSG_LEN(sizeof(int));
	struct cmsghdr *cmsg = (struct cmsghdr *)calloc(1,len);
	cmsg->cmsg_len = len;
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	msg.msg_control = cmsg;
	msg.msg_controllen = len;
	int ret;
	ret = recvmsg(fd,&msg,0);
	ERROR_CHECK(ret,-1,"recvmsg");
	*new_fd = *(int*)CMSG_DATA(cmsg);
    *exit_flag = *(int*)(msg.msg_iov[0].iov_base);
	return 0;
}
