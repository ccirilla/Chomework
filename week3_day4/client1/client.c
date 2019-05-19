#include <func.h>

int recv_cyle(int new_sfd,void *pbuf,int len)
{
    char *buf = (char*)pbuf;
    int total = 0;
    int ret;
    while(total < len)
    {
        ret = recv(new_sfd,buf+total,len-total,0);
        total += ret;
    }
    return 0;
}

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,3);
	int cfd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family = AF_INET;
	ser.sin_port = htons(atoi(argv[2]));
	ser.sin_addr.s_addr = inet_addr(argv[1]);
	int ret = connect(cfd,(struct sockaddr*)&ser,sizeof(ser));
	ERROR_CHECK(ret,-1,"connect");
    printf("connect sucesesful\n");
    int len;
    off_t file_size,old_size=0,now_size=0,slice_size;
    time_t start,now;
	char buf[2000];
	bzero(buf,sizeof(buf));
	ret = recv_cyle(cfd,&len,4);
	ret = recv_cyle(cfd,buf,len);
	ret = recv_cyle(cfd,&len,4);
	ret = recv_cyle(cfd,&file_size,len);
    printf("文件大小为：%ld\n",file_size);
	int fd = open(buf,O_CREAT|O_WRONLY,0666);
	ERROR_CHECK(fd,-1,"open");
    slice_size = file_size/10000;
    time(&start);
	while(1)
	{
		ret = recv_cyle(cfd,&len,4);
		if(len >0)
		{
			recv_cyle(cfd,buf,len);
			write(fd,buf,len);
            now_size += len;
            if((now_size-old_size)>slice_size)
            {
                printf("\rdownload %5.2lf%%",(float)now_size/file_size*100);
                fflush(stdout);
                old_size = now_size;
            }
		}else
			break;
	}
    time(&now);
	printf("\rdownload  100%%  used time : %ld  \n",now-start);
	close(fd);
	close(cfd);
	return 0;
}

