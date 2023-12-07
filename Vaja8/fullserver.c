#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

 int destport = 0;
 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void *receiveMessages(void *socketDescriptor)
{
    int sock = *(int *)socketDescriptor;
    char buf[1024];
    struct sockaddr_in from;
    socklen_t fromlen = sizeof(struct sockaddr_in);

    while (1)
    {
        int n = recvfrom(sock, buf, 1024, 0, (struct sockaddr *)&from, &fromlen);
        if (n < 0)
            error("recvfrom");

        printf("Received a datagram:%s\n ", buf);
        printf("%d",ntohs(from.sin_port));
        destport = ntohs(from.sin_port);
        
        
        if (buf[0] == 'X')
            break;
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{   
    int sock, length, n;
    struct sockaddr_in server, from, dest; // Added dest variable
    socklen_t fromlen;
    char buf[1024];

    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(0);
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0)
        error("Opening socket");

    length = sizeof(server);
    bzero(&server, length);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    if (bind(sock, (struct sockaddr *)&server, length) < 0)
        error("binding");

    fromlen = sizeof(struct sockaddr_in);

    pthread_t sprejem;
    if (pthread_create(&sprejem, NULL, receiveMessages, (void *)&sock) != 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // Initialize destination address
    bzero(&dest, sizeof(dest));
    dest.sin_family = AF_INET;
    //dest.sin_port = htons(atoi(argv[1])); // Use the same port as the server
    dest.sin_port = htons(atoi(argv[2]));
    dest.sin_addr.s_addr =INADDR_ANY; /* Set the destination IP address, e.g., INADDR_LOOPBACK for localhost */;

    while (1)
    {
        printf("Please enter the message: ");
        bzero(buf, 1024);
        fgets(buf, 1024, stdin);
        printf("Sent %s \n", buf);

        // Use 'dest' for the sendto call
        n = sendto(sock, buf, 1024, 0, (struct sockaddr *)&dest, sizeof(dest));
        if (n < 0)
            error("sendto");
        if (buf[0] == 'X')

            break;
            pthread_exit(NULL);
    }
    pthread_join(sprejem, NULL);

    close(sock);
    return 0;
}
