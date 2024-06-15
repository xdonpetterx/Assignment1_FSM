#pragma once

#ifdef _WIN32
#include <windows.h>

// Color codes for the console output for Windows
#define RESET   7 // Default console color
#define RED     12 // Red console color
#define GREEN   10 // Green console color
#define YELLOW  14 // Yellow console color
#define BLUE    9 // Blue console color
#define MAGENTA 13 // Magenta console color
#define CYAN    11 // Cyan console color
#define WHITE   15 // White console color
#endif

#ifndef _WIN32
#define WORD std::string

// Color codes for the console output for Mac and Linux
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#endif
