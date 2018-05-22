#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/*********************************************************************************/
/*** internal function declarations ***/
/*********************************************************************************/
Link* create_link(Link**, const char*);
Link** find_end(List*);

/*********************************************************************************/
/*** public functions ***/
/*********************************************************************************/
Link* list_add_link(List* list, const char* value) {
  return create_link(find_end(list), value);
}

void list_set_ref(Link* from, Link* to) {
  from->ref = to;
}

void list_free(List* list) {
  Link* tmp;
  while (list->head != NULL) {
    tmp = list->head;
    list->head = list->head->next;
    free(tmp->value);
    tmp->next = NULL;
    free(tmp);
  }
}

/********************************************************************************
* Deep Copy in time O(n), space O(1). Used the following link for reference:
* https://www.tutorialcup.com/linked-list/clone-linked-list-next-random-pointer.htm
********************************************************************************/
int list_copy(List* from, List* to) {
  //create new copies of each link and interleave them in the 'from' list
  Link* current = from->head;
  while(current) {
    Link* new;
    create_link(&new, current->value);
    if(new == NULL) {
      fprintf(stderr, "Unable to copy list.\n");
      return -1;
    }

    new->next = current->next;
    current->next = new;
    current = new->next;
  }

  //copy refs
  current = from->head;
  while(current) {
    if(current->ref) {
      current->next->ref = current->ref->next;
    }
    current = current->next->next;
  }

  //finalize lists
  current = from->head;
  to->head = from->head->next;
  while(current) {
    Link* copy = current->next;
    current->next = current->next->next;
    if(copy->next) {
      copy->next = copy->next->next;
    }
    current = current->next;
  }

  return 0;
}

/*********************************************************************************/
/*** internal function definitions ***/
/*********************************************************************************/
Link* create_link(Link** dst, const char* value) {
  *dst = (Link*) malloc(sizeof(Link));
  Link* buffer = *dst;
  if(buffer == NULL) {
    fprintf(stderr, "Unable to allocate memory for link.\n");
    return NULL;
  }
  buffer->next = NULL;
  buffer->ref = NULL;

  buffer->value = malloc(strlen(value) + 1);
  if(buffer->value == NULL) {
    fprintf(stderr, "Unable to allocate memory for vallue.\n");
    free(buffer);
    buffer == NULL;
    return NULL;
  }

  strcpy(buffer->value, value);

  return buffer;
}

Link** find_end(List* list) {
  Link** result = &list->head;
  while(*result != NULL) {
    result = &((*result)->next);
  }
  return result;
}

