#ifndef CONSLMANIP_H
#define CONSLMANIP_H

#include <iostream>
#include <thread>
#include <chrono>

#ifdef _WIN32
  #include <windows.h>
#endif

#ifdef _WIN32
inline bool ansiEnabled() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return false;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return false;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    return SetConsoleMode(hOut, dwMode) != 0;
}

inline bool& ansiSupported() {
    static bool val = ansiEnabled();
    return val;
}

inline void enableANSIColors() {
    ansiSupported();
}
#else
inline void enableANSIColors() {}
#endif

inline void setColor(int colorCode) {
#ifdef _WIN32
    if (!ansiSupported()) {

        static const WORD winColors[16] = {
            0,                                           //  0  Black
            FOREGROUND_BLUE,                             //  1  Dark Blue
            FOREGROUND_GREEN,                            //  2  Dark Green
            FOREGROUND_GREEN | FOREGROUND_BLUE,          //  3  Dark Cyan
            FOREGROUND_RED,                              //  4  Dark Red
            FOREGROUND_RED   | FOREGROUND_BLUE,          //  5  Dark Magenta
            FOREGROUND_RED   | FOREGROUND_GREEN,         //  6  Dark Yellow
            FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE, // 7 Grey
            FOREGROUND_INTENSITY,                        //  8  Dark Grey
            FOREGROUND_BLUE  | FOREGROUND_INTENSITY,     //  9  Blue
            FOREGROUND_GREEN | FOREGROUND_INTENSITY,     // 10  Green
            FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY, // 11 Cyan
            FOREGROUND_RED   | FOREGROUND_INTENSITY,     // 12  Red
            FOREGROUND_RED   | FOREGROUND_BLUE  | FOREGROUND_INTENSITY, // 13 Magenta
            FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY, // 14 Yellow
            FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY // 15 White
        };
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE) {
            WORD attr = (colorCode >= 0 && colorCode < 16)
                            ? winColors[colorCode]
                            : (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            SetConsoleTextAttribute(hOut, attr);
        }
        return;
    }
#endif
    switch (colorCode) {
        case 0:  std::cout << "\033[30m";  break; // Black
        case 1:  std::cout << "\033[34m";  break; // Dark Blue
        case 2:  std::cout << "\033[32m";  break; // Dark Green
        case 3:  std::cout << "\033[36m";  break; // Dark Cyan
        case 4:  std::cout << "\033[31m";  break; // Dark Red
        case 5:  std::cout << "\033[35m";  break; // Dark Magenta
        case 6:  std::cout << "\033[33m";  break; // Dark Yellow
        case 7:  std::cout << "\033[90m";  break; // Grey (default text)
        case 8:  std::cout << "\033[37m";  break; // Dark Grey
        case 9:  std::cout << "\033[94m";  break; // Bright Blue
        case 10: std::cout << "\033[92m";  break; // Bright Green
        case 11: std::cout << "\033[96m";  break; // Bright Cyan
        case 12: std::cout << "\033[91m";  break; // Bright Red
        case 13: std::cout << "\033[95m";  break; // Bright Magenta
        case 14: std::cout << "\033[93m";  break; // Bright Yellow
        case 15: std::cout << "\033[97m";  break; // Bright White
        default: std::cout << "\033[0m";   break; // Reset
    }
}

inline void typewriter(const std::string& text, int delay = 50) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    std::cout << '\n';
}

inline void clrscr() {
#ifdef _WIN32
    if (!ansiSupported()) {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE) return;

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (!GetConsoleScreenBufferInfo(hOut, &csbi)) return;

        DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
        DWORD count;
        COORD homeCoord = { 0, 0 };

        FillConsoleOutputCharacter(hOut, ' ', cellCount, homeCoord, &count);
        FillConsoleOutputAttribute(hOut, csbi.wAttributes, cellCount, homeCoord, &count);
        SetConsoleCursorPosition(hOut, homeCoord);
        return;
    }
#endif
    std::cout << "\033[2J\033[3J\033[H" << std::flush;
}

inline void pause(int delay) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

#endif