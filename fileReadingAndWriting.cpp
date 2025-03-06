//
//#include <iostream>
//#include <fstream>
//using namespace std;
//
//int main()
//{
//    fstream file("my.txt",ios_base::in);
//    string x;
//    file>>x;
//    cout<<x;
//}
// stringstream::str
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream, std::stringbuf

int main () {
  std::stringstream ss;
  ss.str ("23476");
 int s = ss.get();
  std::cout << s << '\n';
  return 0;
