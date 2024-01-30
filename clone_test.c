#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"

volatile int c = 0;

void addToCounter(void* arg1, void* arg2){
  c++;
  printf(1, "counter is: %x\n", c);
  exit();
}

int
main(int argc, char *argv[])
{
 int pid;
 void * stack[10];

 printf(1, "running testUserCalls:\n");
 c++;
 printf(1, "before cloning counter is: %x\n", c);

 int x;
 for(x=0; x<10; x++){
   stack[x] = malloc(4096);
   pid = clone(&addToCounter, 0,0, (void *) stack[x]);
   printf(1, "user pid: %d\n", pid);
 }

 for(x=0; x<10; x++){
   printf(1, "join pid %d\n", join((void **) &stack[x]));
 }


 c++;
 printf(1, "joined\n");

 printf(1, "x should be 12(C) and it is = %x\n", c);
 exit();
 return 0;
}
