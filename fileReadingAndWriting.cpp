
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream, std::stringbuf

int main () {
  std::stringstream ss;
  ss.str ("23476");
 int s = ss.get();
  std::cout << s << '\n';
  return 0;
