#include "common.h"
#include <stdlib.h>  // manjka 1
#include <stdio.h> // manjka 1
#include <string.h> // manjka 1
#include <mqueue.h> 
#include <unistd.h>
int main()
{
mqd_t mq;
char MESSAGE[MAX_SIZE]="AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\0";
/* open the mail queue */
int i;
mq = mq_open(QUEUE_NAME,O_WRONLY);
if (mq == (mqd_t)-1) {
    perror("mq_open");
    exit(EXIT_FAILURE);
}
for (i=0;i<15;i++)
{sleep(1);
mq_send(mq, MESSAGE, 128, 0); /* send the message */
printf("%s\n", MESSAGE);
//sleep();
}
mq_send(mq, MSG_STOP, MAX_SIZE, 0);
mq_close(mq);
return 0;
}
