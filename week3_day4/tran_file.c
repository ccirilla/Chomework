#include "func.h"

int tran_file(int new_fd)
{
	int ret;
	train_t train;
	train.data_len = strlen(FILENAME);
	strcpy(train.buf,FILENAME);
	ret = send(new_fd,&train,4+train.data_len,0);
	ERROR_CHECK(ret,-1,"send");
	int fd = open(FILENAME,O_RDONLY);
	ERROR_CHECK(fd,-1,"open");
    struct stat ss;
    fstat(fd,&ss);
    train.data_len = sizeof(ss.st_size);
    memcpy(train.buf,&ss.st_size,sizeof(ss.st_size));
	ret = send(new_fd,&train,4+train.data_len,0);
	ERROR_CHECK(ret,-1,"send");
	while( (ret = read(fd,train.buf,sizeof(train.buf))) )
	{
		train.data_len = ret;
		ret = send(new_fd,&train,4+train.data_len,0);
	    ERROR_CHECK(ret,-1,"send");
	}
	train.data_len = 0;
	ret = send(new_fd,&train,4+train.data_len,0);
	ERROR_CHECK(ret,-1,"send");
	return 0;
}



	

