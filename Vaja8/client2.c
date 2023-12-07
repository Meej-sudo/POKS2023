/* Creates datagram UDP client in the internet domain. */
/* IP address and port are passed as argument */
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>

void error(const char *msg) {           //MANJKA 2
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
   struct hostent *hp;                       //MANJKA 2
   int sock, length, n;                       //MANJKA 2
   struct sockaddr_in server, from;                       //MANJKA 2
   socklen_t fromlen;                       //MANJKA 2
   char buf[1024];                       //MANJKA 2
   
   if(argc != 3) { 
      printf("Usage: client IP port\n");
      exit(1);
   }

   sock= socket(AF_INET, SOCK_DGRAM, 0);

   if(sock < 0) error("socket");

   server.sin_family = AF_INET;
   hp = gethostbyname(argv[1]);

   if(hp==0) error("Unknown host");

   //bcopy((char *)hp->h_addr, (char *)&server.sin_addr, hp->h_length);
   server.sin_port = htons(atoi(argv[2]));
   length=sizeof(struct sockaddr_in);

   while(1){                        //MANJKA 3
      printf("Please enter the message: ");
      bzero(buf,1024);
      fgets(buf,1024,stdin);
      printf("Send %s \n", buf);
      n=sendto(sock,buf,1024,0,(const struct sockaddr *)&server,length);
      if(n < 0) error("Sendto");

      if(buf[0] == 'X')                           //MANJKA 3 in 4
        break;

      n = recvfrom(sock,buf,1024,0,(struct sockaddr *)&server, &length);           //MANJKA 5
       if(n < 0) error("recvfrom");
       printf("Received a datagram:%s\n ",buf);

       if(buf[0] == 'X')                          //MANJKA 3 in 4
        break;
   }
   
   close(sock);
   return 0;
}
