typedef struct Link Link;

struct Link {
  char* value;
  Link* next;
  Link* ref;
};

typedef struct List {
  Link* head;
} List;

int add_link(List* list, const char* value);

void set_ref(Link* from, Link* to);

int copy_list(List* from, List* to);

void free_list(List* list);
