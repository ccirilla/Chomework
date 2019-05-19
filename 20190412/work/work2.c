#include<func.h>

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	int fd = open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	struct stat buf;
	fstat(fd,&buf);
	char *p;
	p =(char*) mmap(NULL,buf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	ERROR_CHECK(p,(char *)-1,"mmap");
	strcpy(p,"world");
	munmap(p,buf.st_size);
	return 0;
}

