#pragma once
#include "Core.h"

#pragma region coreImplementations
C3D_RenderTarget *top{};

void Initialize() {
  romfsInit();
  gfxInitDefault();
  C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
  C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
  C2D_Prepare();
  consoleInit(GFX_BOTTOM, NULL);

  top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

  utils::setTarget(top);
}

extern void Start();
extern void Console();
extern void Update(float elapsedSec);
extern void Draw();
extern void End();

extern void OnKeyDownEvent(u8 key);
extern void OnKeyUpEvent(u8 key);
extern void OnKeyHeldEvent(u8 key);

extern void OnCirclePadEvent(circlePosition pos);

extern void OnTouchDownEvent(touchPosition pos);
extern void OnTouchUpEvent(touchPosition pos);

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

void Run() {
  Start();
  while (aptMainLoop()) {
    hidScanInput();

    // Respond to user input
    u32 kDown = hidKeysDown();
    u32 kHeld = hidKeysHeld();
    u32 kUp = hidKeysUp();

    touchPosition touch{};
    hidTouchRead(&touch);

    circlePosition circlePos{};
    hidCircleRead(&circlePos);
    OnCirclePadEvent(circlePos);

    OnKeyDownEvent(kDown);
    OnKeyUpEvent(kUp);
    OnKeyHeldEvent(kHeld);

    OnTouchDownEvent(touch);
    OnTouchUpEvent(touch);

    if (kDown & KEY_START)
      break; // break in order to return to hbmenu

    Console();

    Update(0);

    // Render the scene
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    C2D_SceneBegin(top);

    Draw();

    C3D_FrameEnd(0);
  }

  End();
}

void Cleanup() {
  C2D_Fini();
  C3D_Fini();
  gfxExit();
  romfsExit();
}

#pragma endregion coreImplementations