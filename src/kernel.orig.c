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
  printnewl = 1;#include "vars.h"

int strlen(char str[]) {
  int i;
  for(i = 0; str[i] != '\0'; i++);
  return i;
}

int readbyte(int val) {
  unsigned char *p;
  p = (unsigned char*)val;
  return p[0];
}

int writebyte(int addr, int val) {
  *(char*)addr = val;
  return addr + 1;
}

int fillline(int line, int val) {
  for (int i = 0; i < 160; i += 2) {
    int current = vidmem + (line * 160) + i;
    writebyte(current, val);
    writebyte(current + 1, printcolor);
  }
  return 0;
}
int clearline(int line) {
  fillline(line, ' ');
}
int clearscreen() {
  for (int i = 0; i < 25; i++) {
    clearline(i);
  }
}

char *inttostr(int val, int base) {
  static char buf[] = {0};
  int i = 30;
  int isneg = 0;
  if (val < 0) {
    isneg = 1;
    val += -val * 2;
  }
  if (val == 0) {
    return "0";
  }
  for (; val && i; --i, val /= base) {
    buf[i] = "0123456789abcdef"[val % base];
  }
  if (isneg == 1) {
    buf[i--] = *"-";
  }
  return &buf[i + 1];
}

int scroll() {
  for (int i = 1; i < 25; i++) {
    for (int j = 0; j < 160; j += 2) {
      int charaddr = vidmem + (i * 160) + j;
      int coloraddr = charaddr + 1;
      int val = readbyte(charaddr);
      int color = readbyte(coloraddr);
      writebyte(charaddr - 160, val);
      writebyte(coloraddr - 160, color);
    }
  }
}

int print(char str[]) {
  if (vidpointer > vidmem + 3840) {
    scroll();
    vidpointer -= 160;
  }
  for (int i = 0; i < strlen(str); i++) {
    vidpointer = writebyte(vidpointer, str[i]);
    vidpointer = writebyte(vidpointer, printcolor);
  }
  if (printnewl == 1) {
    int length = strlen(str);
    while (length > 80) length -= 80;
    vidpointer += 160 - (length * 2);
  }
  return 0;
}
  return 0;
}

int main(void) {
  if (init() == -1) {
    crash();
    return -1;
  }
  char str[] = "This will print, but...";
  print(inttostr(-15, 10));
  print("This won't print :(");
  fillline(5, 'A');
  print(str);

  return 0;
}