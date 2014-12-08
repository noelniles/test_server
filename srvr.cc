#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "srvr.h"
 
 
int main (int argc, char **argv)
{
    //int i;
    int listenfd;
    int socketfd;
    ssize_t n;
    char buf[MAXLINE];
    socklen_t clilen;
    struct sockaddr_in cliaddr;
    struct sockaddr_in servaddr;
 
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
 
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
 
    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
 
    listen(listenfd, LISTENQ);
 
    clilen = sizeof(cliaddr);
    socketfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
 
    for (;;)
    {
        bzero(buf, MAXLINE);
        if((n = read(socketfd, buf, MAXLINE)) == 0)
        {
            close(socketfd);
            break;
        }
        else
        {
            fputs(buf, stdout);
            write(socketfd, buf, n);
        }
    }
 
    return 0;
}
