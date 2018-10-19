#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argv, char** argc){

   long pageSize;
   long physPages;
   long maxProcess;

   struct rlimit rlim;


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
}
