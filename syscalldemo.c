// Demo the usage of various system calls

#include "types.h"
#include "user.h"

#define RUN_DEMO(demo) \
  printf(1, #demo"\n====================\n");\
  demo();\
  printf(1, "\n\n");

void forkdemo() {
  int pid = fork();

  if (pid > 0) {
    printf(1, "parent: child=%d\n", pid);
    pid = wait();
    printf(1, "child %d is done\n", pid);
  }
  else if (pid == 0) {
    printf(1, "child: exiting\n");
    exit();
  }
  else {
    printf(1, "fork error\n");
  }
}

int
main(int argc, char *argv[]) {
  RUN_DEMO(forkdemo);

  exit();
}
