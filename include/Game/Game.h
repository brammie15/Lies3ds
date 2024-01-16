#pragma once
#include "Engine/utils.h"
using namespace utils;

utils::Texture g_WarioTexture{};
Point2f g_WarioPos{};

#pragma region gameFunctions
void Start();
void Draw();
void Update(float elapsedSec);
void End();

void OnKeyDownEvent(u8 key);
void OnKeyUpEvent(u8 key);
void OnKeyHeldEvent(u8 key);

void OnCirclePadEvent(circlePosition pos);

void OnTouchDownEvent(touchPosition pos);
void OnTouchUpEvent(touchPosition pos);
#pragma endregion gameFunctions