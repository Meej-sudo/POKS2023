#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <errno.h>
#include <mqueue.h> 
#include "common.h" 
#include <unistd.h>
 
int main() { 
    mqd_t mq; 
    struct mq_attr attr; 
    char buffer[MAX_SIZE + 1]; 
    printf("%s", buffer);
     memset(buffer, 0, sizeof(buffer));

    /* initialize the queue attributes */ 
    attr.mq_flags = 0; 
    attr.mq_maxmsg = MAX_MSGS; 
    attr.mq_msgsize = MAX_SIZE; 
    attr.mq_curmsgs = 0; 
 
    /* create the message queue */ 
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0666, &attr); 
    if (mq == (mqd_t)-1) {
    perror("mq_open \n");
    strerror(errno);
    printf("errno: %d\n",errno);
    exit(EXIT_FAILURE);
}
printf("dela");
    sleep(2);//manjka 1
    while(1) {                                                                     
        sleep(2); //manjka 3
        ssize_t bytes_read; 
        printf("%s",buffer);
        bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL); /* receive message */ 
        if (bytes_read == -1) {
        perror("mq_receive");
            }
        printf("%s\n", buffer);      // manjka 1   
        mq_getattr(mq, &attr);  // manjka 5
        printf("Atributi: flags:%ld curmsgs:%ld \n", attr.mq_flags, attr.mq_curmsgs);   // manjka 5
        if(buffer[1] == MSG_STOP[1]){   // manjka 2                                                              
            break;
        }
    }
    mq_close(mq);   /* cleanup */
    mq_unlink(QUEUE_NAME); 
    return 0; 
}
