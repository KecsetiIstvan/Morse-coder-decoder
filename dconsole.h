#ifndef _CONSOLE
#define _CONSOLE
#include <time.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
using namespace std;
// Betûszínek (R-4, G-2, B-1)
const int BLACK=0;
const int BLUE=1;
const int GREEN=2;
const int CYAN=3;
const int RED=4;
const int MAGENTA=5;
const int BROWN=6;
const int LIGHTGRAY=7;
const int DARKGRAY=8;
const int LIGHTBLUE=9;
const int LIGHTGREEN=10;
const int LIGHTCYAN=11;
const int LIGHTRED=12;
const int LIGHTMAGENTA=13;
const int YELLOW=14;
const int WHITE=15;

// Betû háttérszínek (R-64, G-32, B-16)
const int BG_BLACK=0;
const int BG_BLUE=16;
const int BG_GREEN=32;
const int BG_CYAN=48;
const int BG_RED=64;
const int BG_MAGENTA=80;
const int BG_BROWN=96;
const int BG_LIGHTGRAY=112;
const int BG_DARKGRAY=128;
const int BG_LIGHTBLUE=144;
const int BG_LIGHTGREEN=160;
const int BG_LIGHTCYAN=176;
const int BG_LIGHTRED=192;
const int BG_LIGHTMAGENTA=208;
const int BG_YELLOW=224;
const int BG_WHITE=240;

// textcolor - Betûszín és háttérszín beállítása
void textcolor(int color) {
  HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(console, color);
}
//Hatterszin//
void bgcolor(int x)
{
string s="COLOR ";
char buffer [11];
itoa (x,buffer,16);
s=s+buffer;
s="\""+s+"\"";
  int i;
   for (i=0;i<11;i++)
   {buffer[i]=s[i];
   }
     system(buffer);

}

// gotoxy - Kurzorpozíció beállítása
void gotoxy(int x, int y) {
 HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
 COORD coord;
 coord.X = x; coord.Y = y; SetConsoleCursorPosition(console,coord);
}

// clrscr - Konzolos képernyõ törlése
void clrscr() {
 HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
 CONSOLE_SCREEN_BUFFER_INFO info;
 COORD start={0,0};
 DWORD dummy, size;
 GetConsoleScreenBufferInfo(console, &info);
 size = info.dwSize.X * info.dwSize.Y;
 FillConsoleOutputCharacter(console, ' ', size, start, &dummy);
 FillConsoleOutputAttribute(console, 7, size, start, &dummy);
 SetConsoleCursorPosition(console, start);
}

// delay - Várakozás a megadott ezredmásodpercig
void delay(int ms) {
 long int t;
 t=clock()+ms; while (clock()<t);
}

// sound - Hang bekapcsolása a megadott frekvencián a megadott ezredmásodpercig
void sound(DWORD freq, DWORD s) {
 Beep(freq,s);
}

// title - Konzolos ablak címsorszövegének beállítása
void title(char *title) {
  SetConsoleTitle(title);
}

const unsigned int DOS=852;
const unsigned int WIN=1250;

// setcodepage - Konzolos ablak kódlapjának beállítása
void setcodepage(unsigned int codepage) {
 SetConsoleOutputCP(codepage);
}

#endif
