#include "func.h"

int make_child(process_data *pChlid,int child_num)
{
	int i;
	pid_t pid;
	int fds[2];
	int ret;
	for(i = 0;i < child_num;i++)
	{
		ret = socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
		ERROR_CHECK(ret,-1,"socketpair");
		pid = fork();
		if(pid == 0)
		{
			close(fds[1]);
			child_handle(fds[0]);
		}
		else
		{
			pChlid[i].pid = pid;
			pChlid[i].fd = fds[1];
			pChlid[i].busy = 0;
			close(fds[0]);
		}
	}
	return 0;
}

int child_handle(int fd)
{
	int new_fd,exit_flag;
	while(1)
	{
		recv_fd(fd,&new_fd,&exit_flag);
        if(0 == exit_flag)
        {
            exit(0);
        }
		tran_file(new_fd);
		close(new_fd);
		write(fd,&new_fd,4);
	}
	return 0;
}
