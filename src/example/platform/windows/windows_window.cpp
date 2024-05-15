#include "windows_window.hpp"

#include <Windows.h>

#include "fractal/base/common/assert.hpp"

namespace Fractal::Example {

static LRESULT CALLBACK FlWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
  Win32Window* window = (Win32Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

  LRESULT result = 0;
  switch(msg) {
  case WM_CLOSE: {
    window->Close();
    break;
  }

  default: {
    result = DefWindowProcW(hwnd, msg, wparam, lparam);
    break;
  }
  }
  return result;
}

Win32Window::Win32Window() {
  WNDCLASSEXW winClass = { };
  winClass.cbSize = sizeof(WNDCLASSEXW);
  winClass.style = CS_HREDRAW | CS_VREDRAW;
  winClass.lpfnWndProc = FlWndProc;
  winClass.hInstance = GetModuleHandle(NULL);
  winClass.lpszClassName = L"FractalWindowClass";
  
  auto register_result = RegisterClassExW(&winClass);
#ifdef FL_BUILD_DEBUG
  if(!register_result) {
    FL_LOG_ERROR("Win32 Error: RegisterClassEx failed with code {}", GetLastError());
    FL_ASSERT(false);
  }
#endif
  
  RECT initialRect = { 0, 0, 640, 480 };
  AdjustWindowRectEx(&initialRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);
  LONG initialWidth = initialRect.right - initialRect.left;
  LONG initialHeight = initialRect.bottom - initialRect.top;
  
  hwnd = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW,
    winClass.lpszClassName,
    L"Win32 Window",
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    CW_USEDEFAULT, CW_USEDEFAULT,
    initialWidth, 
    initialHeight,
    0, 0, GetModuleHandle(NULL), 0);
 
#ifdef FL_BUILD_DEBUG
  if(!hwnd) {
    FL_LOG_ERROR("Win32 Error: CreateWindowEx failed with code {}", GetLastError());
    FL_ASSERT(false);
  }
#endif

  SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
}

Win32Window::~Win32Window() {
}

bool Win32Window::IsOpen() const {
  return is_open;
}

void Win32Window::PollEvents() {
  MSG message = { };
  while(PeekMessageW(&message, 0, 0, 0, PM_REMOVE)) {
    TranslateMessage(&message);
    DispatchMessageW(&message);
  }
}

void Win32Window::Close() {
  is_open = false;
}

}
