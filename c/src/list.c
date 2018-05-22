#include <stdlib.h>
#include "list.h"

void copy_list(List* from, List* to) {
  Link* current = from->head;
  while(current) {
    add_link(to, current->value);
    current = current->next;
  }
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

void set_ref(Link* from, Link* to) {
  from->ref = to;
}
