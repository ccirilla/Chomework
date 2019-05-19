#include "func.h"
int exit_fds[2];
void sigh_func(int sigh)
{
    write(exit_fds[1],&sigh,1);
}

int main(int argc, char *argv[])
{
    while(fork())
    {
        int status;
        wait(&status);
        if(WIFEXITED(status))
        {
            printf("process exit normal\n");
            exit(0);
        }
    }
    ARGS_CHECK(argc,4);
    pipe(exit_fds);
    signal(SIGUSR1,sigh_func);
    int child_num = atoi(argv[3]);
    process_data *pChild = (process_data *)calloc(child_num,sizeof(process_data));
    make_child(pChild,child_num);
    int socket_fd;
    int i,j,ret;
    tcp_init(&socket_fd,argv[1],argv[2]);
    int epfd = epoll_create(1);
    struct epoll_event event,evs[child_num + 2];
    event.events = EPOLLIN;
    event.data.fd = socket_fd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,socket_fd,&event);
    event.data.fd = exit_fds[0];
    epoll_ctl(epfd,EPOLL_CTL_ADD,exit_fds[0],&event);
    for(i=0;i<child_num;i++)
    {
        event.data.fd = pChild[i].fd;
        epoll_ctl(epfd,EPOLL_CTL_ADD,pChild[i].fd,&event);
    }
    while(1)
    {
        int read_num = epoll_wait(epfd,evs,child_num+2,-1);
        for(i=0;i<read_num;i++)
        {
            if(evs[i].data.fd == socket_fd)
            {
                int new_fd = accept(socket_fd,NULL,NULL);
                for(j = 0;j<child_num;j++)
                {
                    if(pChild[j].busy == 0)
                    {
                        ret = send_fd(pChild[j].fd,new_fd,1);
                        ERROR_CHECK(ret,-1,"send_fd");
                        printf("%d chilid is busy \n",pChild[j].pid);
                        pChild[i].busy = 1;
                        break;
                    }
                }
                close(new_fd);
            }else if(evs[i].data.fd == exit_fds[0])
            {
                printf("strat quit\n");
                close(socket_fd);
                for(j=0;j<child_num;j++)
                {
                    ret = send_fd(pChild[j].fd,0,0);
                }
                for(j=0;j<child_num;j++)
                {
                    wait(NULL);
                }
                printf("qiut finish\n");
                return 0;
            }else
            {
                for(j = 0;j<child_num;j++)
                {
                    if(evs[i].data.fd == pChild[j].fd)
                    {
                        read(pChild[j].fd,&ret,4);
                        printf("%d chilid is not busy \n",pChild[j].pid);
                        pChild[j].busy = 0;
                        break;
                    }
                }
            }
        }
    }
 return 0;
}

