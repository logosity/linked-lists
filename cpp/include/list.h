#include <memory>
#include <string>
#include <vector>

using Value = std::string;
using Values = std::vector<Value>;

struct Link {
  Value value;
  std::shared_ptr<Link> next;
  std::shared_ptr<Link> ref;

  Link(Value value);
};

struct List {
  std::shared_ptr<Link> head;
  List(Value value);
  List(Values values);
};

