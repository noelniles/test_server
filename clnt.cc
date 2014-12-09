#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "clnt.h"


int main (int argc, char **argv)
{
    //int i;
    int sockfd;
    struct sockaddr_in servaddr;
    char sendline[MAXLINE];
    char recvline[MAXLINE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    while(fgets(sendline, MAXLINE, stdin) != NULL)
    {
        write(sockfd, sendline, strlen(sendline));

        bzero(recvline, MAXLINE);

        if (read(sockfd, recvline, MAXLINE) == 0)
        {
            perror("Server terminated prematurely");
            exit(EXIT_FAILURE);
        }

        fputs(recvline,stdout);
    }

    return 0;
}
