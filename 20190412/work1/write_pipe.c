#include<func.h>

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,3);
	int fdw = open(argv[1],O_WRONLY);
	int fdr = open(argv[2],O_RDONLY);
	ERROR_CHECK(fdr,-1,"open");
	ERROR_CHECK(fdw,-1,"open1");
	char buf[512]={"0"};
	printf("write fdw = %d,fdr = %d\n",fdw,fdr);
	while(1)                                    
	{
		memset(buf,0,sizeof(buf));
	    read(0,buf,sizeof(buf));
		write(fdw,buf,strlen(buf)-1);
		memset(buf,0,sizeof(buf));
		read(fdr,buf,sizeof(buf));
		printf("%s\n",buf);
	}            
	return 0;
}


