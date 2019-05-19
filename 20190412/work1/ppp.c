#include<func.h>

int main(int argc,char**argv)
{
	int fdr = open(argv[1],O_RDONLY);
	int fdW = open(argv[2],O_WRONLY);
	printf("hahahahha\n");
	return 0;
}
