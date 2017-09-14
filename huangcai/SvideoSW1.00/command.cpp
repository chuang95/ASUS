#include "stdafx.h"
#include <string>
#include <conio.h>
#include <stdio.h>
#include "extern.h"
 
static int __BACKGROUND = 0;
static int __FOREGROUND = 7;

//cursor goto xy 
void gotoxy(int x, int y)
{
  COORD c;
 
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//clear screen 
void clrscr ()
{
  DWORD written;
  COORD coord;
 
  coord.X =0;
  coord.Y =0;
  FillConsoleOutputAttribute (GetStdHandle (STD_OUTPUT_HANDLE),__FOREGROUND + (__BACKGROUND << 4), 8000, coord,&written);
  FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',8000, coord, &written);
  gotoxy (1, 1);
}
 
void clreol ()
{
  COORD coord;
  DWORD written;
  CONSOLE_SCREEN_BUFFER_INFO info;
 
  GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE),&info);
  coord.X = info.dwCursorPosition.X;
  coord.Y = info.dwCursorPosition.Y;
 
  FillConsoleOutputCharacter (GetStdHandle (STD_OUTPUT_HANDLE),' ', info.dwSize.X - info.dwCursorPosition.X, coord, &written);
  gotoxy (coord.X, coord.Y);
}
 
void delline()
{
  COORD coord;
  DWORD written;
  CONSOLE_SCREEN_BUFFER_INFO info;
 
  GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE),&info);
  coord.X = info.dwCursorPosition.X;
  coord.Y = info.dwCursorPosition.Y;
 
  FillConsoleOutputCharacter (GetStdHandle (STD_OUTPUT_HANDLE),' ', info.dwSize.X * info.dwCursorPosition.Y, coord, &written);
  gotoxy (info.dwCursorPosition.X + 1,info.dwCursorPosition.Y + 1);
}
 
int _conio_gettext (int left, int top, int right, int bottom,char *str)
{
  int i, j, n;
  SMALL_RECT r;
  CHAR_INFO buffer[25][80];
  COORD c1,c2;
  c1.X = 80;
  c1.Y = 25;
  c2.X = 0;
  c2.Y = 0;
  r.Left = left - 1;
  r.Bottom = bottom - 1;
  r.Right = right - 1;
  r.Top = top - 1;
  ReadConsoleOutput (GetStdHandle (STD_OUTPUT_HANDLE),(PCHAR_INFO) buffer, c1,c2, &r);
 
  lstrcpy (str, "");
  for (i = n = 0; i <= bottom - top; i++)
  for (j = 0; j <= right - left; j++)
  {
    str[n] = buffer[i][j].Char.AsciiChar;
    n++;
  }
  str[n] = 0;
  return 1;
}
 
void puttext (int left, int top, int right, int bottom, char *str)
{ 
	int i = 0, j = 0, n = 0;
	SMALL_RECT r;
	CHAR_INFO buffer[25][80];
	COORD c1,c2;
	c1.X = 80;
	c1.Y = 25;
	c2.X = 0;
	c2.Y = 0;
	memset (buffer, 0, sizeof (buffer));
	r.Left=left - 1;
	r.Bottom=bottom - 1;
	r.Right=right - 1;
	r.Top=top - 1;
	
	for (i = n = 0; i <= bottom - top; i++)
		for (j = 0; j <= right - left && str[n] != 0; j++)
		{
			buffer[i][j].Char.AsciiChar = str[n];
			buffer[i][j].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
			n++;
		}

	WriteConsoleOutput (GetStdHandle (STD_OUTPUT_HANDLE),(CHAR_INFO *) buffer, c1,c2, &r);
}

void _setcursortype (int type)
{
	CONSOLE_CURSOR_INFO Info;

	Info.dwSize = type;
	SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE),	&Info);
}

void Cursor(BOOL type)
{
	CONSOLE_CURSOR_INFO Info;

	Info.bVisible = type;
	SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE),	&Info);
}
 
void textattr (int _attr)
{
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), _attr);
}
 
void textbackground (int color)
{
	__BACKGROUND = color;
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),
	__FOREGROUND + (color << 4));
}
 
void textcolor (int color)
{
	__FOREGROUND = color;
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
	color + (__BACKGROUND << 4));
}
 
int wherex ()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	 
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return info.dwCursorPosition.X + 1;
}
 
int wherey ()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	 
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return info.dwCursorPosition.Y + 1;
}

void PrintStr(int x, int y, char *s, int location, BYTE color)
{
	int print_x = x;
	int i = 0, j = 0, n = 0;
	SMALL_RECT r;
	CHAR_INFO buffer[25][80];
	COORD c1, c2;

	switch(location)
	{		
		case LOC_LEFT:
			print_x=1;
			break;
		case LOC_MIDDLE:
			print_x=(int)((82-strlen(s))/2);
			break;
		case LOC_RIGHT:
			print_x= 82- (int) strlen(s);
			break;
		case LOC_X:
		default:
			break;
	}
	gotoxy(print_x + (int)strlen(s) ,y);

	c1.X = 80;
	c1.Y = 25;
	c2.X = 0;
	c2.Y = 0;

	memset (buffer, 0, sizeof (buffer));

	r.Left = print_x - 1;
	r.Bottom = y - 1;
	r.Right = r.Left + (int) strlen(s) - 1;
	r.Top = y - 1;
	
	for (j = 0; s[n] != 0; j++) 
	{
		buffer[i][j].Char.AsciiChar = s[n];
		buffer[i][j].Attributes = color;
		n++;
	}

	WriteConsoleOutput (GetStdHandle (STD_OUTPUT_HANDLE),(CHAR_INFO *) buffer, c1,c2, &r);
}

void PrintCh(int x, int y, char c, BYTE color, int count)
{
	int i = 0, j = 0, n = 0;
	SMALL_RECT r;
	CHAR_INFO buffer[25][80];
	COORD c1,c2;

	c1.X = 80;
	c1.Y = 25;
	c2.X = 0;
	c2.Y = 0;

	memset (buffer, 0, sizeof (buffer));

	r.Left = x - 1;
	r.Bottom = y - 1;
	r.Right = r.Left + count - 1;
	r.Top = y - 1;
	gotoxy((x + count)%80, y + (x + count)/80);
	
	for (j = 0; j<count; j++) 
	{
		buffer[i][j].Char.AsciiChar = c;
		buffer[i][j].Attributes = color;
		n++;
	}

	WriteConsoleOutput (GetStdHandle (STD_OUTPUT_HANDLE),(CHAR_INFO *) buffer, c1,c2, &r);
}

ULONG atoh(CString s)
{
	ULONG ulRet = 0;
	sscanf(s ,"%lX", ulRet);
	return ulRet;
}

BOOL blParameter(char *s)
{
	if(s == NULL) return false;
	if(s[0] == '-' || s[0] == '/' || strlen(s) == 0 || s[0] == ' ' || s[0] == 0x00) return false;
	return true;
}