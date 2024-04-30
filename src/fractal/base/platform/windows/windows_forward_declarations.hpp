#pragma once

// I am trying very hard to avoid nuking the global namespace by only ever including windows.h in .cc files
// If you need to include windows.h in a header file, include this instead

#ifndef _WINDEF_
  typedef struct HWND__* HWND;
#endif
