#include<func.h>

int main (void)
{
	printf( "pid = %d ; ppid = %d\n",getpid(),getppid());
	printf( "UID = %d ;  GID = %d\n",getuid(),getgid());
	printf("EUID = %d ; EGID = %d\n",geteuid(),getegid());
}
