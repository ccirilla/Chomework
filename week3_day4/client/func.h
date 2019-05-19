
#include <sys/epoll.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <strings.h>
#include <time.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<sys/wait.h>
#include <fcntl.h>
#include<syslog.h>
#include<sys/select.h>
#include<sys/time.h>
#include<sys/mman.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include<dirent.h>

#define ARGS_CHECK(argc,val){if(argc!=val){printf("error args\n");return -1;}}

#define ERROR_CHECK(ret,retval,funcName) \
	{if(ret==retval){printf("%d :",__LINE__);fflush(stdin);perror(funcName);return -1;}}

#define THREAD_ERROR_CHECK(ret,threadFunc){ if(ret !=0) \
	{printf("%s:%s",threadFunc,strerror(ret));return -1;}}

typedef struct {
	pid_t pid;
	int fd;
	short busy;
}process_data;

typedef struct {
	int data_len;
	char buf[2000];
}train_t;

#define FILENAME "file"

int  make_child(process_data *pChlid,int child_num);
int child_handle(int);
int tcp_init(int*,char*,char*);
int send_fd(int fd,int new_fd);
int recv_fd(int fd,int *new_fd);
int tran_file(int);
