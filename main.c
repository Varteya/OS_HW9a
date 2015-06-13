#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    printf("Write IP: ");
    char adr[16];
    scanf("%s", adr);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = inet_addr(adr);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }

    printf("Please, write your string: ");
    char message[256];
    scanf("%s", message);
    char buf[strlen(message)];

    send(sock, message, strlen(message), 0);
    recv(sock, buf, strlen(message), 0);

    printf("Your relult: ");
    printf(buf);
    close(sock);

    return 0;
}