#include <wiringPi.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PCD8544.h"

// pin setup
int _din = 1;
int _sclk = 0;
int _dc = 2;
int _rst = 4;
int _cs = 3;

// lcd contrast
//may be need modify to fit your screen!  normal: 30- 90 ,default is:45 !!!maybe modify this value!
int contrast = 45;

#define BUFFER_FILE "/tmp/pcd8544_buffer"

void print_help()
{
    puts("PCD8544 Command Line Utility");
}

void show_logo(int argc, char **argv) {
    LCDshowLogo();
    LCDdisplay();
}

void clear(int argc, char **argv) {
    LCDclear();
    LCDdisplay();
}

void show_string(int argc, char **argv) {
    int x, y, str;
    sscanf(argv[0], "%d", &x);
    sscanf(argv[1], "%d", &y);
    LCDdrawstring(x, y, argv[2]);
    LCDdisplay();
}

void show_line(int argc, char **argv) {
    int x1, y1, x2, y2;
    sscanf(argv[0], "%d", &x1);
    sscanf(argv[1], "%d", &y1);
    sscanf(argv[2], "%d", &x2);
    sscanf(argv[3], "%d", &y2);
    LCDdrawline(x1, y1, x2, y2, BLACK);
    LCDdisplay();
}

#define TRY_COMMAND(cmdstring, argnum, func) \
    if (argc >= (argnum) + 1 && !strcmp((cmdstring), argv[1])) { (func)(argc - 2, argv + 2); return(0); }

int main (int argc, char **argv)
{
  // check wiringPi setup
  if (wiringPiSetup() == -1)
  {
	printf("FATAL: wiringPi init failed\n");
    exit(1);
  }

  // init and clear lcd
  LCDInit(_sclk, _din, _dc, _cs, _rst, contrast);
  LCDloadbuf(BUFFER_FILE);

  TRY_COMMAND("logo", 0, show_logo);
  TRY_COMMAND("clear", 0, clear);
  TRY_COMMAND("string", 3, show_string);
  TRY_COMMAND("line", 4, show_line);

  LCDsavebuf(BUFFER_FILE);
    //for (;;){
  //  printf("LED On\n");
  //  digitalWrite(pin, 1);
  //  delay(250);
  //  printf("LED Off\n");
  //  digitalWrite(pin, 0);
  //  delay(250);
  //}
  print_help();
  return -1;
}
