#include "vars.h"
#include "base.c"

int _init() {
  vidmem = 0xb8000;
  vidpointer = vidmem;
  printcolor = 0x0f;
  printnewl = 1;

  return 0;
}

int main() {
  _init();

  for (int i = 0; i < 30; i++) {
    print(inttostr(i, 10));
  }
  print("asdf");
  print("asdfasdf");
  print("asdfasdfasdf");
  print("Well, I guess this actually works. Now I can finally relax until something inevitably breaks again.");
  //print("asdf");
  //print(inttostr(-5, 10));

  return 0;
}