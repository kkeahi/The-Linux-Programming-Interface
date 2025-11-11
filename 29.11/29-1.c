#include "/home/trenston/workspace/TLPI/tlpi-book/lib/tlpi_hdr.h"
#include <pthread.h>

static void *threadFunc(void *arg)
{
  char *s = (char *) arg;
  printf("%s", s);

  return (void *) strlen(s);
}

int main() 
{
  pthread_t t1;
  void *res;
  int s;

  s = pthread_create(&t1, NULL, threadFunc, "Message from threadFunc()\n");
  if (s != 0) errExitEN(s, "pthread_create");

  printf("Message from main()\n");

  // s = pthread_join(t1, &res);
  // s = pthread_join(pthread_self(), NULL);    # deadlock here
  pthread_t tid = t1;
  if (!pthread_equal(pthread_self(), tid))
  {
    s = pthread_join(tid, NULL);
    if (s != 0) errExitEN(s, "pthread_join"); 
    printf("Thread successfully joined\n");
  } else {
    printf("Cannot join a thread with itself\n");
  }
  // if (s != 0) errExitEN(s, "pthread_join");

  // printf("Thread successfully joined\n");

  exit(EXIT_SUCCESS);
}


// Console log:
//   Message from main()
//   Message from threadFunc()
//   ERROR [EDEADLK/EDEADLOCK Resource deadlock avoided] pthread_join