#include<func.h>

int main()
{
	int fd = open("file",O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	char *p = (char*)calloc(1,100);
	strcpy(p,"ORINGE duiqu");
	int ret = fork();
	if(ret == 0)
	{
		printf("I am son process \n");
		printf("p = %p ,arr = %s\n",p,p);
		write(fd,&"SCENCD write",12);
		close(fd);
	}
	else
	{
		printf("I am parent process \n");
		strcpy(p,"CHANGE duiqu");
		printf("p = %p ,arr = %s\n",p,p);
		write(fd,&"First write\n",12);
		close(fd);
		sleep(1);
	}
	return 0;
}



