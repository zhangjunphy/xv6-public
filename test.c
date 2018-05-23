#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

#define MAX_TEST_COUNT 256

static int test_count = 0;
static char* test_list[MAX_TEST_COUNT];
static void (*test_functions[MAX_TEST_COUNT])();

void register_test(char* name, void (*function)()) {
  if (test_count >= MAX_TEST_COUNT) {
    printf(0, "Maximal test cases reached!\n");
    exit();
  }

  test_list[test_count] = name;
  test_functions[test_count] = function;
  ++test_count;
}

void test_printf() {
  printf(0, "succeeded!\n");
}

void test_link_file() {
  mkdir("dir");
  mknod("console", 1, 1);
  link("dir", "dir_link");
}

int main(int argc, char* argv[]) {
  register_test("printf", test_printf);
  register_test("link", test_link_file);

  if (argc <= 1) {
    printf(0, "Select a test:\n");
    int i;
    for (i = 0; i < test_count; ++i) {
      printf(0, "  %d: %s\n", i, test_list[i]);
    }
    printf(0, "\n");

    return 0;
  }

  int i;
  for (i = 1; i < argc; ++i) {
    printf(0, "Running test case %s\n", argv[i]);
    int found = 0;
    int j;
    for (j = 0; j < test_count; ++j) {
      if (strcmp(argv[i], test_list[j]) == 0) {
        test_functions[j]();
        found = 1;
        break;
      }
    }

    if (!found) {
      printf(0, "Not found!\n");
    }

    if (i != argc - 1)
      printf(0, "\n");
  }

  return 0;
}
