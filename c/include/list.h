typedef struct Link Link;

struct Link {
  char* value;
  Link* next;
  Link* ref;
};

typedef struct List {
  Link* head;
} List;

void add_link(List* list, char* value);
void free_list(List* list);
void set_ref(Link* from, Link* to);
void copy_list(List* from, List* to);
