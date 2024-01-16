#pragma once
#include <citro2d.h>

#include <string>
#include <vector>

#include "structs.h"

namespace utils {
const float g_Pi{3.1415926535f};
// Dunno why this is here

void setTarget(C3D_RenderTarget *target);
C3D_RenderTarget *getTarget();

void ClearBackground(float r, float g, float b);
void ClearBackground();
void SetColor(float r, float g, float b, float a = 1);
// Pass a Color4f object to the function
void SetColor(const Color4f &color);

// Draws a line by connecting the two points specified by (x1,y1) and (x2,y2)
void DrawLine(float x1, float y1, float x2, float y2, float lineWidth = 1.0f);
// Draws a line by connecting the two points specified by p1 and p1
void DrawLine(const Point2f &p1, const Point2f &p2, float lineWidth = 1.0f);

u32 Colof4fToC2DColor32(const Color4f &color);

void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3,
                  float lineWidth = 1);
void DrawTriangle(const Point2f &p1, const Point2f &p2, const Point2f &p3,
                  float lineWidth = 1);
void FillTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
void FillTriangle(const Point2f &p1, const Point2f &p2, const Point2f &p3);
void DrawRect(float left, float top, float width, float height,
              float lineWidth = 1.0f);
void DrawRect(const Point2f &topLeft, float width, float height,
              float lineWidth = 1.0f);
void DrawRect(const Rectf &rect, float lineWidth = 1.0f);
void FillRect(float left, float top, float width, float height);
void FillRect(const Point2f &topLeft, float width, float height);
void FillRect(const Rectf &rect);

void DrawEllipse(float centerX, float centerY, float radX, float radY,
                 float lineWidth = 1.0f);
void DrawEllipse(const Point2f &center, float radX, float radY,
                 float lineWidth = 1.0f);
void DrawEllipse(const Ellipsef &ellipse, float lineWidth = 1.0f);
void FillEllipse(float centerX, float centerY, float radX, float radY);
void FillEllipse(const Ellipsef &ellipse);
void FillEllipse(const Point2f &center, float radX, float radY);

// // Draws an arc. The angle parameters are in radians, not in degrees.
// void DrawArc(float centerX, float centerY, float radX, float radY, float
// fromAngle, float tillAngle, float lineWidth = 1.0f);
// // Draws an arc. The angle parameters are in radians, not in degrees.
// void DrawArc(const Point2f& center, float radX, float radY, float fromAngle,
// float tillAngle, float lineWidth = 1.0f);
// // Fills an arc. The angle parameters are in radians, not in degrees.
// void FillArc(float centerX, float centerY, float radX, float radY, float
// fromAngle, float tillAngle);
// // Fills an arc. The angle parameters are in radians, not in degrees.
// void FillArc(const Point2f& center, float radX, float radY, float fromAngle,
// float tillAngle);

// void DrawPolygon(const std::vector<Point2f>& vertices, bool closed = true,
// float lineWidth = 1.0f); void DrawPolygon(const Point2f* pVertices, size_t
// nrVertices, bool closed = true, float lineWidth = 1.0f); void
// FillPolygon(const std::vector<Point2f>& vertices); void FillPolygon(const
// Point2f* pVertices, size_t nrVertices);

// #pragma region TextureFunctionality

bool TextureFromFile(const std::string &path, Texture &texture);
// 	bool TextureFromString(const std::string& text, TTF_Font* pFont, const
// Color4f& textColor, Texture& texture); 	bool TextureFromString(const
// std::string& text, const std::string& fontPath, int ptSize, const Color4f&
// textColor, Texture& texture); 	void TextureFromSurface(const
// SDL_Surface* pSurface, Texture& textureData);
void DrawTexture(const Texture &texture, const Point2f &dstTopLeft,
                 const Rectf &srcRect = {});
// 	void DrawTexture(const Texture& texture, const Rectf& dstRect, const
// Rectf& srcRect = {}); 	void DeleteTexture(Texture& texture); #pragma
// endregion TextureFunctionality

bool IsPointInCircle(const Point2f &point, const Circlef &circle);
bool IsPointInRect(const Point2f &point, const Rectf &rect);
bool IsOverlapping(const Circlef &circle1, const Circlef &circle2);
bool IsOverlapping(const Rectf &rect1, const Rectf &rect2);

float GetDistance(const Point2f &point1, const Point2f &point2);

} // namespace utils