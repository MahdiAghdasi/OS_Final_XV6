#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#define SLEEP_TIME 150

lock_t* lk;

void f1(void* arg1, void* arg2) {
  int num = *(int*)arg1;
  if (num)
  	lock_acquire(lk);
  printf(1, "1.should print %s\n", num ? "first" : "whenever");
  printf(1, "1. sleep for %d ticks\n", SLEEP_TIME);
  sleep(SLEEP_TIME);
  if (num)
  	lock_release(lk);
  exit();
}

void f2(void* arg1, void* arg2) {
  int num = *(int*)arg1;
  if (num)
  	lock_acquire(lk);
  printf(1, "2.should print %s\n", num ? "second" : "whenever");
  printf(1, "2. sleep for %d ticks\n", SLEEP_TIME);
  sleep(SLEEP_TIME);
  if (num)
  	lock_release(lk);
  exit();
}

void f3(void* arg1, void* arg2) {
  int num = *(int*)arg1;
  if (num) 
  	lock_acquire(lk);
  printf(1, "3.should print %s\n", num ? "third" : "whenever");
  printf(1, "3. sleep for %d ticks\n", SLEEP_TIME);
  sleep(SLEEP_TIME);
  if (num)
  	lock_release(lk);
  exit();
}

void f4(void* arg1, void* arg2) {
  int num = *(int*)arg1;
  if (num)
  	lock_acquire(lk);
  printf(1, "4.should print %s\n", num ? "forth" : "whenever");
  printf(1, "4. sleep for %d ticks\n", SLEEP_TIME);
  sleep(SLEEP_TIME);
  if (num)
  	lock_release(lk);
  exit();
}

int
main(int argc, char *argv[])
{
  lock_init(lk);
  int arg1 = 1, arg2 = 1;

  printf(1, "below should be sequential print:(having locks)\n");
  thread_create(&f1, (void *)&arg1, (void *)&arg2);
  thread_create(&f2, (void *)&arg1, (void *)&arg2);
  thread_create(&f3, (void *)&arg1, (void *)&arg2);
  thread_create(&f4, (void *)&arg1, (void *)&arg2);
  thread_join();
  thread_join();
  thread_join();
  thread_join();

  arg1 = 0;
  printf(1, "below should be a mess:(not having locks)\n");
  thread_create(&f1, (void *)&arg1, (void *)&arg2);
  thread_create(&f2, (void *)&arg1, (void *)&arg2);
  thread_create(&f3, (void *)&arg1, (void *)&arg2);
  thread_create(&f4, (void *)&arg1, (void *)&arg2);
  thread_join();
  thread_join();
  thread_join();
  thread_join();
  
  exit();
}
