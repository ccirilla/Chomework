#include "func.h"

int recv_cyle(int new_sfd,char *buf,int len)
{
    int totle = 0;
    int ret;
    while(totle < len)
    {
        ret = send(new_sfd,buf+totle,len-totle,0);
        totle += ret;
    }
    return 0;
}

