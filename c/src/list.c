#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int copy_list(List* from, List* to) {
  Link* current = from->head;
  while(current) {
    int result = add_link(to, current->value);
    if(result != 0) {
      return result;
    }
      
    current = current->next;
  }

  return 0;
}
//
//    def copy(self):
//        self._copy_links()
//        self._copy_refs()
//
//        current = self.head
//        copy = self.head.next
//        while current is not None:
//            current_copy = current.next
//            current.next = current.next.next
//
//            if current_copy.next:
//                current_copy.next = current_copy.next.next
//
//            current = current.next
//
//        return List(copy)
//
//    def _copy_links(self):
//        current = self.head
//        while current is not None:
//            new = Link(current.value)
//            new.next = current.next
//            current.next = new
//            current = new.next
//
//    def _copy_refs(self):
//        current = self.head
//        while current is not None:
//            if current.ref:
//                current.next.ref = current.ref.next
//
//            current = current.next.next

int add_link(List* list, const char* value) {
  Link* link = (Link*) malloc(sizeof(Link));
  if(link == NULL) {
    fprintf(stderr, "Unable to allocate memory for link.\n");
    return -1;
  }

  link->value = malloc(strlen(value) + 1);
  if(link->value == NULL) {
    fprintf(stderr, "Unable to allocate memory for vallue.\n");
    free(link);
    link == NULL;
    return -2;
  }

  strcpy(link->value, value);
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
  return 0;
}

void free_list(List* list) {
  Link* tmp;
  while (list->head != NULL) {
    tmp = list->head;
    list->head = list->head->next;
    free(tmp->value);
    tmp->next = NULL;
    free(tmp);
  }
}

void set_ref(Link* from, Link* to) {
  from->ref = to;
}
