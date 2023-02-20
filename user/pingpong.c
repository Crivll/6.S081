#include "kernel/types.h"
#include "user/user.h"
#define MSGSIZE 5

int main()
{
  char *msg = "msg";
  char buf[MSGSIZE];
  int p[2];
  pipe(p);

  if (fork() > 0) {
    write(p[1], msg, MSGSIZE);
    wait(nullptr);
    while (read(p[0], buf, MSGSIZE) > 0) {
      printf("pong recieved\n");
    }
    
  }
  else {
    while (read(p[0], buf, MSGSIZE) > 0) {
      printf("ping received\n");
      write(p[1], msg, MSGSIZE);
    }
  }
  exit(0);
}
