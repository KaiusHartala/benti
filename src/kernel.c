#include "vars.h"
#include "base.c"

int _init() {
  vidmem = 0xb8000;
  vidpointer = vidmem;
  printcolor = 0x1f;
  printnewl = 1;
  fillscreen(' ');

  print("This is a test.");

  return 0;
}

int welcome() {
  return 0;
}

int main() {
  _init();
  welcome();


  return 0;
}