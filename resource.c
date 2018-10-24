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

/**************************************************************
 * Lab 7 - Source code used to find resource limit.
 * @author Jon DeWent
 * @author Cheng Li
 * @version 10-24-2018
 *************************************************************/

int main(int argv, char** argc){
    
    /* Define variables to store resource. */
    long pageSize;
    long physPages;
    long maxProcess;
    long clockResolution;
    int shmId;
    struct rlimit rlim;

    int* semval = malloc(sizeof(int));
    semval[0] = 0;
    int semid = semget(IPC_PRIVATE,1,00600);
    
    struct sembuf waitsem[1];
    
    waitsem[0].sem_num = 0;
    waitsem[0].sem_op = 1;
    waitsem[0].sem_flg = IPC_NOWAIT;
    
    /* Find page size in bytes. */
    pageSize = sysconf(_SC_PAGESIZE);
    printf("POSIX.1 Page Size: %ld\n",pageSize);
    
    /* Find physical pages in system. */
    physPages = sysconf(_SC_PHYS_PAGES);
    printf("POSIX.2 Physical Pages: %ld\n",physPages);
    
    /* Find max # of processes per user. */
    maxProcess = sysconf(_SC_CHILD_MAX);
    printf("POSIX.1 Max # of Processes per user: %ld\n",maxProcess);
    
    /* Find clock resolution (msec) */
    clockResolution = sysconf(_SC_CLK_TCK);
    long mSec = (1.0/clockResolution) * 1000.0;
    printf("Clock resolution (mSec): %ld\n", mSec);
    
    /* Find max filesize in bytes. */
    getrlimit(RLIMIT_FSIZE, &rlim);
    printf("(getrlimit) Max file size: %ld\n", rlim.rlim_cur);
    
    /* Find max # of open files (hard limit) */
    getrlimit(RLIMIT_NOFILE, &rlim);
    printf("(getrlimit Max number of files HARD: %ld\n", rlim.rlim_max);
    
    /* Find max # of open files (soft limit) */
    printf("(getrlimit) Max number of files SOFT: %ld\n", rlim.rlim_cur);
    
    /* Attempt to find the max size of a shared memory segment. */
    int FOO = 2147483640;
    int size = 0;
    while ((shmId = shmget (IPC_PRIVATE, FOO+size, IPC_CREAT|S_IRUSR|S_IWUSR)) > 0){
        size += 1;
        if (shmctl (shmId, IPC_RMID, 0) < 0) {
            perror ("can't deallocate\n");
            exit(1);
        }
    }
    printf("Max size = %d (Empirical on EOS14)\n",size + FOO - 1);
    
    /* Find the maximum value of a (counting) semaphore. */
    int count = 0;
    while (semop(semid,&waitsem[0],1) > -1){
        count++;
    }
    printf("Max count of semaphore %d (Empirical on EOS14)\n", count);
    semctl (semid, 0, IPC_RMID);
}
