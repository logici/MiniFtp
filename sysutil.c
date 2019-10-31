#include "sysutil.h"

//输出当前的主机ip，成功返回0
//失败返回-1
int getlocalip(char *ip)
{
    char host[100] = {0};
    //返回主机名
    if(gethostname(host,sizeof(host)) < 0)return -1;
    
    struct hostent *hp;
    //由主机名返回hostent结构体，里面有ip地址
    if(hp = gethostbyname(host) == NULL)return -1;
    //进行ip地址的格式转换，由网络字节序转换为字符串的形式
    strcpy(ip,inet_ntoa(*(struct in_addr*)hp->h_addr));
    //成功则返回0
    return 0;
}
//设置io为非阻塞
//fd:输入文件描述符
void activate_nonblock(int fd)
{
    int flags = 0;
    flags = fcntl(fd,F_GETFL);
    if(flags == -1)ERR_EXIT("fcntl");
    flags |= O_NONBLOCK;
    if(fcntl(fd,flags) == -1)ERR_EXIT("fcntl");
}
//设置io为阻塞
//fd:输入文件描述符
void deactivate_nonblock(int fd)
{
     int flags = 0;
    flags = fcntl(fd,F_GETFL);
    if(flags == -1)ERR_EXIT("fcntl");
    flags &= ~O_NONBLOCK;
    if(fcntl(fd,flags) == -1)ERR_EXIT("fcntl");   
}
//用于判断是否有读事件发生
//fd:文件描述符
//wait_seconds:等待的秒数
//秒数为0时，不检测超时
//成功（在限定的时间内读到数据）返回0，
//读取失败返回-1，超时返回-1并且errno=ETIMEDOUT
int read_timeout(int fd,unsigned int wait_seconds)
{
    int ret = 0;
    if(wait_seconds > 0)
    {
        //定义一个读集合
        fd_set readset;
        //清空这个集合进行初始化
        FD_ZERO(&readset);
        //把fd放进这个读集合中
        FD_SET(fd,&readset);
        
        struct timeval tval;
        tval.tv_sec = wait_seconds;
        tval.tv_usec = 0;
        //进行检测，如果ret<0并且是中断的行为，则进行
        //循环，以保证select的运行完整。
        do{
            ret = select(fd + 1,&readset,NULL,NULL,&tval);
        }while(ret < 0 && errno == EINTR);

        //为0则说明超时了
        if(ret == 0){
            ret = -1;
            errno = ETIMEDOUT;
        }
        //该例子中，就只有一个readset，并且只有一个fd,所以判断==1
        else if(ret == 1)
        {
            ret = 0;
        }
    }
    return ret; 
     
}
//用于判断是否有写事件发生
//fd:文件描述符
//wait_seconds:等待的时间
//如果seconds为0，则不进行超时检测
//如果（超时检测）成功则返回0，如果超时了，则返回-1
//并且errno返回ETIMEDOUT
int write_timeout(int fd,unsigned int wait_seconds)
{
     int ret = 0;
    if(wait_seconds > 0)
    {
        //定义一个写集合
        fd_set writeset;
        //清空这个集合进行初始化
        FD_ZERO(&writeset);
        //把fd放进这个写集合中
        FD_SET(fd,&writeset);
        
        struct timeval tval;
        tval.tv_sec = wait_seconds;
        tval.tv_usec = 0;
        //进行检测，如果ret<0并且是中断的行为，则进行
        //循环，以保证select的运行完整。
        do{
            ret = select(fd + 1,NULL,&writeset,NULL,&tval);
        }while(ret < 0 && errno == EINTR);

        //为0则说明超时了
        if(ret == 0){
            ret = -1;
            errno = ETIMEDOUT;
        }
        //该例子中，就只有一个writeset，并且只有一个fd,所以判断==1
        else if(ret == 1)
        {
            ret = 0;
        }
    }
    return ret; 
       
}
//带超时检测的accept操作
//fd:套接字
//addr：输出参数，返回对方的地址
//wait_seconds:时间
//成功返回已连接的套接字，超时返回-1并且errno=ETIMEDOUT
int accept_timeout(int fd,struct sockaddr_in *addr,unsigned int wait_seconds)
{
     int ret = 0;
     socklen_t len = sizeof(struct )
    if(wait_seconds > 0)
    {
        //定义一个读集合
        fd_set writeset;
        //清空这个集合进行初始化
        FD_ZERO(&writeset);
        //把fd放进这个读集合中
        FD_SET(fd,&writeset);
        
        struct timeval tval;
        tval.tv_sec = wait_seconds;
        tval.tv_usec = 0;
        //进行检测，如果ret<0并且是中断的行为，则进行
        //循环，以保证select的运行完整。
        do{
            ret = select(fd + 1,NULL,&writeset,NULL,&tval);
        }while(ret < 0 && errno == EINTR);

        //为0则说明超时了
        if(ret == 0){
            ret = -1;
            errno = ETIMEDOUT;
        }
        //该例子中，就只有一个readset，并且只有一个fd,所以判断==1
        else if(ret == 1)
        {
            ret = 0;
        }
    }
    return ret; 
}
//带超时检测的connect操作
int connect_timeout(int fd,struct sockaddr_in *addr,unsigned int wait_seconds);
//读取固定字节数
ssize_t readn(int fd, void *buf,size_t count);
//发送固定字节数
ssize_t writen(int fd,const void *buf,size_t count);
//查看套接字缓冲区数据，但删除数据
ssize_t recv_peek(int fd, void *buf,size_t len);
//按行读取数据
ssize_t readline(int fd,void *buf,size_t maxline);

