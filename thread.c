#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct sum_runner_t {
  long long limit;
  long long answer;
};

//generate sum
void* sum_runner(void* arg) {
//  struct sum_runner_t *arg_struct = (struct sum_runner_t*) arg;
  long long *limit_ptr = (long long*) arg;
  long long sum =  0;
  long long i;

  for (i = 0; i <= *limit_ptr; i++) {
     sum += i;
  }
  // printf("\n\n\n\n\n\n\n---sum is %lld and number is %lld--\n\n\n\n\n\n\n",sum,arg_struct->limit);

   long long *answer = (long long*)malloc(sizeof(*answer));
   *answer = sum; // answer returns pointer to sum
   pthread_exit(answer);

//  pthread_exit(0);
}

int main (int argc, char **argv) {

  int num_args = argc - 1;
  long long *limit = malloc(sizeof(*limit));
  *limit = atoll(argv[1]);
  // thread ID
  pthread_t tid;
  pthread_create(&tid,NULL,sum_runner,limit);



     long long* result;
     pthread_join(tid,(void**)&result);
     printf("Sum  = %lld\n",*result);
     free(result);



 return 0;
}
