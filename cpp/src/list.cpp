#include <memory>
#include <string>
#include <vector>

#include "list.h"

using namespace std;

Link::Link(Value value) : value{value}, next{nullptr}, ref{nullptr} {}

List::List(Value value) : head{new Link(value)} {}

List::List(Values values) {
  for (Values::reverse_iterator rv = values.rbegin(); rv != values.rend(); ++rv) {
    shared_ptr<Link> link(new Link(*rv));
    link.get()->next = head;
    head = link;
  }
}
