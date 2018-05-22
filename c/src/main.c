#include <stdio.h>
#include "list.h"

void print_list(const List* list) {
  int i = 0;
  Link* head = list->head;
  while(head) {
    printf("link (%d): %s\n", i, head->value);
    head = head->next;
    ++i;
  }
}

int main() {
  List list = {};
  list_add_link(&list, "Test1");
  list_add_link(&list, "Test2");
  list_add_link(&list, "Test3");
  list_add_link(&list, "Test4");

  list_set_ref(list.head, list.head->next->next->next);
  list_set_ref(list.head->next, list.head->next);
  list_set_ref(list.head->next->next, list.head->next);
  list_set_ref(list.head->next->next->next, list.head);

  List copy = {};
  list_copy(&list, &copy);

  printf("original list:\n");
  print_list(&list);

  printf("copy list:\n");
  print_list(&copy);

  return 0;
}
