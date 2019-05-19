#include<func.h>

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,4);
	int ret = execl(argv[1],"啊哈，I am Begin！",argv[2],argv[3],NULL);
	ERROR_CHECK(ret,-1,"execl");
	return 0;
}
