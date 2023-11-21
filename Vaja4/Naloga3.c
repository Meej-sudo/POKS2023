#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *fun1();

int stevec = 0;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

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
      pthread_mutex_lock(&mutex1);
      stevecint = stevec;
      stevecint++;
      for (n = 0; n < 100; n++) {
         int a = 2*32/5;
         usleep(1);
      }
      stevec = stevecint;
      pthread_mutex_unlock(&mutex1);
   }

}
