#include<func.h>

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,3);
	printf("%s\n",argv[0]);
	printf("%s + %s = %d\n啊哈，溜了溜了！",argv[1],argv[2],atoi(argv[1])+atoi(argv[2]));
	return 0;
}
