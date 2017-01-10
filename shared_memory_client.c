#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHSIZE 100

int main  () {

   int shmid;
   key_t key = 0x12345;
   char *shm;
   //char *buff = "Hello World";
   void *sh_addr;
//   int length = strlen(buff);
   char *s;

    if ( (shmid = shmget(key,SHSIZE,0666) ) < 0) {
       perror("Cant create shared memory segment");
       exit(1);
    }

   // printf("=> Shared Memory segment created succesfuly => %d",shmid);

    sh_addr = shmat(shmid,NULL,0);

    if ((int)sh_addr == -1) {
      perror("Cant attach Shared Memory segment to proccess address space");
      exit(1);
    }

     shm = (char*)sh_addr;

      for (s = shm; *s != 0; s++) {
         printf("%c",*s);
      }

    printf("\n");
    *shm = '*';

    struct shmid_ds buf;

int   ret = shmctl(shmid, IPC_STAT, &buf);
    if (ret < 0) {
        fprintf(stderr, "failed to shmctl\n");
        perror("shmctl");
        return -1;
    }

    printf("size %d\n", buf.shm_segsz);
    printf("attach time %d\n", buf.shm_atime);
    printf("detach time %d\n", buf.shm_dtime);
    printf("change time %d\n", buf.shm_ctime);
    printf("creator pid %d\n", buf.shm_cpid);
    printf("n attach %d\n", buf.shm_nattch);

  return 0;
}
