#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/sem.h>



int main(int argv, char** argc){

   long pageSize;
   long physPages;
   long maxProcess;
   int shmId;
   struct rlimit rlim;

   sem_t sem;

   int* semval = malloc(sizeof(int));
   semval[0] = 0;
   int semid = semget(IPC_PRIVATE,1,00600);                                    \

   struct sembuf waitsem[1];


    waitsem[0].sem_num = 0;
    waitsem[0].sem_op = 1;
    waitsem[0].sem_flg = IPC_NOWAIT;

   pageSize = sysconf(_SC_PAGESIZE);
   printf("POSIX.1 Page Size: %ld\n",pageSize);

   physPages = sysconf(_SC_PHYS_PAGES);
   printf("POSIX.2 Physical Pages: %ld\n",physPages);

   maxProcess = sysconf(_SC_CHILD_MAX);
   printf("POSIX.1 Max # of Processes per user: %ld\n",maxProcess);

   getrlimit(RLIMIT_FSIZE, &rlim);
   printf("(getrlimit) Max file size: %ld\n", rlim.rlim_cur);

   getrlimit(RLIMIT_NOFILE, &rlim);
   printf("(getrlimit Max number of files HARD: %ld\n", rlim.rlim_max);

   printf("(getrlimit) Max number of files SOFT: %ld\n", rlim.rlim_cur);

   int FOO = 2147483640;
   int size = 0;
   while ((shmId = shmget (IPC_PRIVATE, FOO+size, IPC_CREAT|S_IRUSR|S_IWUSR)) >\
 0){
     size += 1;
     // printf("Max size = %d\n",size + 4088);                                  


     if (shmctl (shmId, IPC_RMID, 0) < 0) {
      perror ("can't deallocate\n");
      exit(1);
   }
   }
   printf("Max size = %d (Empirical on EOS14)\n",size + FOO - 1);
   int count = 0;
   while (semop(semid,&waitsem[0],1) > -1){
     count++;
   }
   printf("Max count of semaphore %d (Empirical on EOS14)\n", count);
   semctl (semid, 0, IPC_RMID);

}
