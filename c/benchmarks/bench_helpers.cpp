#include <vector>
#include <cstdlib>
#include <cstdio>
extern "C" {
#include "list.h"
}

#include "bench_helpers.h"

void assign_refs(List* list) {
  std::vector<Link*> links;
  Link* current = list->head;
  while(current) {
    links.push_back(current);
    current = current->next;
  }
  int range = links.size();
  for(auto it = links.begin(); it != links.end(); it++) {
    int ref_idx = rand() % range;
    (*it)->ref = links[ref_idx];
  }
}

void add_links(List* list, int count) {
  for(auto i = 0; i < count; ++i) {
    char tag[15];
    sprintf(tag, "Bench%010d", i);
    list_add_link(list, tag);
  }
}

