#ifndef CONSLMANIP_H
#define CONSLMANIP_H

#include <iostream>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
inline void enableANSIColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING
    SetConsoleMode(hOut, dwMode);
}
#else
inline void enableANSIColors() {}
#endif

inline void setColor(int colorCode) {
    switch (colorCode) {
        case 0:  std::cout << "\033[30m"; break;
        case 1:  std::cout << "\033[34m"; break;
        case 2:  std::cout << "\033[32m"; break;
        case 3:  std::cout << "\033[36m"; break;
        case 4:  std::cout << "\033[31m"; break;
        case 5:  std::cout << "\033[35m"; break;
        case 6:  std::cout << "\033[33m"; break;
        case 7:  std::cout << "\033[90m"; break;
        case 8:  std::cout << "\033[37m"; break;
        case 9:  std::cout << "\033[94m"; break;
        case 10: std::cout << "\033[92m"; break;
        case 11: std::cout << "\033[96m"; break;
        case 12: std::cout << "\033[91m"; break;
        case 13: std::cout << "\033[95m"; break;
        case 14: std::cout << "\033[93m"; break;
        case 15: std::cout << "\033[97m"; break;
        default: std::cout << "\033[0m";  break;
    }
}

inline void typewriter(const std::string& text, int delay = 50) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    std::cout << std::endl;
}

inline void clrscr() {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

inline void pause(int delay) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

#endif
