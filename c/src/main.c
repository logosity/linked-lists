#include <stdio.h>
#include "list.h"

int main() {
  List list = {};
  add_link(&list, "foo");
  printf("Hello, World!");
  return 0;
}
