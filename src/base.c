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
}

int print(char *str) {
  int length = strlen(str);
  int lines = length / 160;
  //for (int i = 0; i < )
  if (vidpointer > vidmem + 3840) {
    scroll();
    vidpointer -= 160;
  }
  for (int j = 0; j < length; j++) {
    vidpointer = _outb(vidpointer, str[j]);
    vidpointer = _outb(vidpointer, printcolor);
  }
  if (printnewl) {
    while (length > 80) length -= 80;
    vidpointer += 160 - (length * 2);
  }

  return 0;
}