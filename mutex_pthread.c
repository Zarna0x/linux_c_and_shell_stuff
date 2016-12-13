#include <stdio.h>
#include <pthread.h>


#define NUM_LOOPS 5000000
long long sum = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void* counting_thread (void*);

int main () {


// Spawn thread
  int offset1 = 1;
  pthread_t id1;
  pthread_create(&id1,NULL,counting_thread,&offset1);



  int offset2 = -1;
  pthread_t id2;
  pthread_create(&id2,NULL,counting_thread,&offset2);

   pthread_join(id1,NULL);
 // WAIT THREAD TO FINISH
  pthread_join(id2,NULL);


  printf("Sum = %lld\n",sum);
  return 0;
}


void* counting_thread (void *arg) {
   int offset = *(int*)arg;
   int i;
   for (i = 0; i < NUM_LOOPS; i++) {
      // Start Critical SECTION
      pthread_mutex_lock(&mutex);
      sum += offset;
      pthread_mutex_unlock(&mutex);

      //END OF Critical SECTION
   }
  pthread_exit(NULL);
}
