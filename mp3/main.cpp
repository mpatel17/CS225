#include "list.h"

int main() {

  List<int> l, s;

 for(int i = 0; i < 10; i+=2) {
    l.insertBack(i);
  }

  for(int i = 0; i < 10; i+=2) {
    s.insertBack(i);
  }

  std::cout << l << std::endl;
  std::cout << s << std::endl;


  l.mergeWith(s);

  std::cout << l << std::endl;
  std::cout << s << std::endl;

  return 0;

}
