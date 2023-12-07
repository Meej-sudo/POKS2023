#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void *receiveMessages(void *socketDescriptor)
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0)
        error("socket");

    struct sockaddr_in client;
    socklen_t fromlen = sizeof(struct sockaddr_in);

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(5067); // Let the OS choose a random port for receiving

    if (bind(sock, (struct sockaddr *)&client, sizeof(client)) < 0)
        error("binding");

    char buf[1024];

    while (1)
    {
        int n = recvfrom(sock, buf, 1024, 0, (struct sockaddr *)&client, &fromlen);
        if (n < 0)
            error("recvfrom");

        printf("Received a datagram:%s\n ", buf);

        if (buf[0] == 'X')
            break;
    }

    close(sock);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    struct hostent *hp;
    int sock, length, n;
    struct sockaddr_in server;
    socklen_t fromlen;
    char buf[1024];

    if (argc != 3)
    {
        printf("Usage: client IP port\n");
        exit(1);
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0)
        error("socket");

    server.sin_family = AF_INET;
    hp = gethostbyname(argv[1]);
    server.sin_port = htons(atoi(argv[2]));
    length = sizeof(struct sockaddr_in);

    pthread_t sprejem;
    if (pthread_create(&sprejem, NULL, receiveMessages, NULL) != 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        printf("Please enter the message: ");
        bzero(buf, 1024);
        fgets(buf, 1024, stdin);
        printf("Send %s \n", buf);
        n = sendto(sock, buf, 1024, 0, (const struct sockaddr *)&server, length);
        if (n < 0)
            error("Sendto");

        if (buf[0] == 'X')
            break;
    }

    pthread_join(sprejem, NULL);

    close(sock);
    return 0;
}
