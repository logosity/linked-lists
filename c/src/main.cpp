#include <cstdio>
#include <cstdlib>

extern "C" {
#include "list.h"
}

#include "bench_helpers.h"

void print_list(const List* list, int padding) {
  int i = 0;
  Link* head = list->head;
  while(head) {
    char null[6] = "NULL";
    char* ref_val = null;
    if(head->ref) ref_val = head->ref->value;
    printf("link (%0*d): %s, refs: (%s) \n", padding, i, head->value, ref_val);
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
  print_list(&list, 1);

  printf("copy list:\n");
  print_list(&copy, 1);

  List bench = {};
  add_links(&bench, 100);
  assign_refs(&bench);
  printf("bench list:\n");
  print_list(&bench,2);

  printf("RAND_MAX:%d\n",RAND_MAX);

  return 0;
}
