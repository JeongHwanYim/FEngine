#pragma once

#include <Windows.h>

extern HINSTANCE gMainInstance;

__forceinline void RegistMainInstance(HINSTANCE Instance) { gMainInstance = Instance; }
void CreateMainWindow();
LRESULT CALLBACK WindowMainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);