#include <windows.h>
int mousePosX() {
  int pos;

  POINT cursor_pos;
  if (GetCursorPos(&cursor_pos))
    pos = cursor_pos.x;
  else 
    pos = -1;

  return pos;
}
int mousePosY() {
  int pos;

  POINT cursor_pos;
  if (GetCursorPos(&cursor_pos))
    pos = cursor_pos.y;
  else 
    pos = -1;

  return pos;
}
int getMouseBtn() {
   return (GetKeyState(VK_LBUTTON) & 0x80) != 0 || (GetKeyState(VK_RBUTTON) & 0x80) != 0;
}