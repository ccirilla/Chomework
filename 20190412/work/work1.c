
#include<func.h>

typedef struct student{
	int id;
	char name[20];
	float sore;
}Stu,*pStu;

int main(int argc ,char *argv[])
{
	ARGS_CHECK(argc,2);
	int fd = open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	Stu s[3] ={{1001,"lele",85.4},{1002,"zhangjing",99.9},{1003,"theshay",77.3}};
	write(fd,s,sizeof(s));
	memset(s,0,sizeof(s));
	lseek(fd,0,SEEK_SET);
	read(fd,s,sizeof(s));
	for(int i =0;i<3;i++)
		printf("%d %s %lf\n",s[i].id,s[i].name,s[i].sore);
	return 0;
}

