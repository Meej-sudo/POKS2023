#include <stdio.h>
#include <pthread.h>

void *fun1();

int stevec = 0;

int main() {
   
   pthread_t thread1, thread2;


   pthread_create(&thread1, NULL, &fun1, NULL);
   pthread_create(&thread2, NULL, &fun1, NULL);

   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL);
      
   printf("Konec, Rezultat = %d\n", stevec);
   return(1);
}

void *fun1(){
   int stevecint = 0;
   int i,n;
   for (i = 0; i < 2000; i++) {
      stevecint = stevec;
      stevecint++; 
      for (n = 0; n < 5000; n++) {
         int a = 2*32/5;
         // sleep(1);
      }
      stevec = stevecint;
   }

}
