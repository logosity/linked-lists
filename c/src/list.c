#include <stdlib.h>
#include "list.h"

void add_link(List* list, char* value) {
  Link* link = (Link*) malloc(sizeof(Link));
  link->value = value;
  link->next = NULL;
  link->ref = NULL;

  if(!list->head) {
    list->head = link;
  } else {
    Link* end = list->head;
    while(end->next != NULL) {
      end = end->next;
    }
    end->next = link;
  }
}

void free_list(List* list) {
  Link* tmp;
  while (list->head != NULL) {
    tmp = list->head;
    list->head = list->head->next;
    tmp->next = NULL;
    free(tmp);
  }
}
