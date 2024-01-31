#include <iostream>

using namespace std;
using ull = unsigned long long;

struct Xn {
  unsigned int a, b, c, d, e, f; // make sizeof(Xn) == n
};

void inspect(ull address) {
  cout << hex << "At 0x" << address << dec << ": ";
  printf("%02x\n", *((unsigned char *)(address)));
}
void inspect8(ull address) {
  cout << hex << "At 0x" << address << dec << ": ";
  for (int i = 0; i < 8; ++i) {
    printf("%02x ", *((unsigned char *)(address + i)));
  }
  cout << endl;
}

int main() {
  Xn *a = new Xn;
  *a = Xn{0x11111111};

  ull aAddress = (ull)a;

  inspect8(aAddress - 8);
  cout << "A" << endl;
  for (ull i = aAddress; i < aAddress + 32; i += 8) {
    inspect8(i);
  }
  cout << "B" << endl;
  for (ull i = aAddress + 32; i < aAddress + 32 + 32; i += 8) {
    inspect8(i);
  }

  cout << endl << "Allocate B" << endl;
  Xn *b = new Xn;
  *b = Xn{0xaaaaaaaa};
  
  ull bAddress = (ull)b;
  ull size = bAddress - aAddress;  
  
  inspect8(aAddress - 8);
  cout << "A" << endl;
  for (ull i = aAddress; i < aAddress + size; i += 8) {
    inspect8(i);
  }
  cout << "B" << endl;
  for (ull i = bAddress; i < bAddress + size; i += 8) {
    inspect8(i);
  }

  return 0;
}