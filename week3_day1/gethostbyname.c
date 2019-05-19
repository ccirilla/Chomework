#include<func.h>

int main(int argc,char *argv[])
{
	struct hostent *ph;
	ph = gethostbyname(argv[1]);
	printf("%s\n",ph->h_name);
	int i =0;
	for(;ph->h_aliases[i]!=NULL;i++)
		printf("%s\n",ph->h_aliases[i]);
	printf("%d\n",ph->h_addrtype);
	printf("%d\n",ph->h_length);
	char *addr;
	for(i=0;ph->h_addr_list[i]!=NULL;i++)
	{
		addr = inet_ntoa(*((struct in_addr *)ph->h_addr_list[i]));
		printf("%s\n",addr);
	}
	return 0;
}

