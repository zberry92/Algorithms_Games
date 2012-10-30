#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
  char x = '2';
  int y;

  x = x;
  y = atoi(&x);

  cout <<y <<endl;
  return 0;
}
  
