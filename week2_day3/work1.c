#include <func.h>

int main(void)
{
	if(fork())
		exit(0);
	chdir("/");
	setsid();
	umask(0);
	for(int i=0;i<3;i++)
		close(i);
	FILE *fp=fopen("/tmp/log","rb+");
	int i = 0;
	while(1)
	{
		i++;
		sleep(5);
		fprintf(fp,"I have run 5s---------------%d\n",i);
		fflush(fp);
	}
}


