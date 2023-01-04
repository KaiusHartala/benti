int _outb(int addr, int byte) {
  *(char*)addr = byte;
  return addr + 1;
}
int strlen(char *str) {
  int i;
  for(i = 0; str[i] != '\0'; i++);
  return i;
}
int _inb(int addr) {
  unsigned char *p;
  p = (unsigned char*)addr;
  return p[0];
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

      int character = _inb(charaddr);
      int color = _inb(coloraddr);
      _outb(charaddr - 160, character);
      _outb(coloraddr - 160, color);
    }
  }
  vidpointer -= 160;
  for (int i = 0; i < 160; i += 2) {
    _outb(0xb8000 + 3840 + i, ' ');
    _outb(0xb8000 + 3840 + i + 1, printcolor);
  }
}

int fillscreen(char *str) {
  int pointer = vidmem;
  for (int i = 0; i < 2000; i++) {
    pointer = _outb(pointer, str);
    pointer = _outb(pointer, printcolor);
  }
  return 0;
}
int print(char *str) {
  int length = strlen(str);
  if (vidpointer > vidmem + 3840) {
    scroll();
  }
  int linelength = 0;
  for (int i = 0; i < 80; i++) {
    char character = str[i];
    if (character == 0) break;
    linelength++;
    vidpointer = _outb(vidpointer, character);
    vidpointer = _outb(vidpointer, printcolor);
  }
  if (printnewl) {
    vidpointer += 160 - (linelength * 2);
    while (vidpointer > vidmem + 3840) scroll();
  }

  return 0;
}