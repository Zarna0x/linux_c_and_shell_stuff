#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int i = 0;
int j = 0;
void doSomeWork(char*);

int main () {
  pid_t proccessId = getpid();
  printf("I am : %d \n",proccessId);
  sleep(2);


  pid_t pid  = fork();
  srand((int)pid);

  printf("Fork returned: %d \n",(int)pid);

  if(pid < 0) {
     perror("Fork Failed !!");
  }

  if (pid == 0) {
     printf("I am child with pid: %d\n",(int)getpid());
     doSomeWork("CHILD");
     exit(42);
  } else if (pid > 0) {
     printf("I am parrent  and waiting child to end:\n");
     sleep(30);
     doSomeWork("PARENT");
     int status = 0;
     pid_t child_PID = wait(&status);

     printf("Parent Know child %d finished with status %d...|\n",(int) child_PID,status);
     int child_return_value = WEXITSTATUS(status);
     printf(" \n Return value was -> %d \n",child_return_value);
   }


  return 0;
}


void doSomeWork (char* thread_name) {
    const int NUM_TIMES = 2;
    if (strcmp(thread_name,"PARENT") == 0) {
        for (i = 0; i < NUM_TIMES; i++) {
         sleep(rand()% 4);
         printf("Done pass %d for %s \n",i,thread_name);
       }
    } else if (strcmp(thread_name,"CHILD") == 0) {
        for (j = 0; j < NUM_TIMES; j++) {
           sleep(rand()% 4);
        printf("Done pass %d for %s \n",j,thread_name);
      }
    }



}
