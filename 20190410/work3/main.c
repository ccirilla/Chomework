#include<ssss.h>
int add(int,int);
int main(void)
{
#ifdef DEBUG
	printf("I am DEBUG\n");
#endif
	int a = add(3,4);
	printf("a = %d\n",a);
	return 0;
}

