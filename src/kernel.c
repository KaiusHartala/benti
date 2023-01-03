#include "vars.h"
#include "base.c"

//video memory is 80 * 25

int crash() {
  printcolor = 0x1f;
  clearscreen();
  vidpointer = vidmem;
  print("Whelp! The OS crashed again. Hope this helps:");
  print("");
  print("...");
  print("Okay so it turns out I was too lazy to print the register values so... enjoy");
  print("debugging!");
  return 0;
}

int init() {
  vidmem = 0xb8000;
  vidpointer = vidmem;
  printcolor = 0x0f; //dark mode, nice!
  printnewl = 1;
  return 0;
}

int main(void) {
  if (init() == -1) {
    crash();
    return -1;
  }
  char str[] = "str";
  print(inttostr(-15, 10));
  print("ASDF");
  print(str);

  return 0;
}