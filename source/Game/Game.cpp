#include "Game.h"

// Basic game functions
#pragma region gameFunctions
void Start() {
  utils::TextureFromFile("romfs:gfx/wario.t3x", g_WarioTexture);
  ClearBackground();
}

void Console() {
  printf("\x1b[1;1HLies Engine");
  printf("\x1b[2;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime() * 6.0f);
  printf("\x1b[3;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime() * 6.0f);
  printf("\x1b[4;1HCmdBuf:  %6.2f%%\x1b[K", C3D_GetCmdBufUsage() * 100.0f);
}

void Draw() {
  ClearBackground();

  utils::DrawTexture(g_WarioTexture, g_WarioPos, Rectf{0, 0, 32, 32});

  if (hidKeysDown() & KEY_A)
    ClearBackground();
}

void Update(float elapsedSec) {}

void End() {
  // free game resources here
}

void OnKeyDownEvent(u8 key) {}

void OnKeyUpEvent(u8 key) {}

void OnKeyHeldEvent(u8 key) {
  switch (key) {
  case KEY_DLEFT:
    g_WarioPos.x -= 1;
    break;
  case KEY_DRIGHT:
    g_WarioPos.x += 1;
    break;
  case KEY_DUP:
    g_WarioPos.y -= 1;
    break;
  case KEY_DDOWN:
    g_WarioPos.y += 1;
    break;
  }
}

void OnCirclePadEvent(circlePosition pos) {}

void OnTouchDownEvent(touchPosition pos) {}

void OnTouchUpEvent(touchPosition pos) {}

#pragma endregion gameFunctions
