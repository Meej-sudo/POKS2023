#include <stdio.h>
#include <pthread.h>

void *fun1();
void *fun2();
void *fun3();

struct arg_struct {
   int arg1;
   int arg2;
};



main() {
   
   pthread_t thread1, thread2, thread3;

   struct arg_struct args1, args2, args3;
   args1.arg1 = 50;
   args1.arg2 = 20;
   args2.arg1 = 40;
   args2.arg2 = 23;
   args3.arg1 = 12;
   args3.arg2 = 22;

   int R = 0;
   int AB;
   int CD;
   int EF;

   pthread_create(&thread1, NULL, &fun1, (void *)&args1);
   pthread_create(&thread2, NULL, &fun2, (void *)&args2);
   pthread_create(&thread3, NULL, &fun3, (void *)&args3);

   pthread_join(thread1, (void **)&AB);
   printf("%d\n", AB);
   pthread_join(thread2, (void **)&CD);
   printf("%d\n", CD);
   pthread_join(thread3, (void **)&EF);
   printf("%d\n", EF);

   R = AB * CD * EF;
      
   printf("Konec, Rezultat = %d\n", R);
   return(1);
}

void *fun1(void * arguments){
   struct arg_struct *args = arguments;
   int AB = (args -> arg1) + (args -> arg2);
   pthread_exit((void *) AB);
   return 0;
}
void *fun2(void * arguments){
   struct arg_struct *args = arguments;
   int CD = (args -> arg1) - (args -> arg2);
   pthread_exit((void *) CD);
   return 0;
}
void *fun3(void * arguments){
   struct arg_struct *args = arguments;
   int EF = (args -> arg1) + (args -> arg2);
   pthread_exit((void *) EF);
   return 0;
}
