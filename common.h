#ifndef COMMON_H
#define COMMON_H

#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#define ERR_EXIT(m) \
    do\
{\
    perror(m);\
    exit(EXIT_FAILURE);\
    }\
while(0)
#endif
