//This file is probably safe to delete, but it might be used to change the text color of the console window in Windows.

#pragma once

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#include <iostream>



//default text colors can be found in wincon.h
inline void SetTextColor(WORD colors)
{
  HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

  SetConsoleTextAttribute(hConsole, colors);
}

inline void PressAnyKeyToContinue()
{
  //change text color to white
  SetTextColor(FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_GREEN);

  std::cout << "\n\nPress any key to continue" << std::endl;

  while (!_kbhit()){}

  return;
}
#else
#include <unistd.h>
#endif
#include <iostream>