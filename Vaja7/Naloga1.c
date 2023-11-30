#include<stdio.h>
#include<pthread.h>
#include<string.h>
#define MAX_MSG 10
#define MAX_MSG_LEN 100

void fun1(void);

char vrsta [MAX_MSG][MAX_MSG_LEN];
int vpis = 0;
int branje = 0;

int main(){
    pthread_t nit1, nit2;
    pthread_create(&nit1, NULL, (void*)fun1, NULL);

    pthread_join(nit1, NULL);
    printf("Konec \n");
}

void fun1(void){
    char MESSAGE [MAX_MSG_LEN] = "AAAAAAAAAAAAAAA\0";
    char MESSAGEX [MAX_MSG_LEN] = "XXXXXXXXXXXXXXX\0";
    int i;

    vpis = 0;
    branje = 0;
    printf("Nit 1 zacela - sender\n");
    for(i=0;i<15;i++)
    {
        sleep(1);
        while(((vpis + 1) % MAX_MSG)== branje);
        strcpy(vrsta[vpis], MESSAGE);
        printf("Nit1 posilja %d: %s \n", i, (char *) &MESSAGE);
        vpis = (vpis + 1) % MAX_MSG;
        MESSAGE[0]++;
    }
        printf("Nit1 posilja %d: %s \n", i, (char *) &MESSAGEX);
        strcpy(vrsta[vpis], MESSAGEX);
        printf("Nit1 zakljucena\n");

}

void fun2(void){
    char msgBuff[MAX_MSG_LEN];
    printf("Nit2 se zacenja - sprejem \n");
    sleep(5);
    while(1)
    {
        while(vpis == branje);
        //strcpy();
        pritnf("Nit2 je sprejela: %s Branje=%d Vpis=%d\n", msgBuff, branje, vpis);
        //branje;
        if(msgBuff[0]=='X')
        {
            printf("Nit2 je zakljucila");
        }
    }


}
