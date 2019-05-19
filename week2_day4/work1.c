#include <func.h>

int seq = 0;
void SighHandler(int SighNo)
{
	seq++;
	printf("%d Enter SighHandler,signo: %d\n",seq,SighNo);
	sleep(3);
	printf("%d Leave  SighHandler,signo: %d\n",seq,SighNo);
}
int main(void)
{
	if(signal(SIGINT,SighHandler)==SIG_ERR)
		perror("signal");
	if(signal(SIGQUIT,SighHandler)==SIG_ERR)
		perror("signal");
	while(1);
}

