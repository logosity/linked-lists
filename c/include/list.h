typedef struct Link Link;

struct Link {
  char* value;
  Link* next;
  Link* ref;
};

typedef struct List {
  Link* head;
} List;

Link* list_add_link(List* list, const char* value);
void list_set_ref(Link* from, Link* to);
void list_free(List* list);
int list_copy(List* from, List* to);

