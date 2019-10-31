#ifndef SYSUTIL_H
#define SYSUTIL_H

#include "common.h"
//输出当前的主机ip，成功返回0
//失败返回-1
int getlocalip(char *ip);
//设置io为非阻塞
void activate_nonblock(int fd);
//设置io为阻塞
void deactivate_nonblock(int fd);
//用于判断是否有读事件发生
int read_timeout(int fd,unsigned int wait_seconds);
//用于判断是否有写事件发生
int write_timeout(int fd,unsigned int wait_seconds);
//带超时检测的accept操作
int accept_timeout(int fd,struct sockaddr_in *addr,unsigned int wait_seconds);
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
#endif
