// #define _USE_MATH_DEFINES
// #include <cmath>
#include "utils.h"

#include <3ds.h>
#include <citro2d.h>

Color4f g_currentColor{};
C3D_RenderTarget *g_pTarget{};

namespace utils {

void setTarget(C3D_RenderTarget *target) { g_pTarget = target; }

C3D_RenderTarget *getTarget() { return g_pTarget; }

#pragma region OpenGLDrawFunctionality
void ClearBackground(float r, float g, float b) {
  C2D_TargetClear(g_pTarget, C2D_Color32(r, g, b, 0xFF));
}
void ClearBackground() { ClearBackground(185.0f, 211.0f, 238.0f); }
void SetColor(float r, float g, float b, float a) {
  g_currentColor = {r, g, b, a};
}

void SetColor(const Color4f &color) { g_currentColor = color; }

void DrawLine(float x1, float y1, float x2, float y2, float lineWidth) {
  C2D_DrawLine(x1, y1, Colof4fToC2DColor32(g_currentColor), x2, y2,
               Colof4fToC2DColor32(g_currentColor), lineWidth, 0);
}

u32 Colof4fToC2DColor32(const Color4f &color) {
  return C2D_Color32(color.r * 255, color.g * 255, color.b * 255,
                     color.a * 255);
}

void DrawLine(const Point2f &p1, const Point2f &p2, float lineWidth) {
  DrawLine(p1.x, p1.y, p2.x, p2.y, lineWidth);
}

void DrawRect(float left, float top, float width, float height,
              float lineWidth) {
  u32 Color = Colof4fToC2DColor32(g_currentColor);
  DrawLine(left, top, left + width, top, lineWidth);
  DrawLine(left + width, top, left + width, top + height, lineWidth);
  DrawLine(left + width, top + height, left, top + height, lineWidth);
  DrawLine(left, top + height, left, top, lineWidth);
}

void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3,
                  float lineWidth) {
  u32 Color = Colof4fToC2DColor32(g_currentColor);
  DrawLine(x1, y1, x2, y2, lineWidth);
  DrawLine(x2, y2, x3, y3, lineWidth);
  DrawLine(x3, y3, x1, y1, lineWidth);
}

void DrawTriangle(const Point2f &p1, const Point2f &p2, const Point2f &p3,
                  float lineWidth) {
  DrawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, lineWidth);
}

void FillTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
  u32 Color = Colof4fToC2DColor32(g_currentColor);
  C2D_DrawTriangle(x1, y1, Color, x2, y2, Color, x3, y3, Color, 0);
}

void FillTriangle(const Point2f &p1, const Point2f &p2, const Point2f &p3) {
  FillTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
}

void DrawRect(const Point2f &topLeft, float width, float height,
              float lineWidth) {
  DrawRect(topLeft.x, topLeft.y, width, height, lineWidth);
}

void DrawRect(const Rectf &rect, float lineWidth) {
  DrawRect(rect.left, rect.top, rect.width, rect.height, lineWidth);
}

void FillRect(float left, float top, float width, float height) {
  u32 Color = Colof4fToC2DColor32(g_currentColor);
  C2D_DrawRectSolid(left, top, 0, width, height, Color);
}

void FillRect(const Point2f &topLeft, float width, float height) {
  FillRect(topLeft.x, topLeft.y, width, height);
}

void FillRect(const Rectf &rect) {
  FillRect(rect.left, rect.top, rect.width, rect.height);
}

void DrawEllipse(float centerX, float centerY, float radX, float radY,
                 float lineWidth) {
  float dAngle{radX > radY ? float(g_Pi / radX) : float(g_Pi / radY)};
  u32 Color = Colof4fToC2DColor32(g_currentColor);

  C2D_DrawCircle(centerX, centerY, 0, radX, Color, Color, Color, Color);
  C2D_DrawEllipse(centerX, centerY, 0, radX, radY, Color, Color, Color, Color);
}

void DrawEllipse(const Point2f &center, float radX, float radY,
                 float lineWidth) {
  DrawEllipse(center.x, center.y, radX, radY, lineWidth);
}

void DrawEllipse(const Ellipsef &ellipse, float lineWidth) {
  DrawEllipse(ellipse.center.x, ellipse.center.y, ellipse.radiusX,
              ellipse.radiusY, lineWidth);
}

void FillEllipse(float centerX, float centerY, float radX, float radY) {
  C2D_DrawEllipseSolid(centerX, centerY, 0, radX, radY,
                       Colof4fToC2DColor32(g_currentColor));
}

void FillEllipse(const Ellipsef &ellipse) {
  FillEllipse(ellipse.center.x, ellipse.center.y, ellipse.radiusX,
              ellipse.radiusY);
}

void FillEllipse(const Point2f &center, float radX, float radY) {
  FillEllipse(center.x, center.y, radX, radY);
}

// void DrawArc(float centerX, float centerY, float radX, float radY, float
// fromAngle, float tillAngle, float lineWidth)
// {
// 	if (fromAngle > tillAngle)
// 	{
// 		return;
// 	}

// 	// flip the angles (because view is flipped)
// 	fromAngle *= -1;
// 	tillAngle *= -1;
// 	std::swap(fromAngle, tillAngle); // from becomes to and vice versa

// 	float dAngle{radX > radY ? float(g_Pi / radX) : float(g_Pi / radY)};

// 	glLineWidth(lineWidth);
// 	glBegin(GL_LINE_STRIP);
// 	{
// 		for (float angle = fromAngle; angle < tillAngle; angle +=
// dAngle)
// 		{
// 			glVertex2f(centerX + radX * float(cos(angle)), centerY +
// radY * float(sin(angle)));
// 		}
// 		glVertex2f(centerX + radX * float(cos(tillAngle)), centerY +
// radY * float(sin(tillAngle)));
// 	}
// 	glEnd();
// }

// void DrawArc(const Point2f &center, float radX, float radY, float fromAngle,
// float tillAngle, float lineWidth)
// {
// 	DrawArc(center.x, center.y, radX, radY, fromAngle, tillAngle,
// lineWidth);
// }

// void FillArc(float centerX, float centerY, float radX, float radY, float
// fromAngle, float tillAngle)
// {
// 	if (fromAngle > tillAngle)
// 	{
// 		return;
// 	}

// 	// flip the angles (because view is flipped)
// 	fromAngle *= -1;
// 	tillAngle *= -1;
// 	std::swap(fromAngle, tillAngle); // from becomes to and vice versa

// 	float dAngle{radX > radY ? float(g_Pi / radX) : float(g_Pi / radY)};

// 	glBegin(GL_POLYGON);
// 	{
// 		glVertex2f(centerX, centerY);
// 		for (float angle = fromAngle; angle < tillAngle; angle +=
// dAngle)
// 		{
// 			glVertex2f(centerX + radX * float(cos(angle)), centerY +
// radY * float(sin(angle)));
// 		}
// 		glVertex2f(centerX + radX * float(cos(tillAngle)), centerY +
// radY * float(sin(tillAngle)));
// 	}
// 	glEnd();
// }

// void FillArc(const Point2f &center, float radX, float radY, float fromAngle,
// float tillAngle)
// {
// 	FillArc(center.x, center.y, radX, radY, fromAngle, tillAngle);
// }

// void DrawPolygon(const std::vector<Point2f> &vertices, bool closed, float
// lineWidth)
// {
// 	DrawPolygon(vertices.data(), vertices.size(), closed, lineWidth);
// }

// void DrawPolygon(const Point2f *pVertices, size_t nrVertices, bool closed,
// float lineWidth)
// {
// 	glLineWidth(lineWidth);
// 	closed ? glBegin(GL_LINE_LOOP) : glBegin(GL_LINE_STRIP);
// 	{
// 		for (size_t idx{0}; idx < nrVertices; ++idx)
// 		{
// 			glVertex2f(pVertices[idx].x, pVertices[idx].y);
// 		}
// 	}
// 	glEnd();
// }

// void FillPolygon(const std::vector<Point2f> &vertices)
// {
// 	FillPolygon(vertices.data(), vertices.size());
// }

// void FillPolygon(const Point2f *pVertices, size_t nrVertices)
// {
// 	glBegin(GL_POLYGON);
// 	{
// 		for (size_t idx{0}; idx < nrVertices; ++idx)
// 		{
// 			glVertex2f(pVertices[idx].x, pVertices[idx].y);
// 		}
// 	}
// 	glEnd();
// }
#pragma endregion OpenGLDrawFunctionality

// #pragma region textureImplementations

bool TextureFromFile(const std::string &path, Texture &texture) {
  C2D_SpriteSheet spriteSheet = C2D_SpriteSheetLoad(path.c_str());

  if (spriteSheet == nullptr) {
    svcBreak(USERBREAK_PANIC);
    return false;
  }

  texture.image = C2D_SpriteSheetGetImage(spriteSheet, 0);
  texture.width = texture.image.tex->width;
  texture.height = texture.image.tex->height;

  return true;
}

// 	bool TextureFromString(const std::string& text, const std::string&
// fontPath, int ptSize, const Color4f& textColor, Texture& texture)
// 	{
// 		// Create font
// 		TTF_Font* pFont{};
// 		pFont = TTF_OpenFont(("..\\" + fontPath).c_str(), ptSize);
// 		if (pFont == nullptr)
// 		{
// 			std::cout << "TextureFromString: Failed to load font!
// SDL_ttf Error: " << TTF_GetError(); 			std::cin.get();
// return false;
// 		}

// 		// Create texture using this fontand close font afterwards
// 		bool textureOk = TextureFromString(text, pFont, textColor,
// texture); 		TTF_CloseFont(pFont);

// 		return textureOk;
// 	}

// 	bool TextureFromString(const std::string& text, TTF_Font* pFont, const
// Color4f& color, Texture& texture)
// 	{
// 		if (pFont == nullptr)
// 		{
// 			std::cerr << "Texture::CreateFromString, invalid
// TTF_Font pointer\n"; 			return false;
// 		}

// 		//Render text surface
// 		SDL_Color textColor{};
// 		textColor.r = Uint8(color.r * 255);
// 		textColor.g = Uint8(color.g * 255);
// 		textColor.b = Uint8(color.b * 255);
// 		textColor.a = Uint8(color.a * 255);

// 		SDL_Surface* pLoadedSurface = TTF_RenderText_Blended(pFont,
// text.c_str(), textColor);
// 		//SDL_Surface* pLoadedSurface = TTF_RenderText_Solid(pFont,
// textureText.c_str(), textColor); 		if (pLoadedSurface == nullptr)
// 		{
// 			std::cerr << "TextureFromString: Unable to render text
// surface! SDL_ttf Error: " << TTF_GetError() << '\n';
// return false;
// 		}

// 		// copy to video memory
// 		TextureFromSurface(pLoadedSurface, texture);

// 		//Free loaded surface
// 		SDL_FreeSurface(pLoadedSurface);

// 		return true;
// 	}

// 	void TextureFromSurface(const SDL_Surface* pSurface, Texture& texture)
// 	{
// 		//Get image dimensions
// 		texture.width = float(pSurface->w);
// 		texture.height = float(pSurface->h);

// 		// Get pixel format information and translate to OpenGl format
// 		GLenum pixelFormat{ GL_RGB };
// 		switch (pSurface->format->BytesPerPixel)
// 		{
// 		case 3:
// 			if (pSurface->format->Rmask == 0x000000ff)
// 			{
// 				pixelFormat = GL_RGB;
// 			}
// 			else
// 			{
// 				pixelFormat = GL_BGR;
// 			}
// 			break;
// 		case 4:
// 			if (pSurface->format->Rmask == 0x000000ff)
// 			{
// 				pixelFormat = GL_RGBA;
// 			}
// 			else
// 			{
// 				pixelFormat = GL_BGRA;
// 			}
// 			break;
// 		default:
// 			std::cerr << "TextureFromSurface error: Unknow pixel
// format, BytesPerPixel: " << pSurface->format->BytesPerPixel << "\nUse 32 bit
// or 24 bit images.\n";; 			texture.width = 0;
// texture.height = 0; 			return;
// 		}

// 		//Generate an array of textures.  We only want one texture (one
// element array), so trick
// 		//it by treating "texture" as array of length one.
// 		glGenTextures(1, &texture.id);

// 		//Select (bind) the texture we just generated as the current 2D
// texture OpenGL is using/modifying.
// 		//All subsequent changes to OpenGL's texturing state for 2D
// textures will affect this texture. 		glBindTexture(GL_TEXTURE_2D,
// texture.id); 		glPixelStorei(GL_UNPACK_ROW_LENGTH, pSurface->pitch /
// pSurface->format->BytesPerPixel);

// 		// check for errors.
// 		GLenum e = glGetError();
// 		if (e != GL_NO_ERROR)
// 		{
// 			std::cerr << "TextureFromSurface, error binding
// textures, Error id = " << e << '\n'; 			std::cerr <<
// "Can happen if a texture is created before performing the initialization code
// (e.g. a static Texture object).\n"; 			std::cerr << "There
// might be a white rectangle instead of the image.\n";
// texture.width = 0; 			texture.height = 0;
// return;
// 		}

// 		//Specify the texture's data.  This function is a bit tricky,
// and it's hard to find helpful documentation.  A summary:
// 		//   GL_TEXTURE_2D:    The currently bound 2D texture (i.e. the
// one we just made)
// 		//               0:    The mipmap level.  0, since we want to
// update the base level mipmap image (i.e., the image itself,
// 		//                         not cached smaller copies)
// 		//         GL_RGBA:    Specifies the number of color components
// in the texture.
// 		//                     This is how OpenGL will store the texture
// internally (kinda)--
// 		//                     It's essentially the texture's type.
// 		//      surface->w:    The width of the texture
// 		//      surface->h:    The height of the texture
// 		//               0:    The border.  Don't worry about this if
// you're just starting.
// 		//     pixelFormat:    The format that the *data* is in--NOT the
// texture!
// 		//GL_UNSIGNED_BYTE:    The type the data is in.  In SDL, the
// data is stored as an array of bytes, with each channel
// 		//                         getting one byte.  This is fairly
// typical--it means that the image can store, for each channel,
// 		//                         any value that fits in one byte (so 0
// through 255).  These values are to be interpreted as
// 		//                         *unsigned* values (since 0x00 should
// be dark and 0xFF should be bright).
// 		// surface->pixels:    The actual data.  As above, SDL's array
// of bytes. 		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pSurface->w,
// pSurface->h, 0, pixelFormat, GL_UNSIGNED_BYTE, pSurface->pixels);

// 		//Set the minification and magnification filters.  In this case,
// when the texture is minified (i.e., the texture's pixels (texels) are
// 		//*smaller* than the screen pixels you're seeing them on,
// linearly filter them (i.e. blend them together).  This blends four texels for
// 		//each sample--which is not very much.  Mipmapping can give
// better results.  Find a texturing tutorial that discusses these issues
// 		//further.  Conversely, when the texture is magnified (i.e., the
// texture's texels are *larger* than the screen pixels you're seeing
// 		//them on), linearly filter them.  Qualitatively, this causes
// "blown up" (overmagnified) textures to look blurry instead of blocky.
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
// GL_NEAREST); 		glTexParameteri(GL_TEXTURE_2D,
// GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// 	}

// 	void DeleteTexture(Texture& texture)
// 	{
// 		glDeleteTextures(1, &texture.id);
// 	}

void DrawTexture(const Texture &texture, const Point2f &dstTopLeft,
                 const Rectf &srcRect) {
  Rectf dstRect{dstTopLeft.x, dstTopLeft.y, srcRect.width, srcRect.height};
  C2D_DrawParams params{};
  params.pos = {dstRect.left, dstRect.top, srcRect.width, srcRect.height};

  C2D_DrawImage(texture.image, &params, nullptr);
}

// 	void DrawTexture(const Texture& texture, const Rectf& dstRect, const
// Rectf& srcRect)
// 	{
// 		// Determine texture coordinates using srcRect and default
// destination width and height 		float textLeft{};
// float textRight{}; 		float textTop{}; 		float
// textBottom{};

// 		float defaultDstWidth{};
// 		float defaultDstHeight{};
// 		if (!(srcRect.width > 0.0f && srcRect.height > 0.0f)) // No
// srcRect specified
// 		{
// 			// Use complete texture
// 			textLeft = 0.0f;
// 			textRight = 1.0f;
// 			textTop = 0.0f;
// 			textBottom = 1.0f;

// 			defaultDstHeight = texture.height;
// 			defaultDstWidth = texture.width;
// 		}
// 		else // srcRect specified
// 		{
// 			textLeft = srcRect.left / texture.width;
// 			textRight = (srcRect.left + srcRect.width) /
// texture.width; 			textTop = srcRect.top / texture.height;
// textBottom = (srcRect.top + srcRect.height) / texture.height;

// 			defaultDstHeight = srcRect.height;
// 			defaultDstWidth = srcRect.width;
// 		}

// 		// Determine vertex coordinates
// 		float vertexTop{ dstRect.top };
// 		float vertexLeft{ dstRect.left };
// 		float vertexBottom{};
// 		float vertexRight{};
// 		if (!(dstRect.width > 0.001f && dstRect.height > 0.001f)) // If
// no size specified use default size
// 		{
// 			vertexRight = vertexLeft + defaultDstWidth;
// 			vertexBottom = vertexTop + defaultDstHeight;
// 		}
// 		else
// 		{
// 			vertexRight = vertexLeft + dstRect.width;
// 			vertexBottom = vertexTop + dstRect.height;
// 		}

// 		// Tell opengl which texture we will use
// 		glBindTexture(GL_TEXTURE_2D, texture.id);
// 		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

// 		// Draw
// 		glEnable(GL_TEXTURE_2D);
// 		{
// 			glBegin(GL_QUADS);
// 			{
// 				glTexCoord2f(textLeft, textBottom);
// 				glVertex2f(vertexLeft, vertexBottom);

// 				glTexCoord2f(textLeft, textTop);
// 				glVertex2f(vertexLeft, vertexTop);

// 				glTexCoord2f(textRight, textTop);
// 				glVertex2f(vertexRight, vertexTop);

// 				glTexCoord2f(textRight, textBottom);
// 				glVertex2f(vertexRight, vertexBottom);
// 			}
// 			glEnd();
// 		}
// 		glDisable(GL_TEXTURE_2D);

// 	}
// #pragma endregion textureImplementations

#pragma region CollisionFunctionality
bool IsPointInCircle(const Point2f &point, const Circlef &circle) {
  const float distance{GetDistance(point, circle.center)};

  return (distance <= circle.radius);
}

bool IsPointInRect(const Point2f &point, const Rectf &rect) {
  const bool horizontalCheck{(point.x >= rect.left) &&
                             (point.x <= rect.left + rect.width)};
  const bool verticalCheck{(point.y >= rect.top) &&
                           (point.y <= rect.top + rect.height)};

  return (horizontalCheck && verticalCheck);
}

bool IsOverlapping(const Circlef &circle1, const Circlef &circle2) {
  const float distance{GetDistance(circle1.center, circle2.center)};

  return (distance <= circle1.radius + circle2.radius);
}

bool IsOverlapping(const Rectf &rect1, const Rectf &rect2) {
  if (rect2.left > (rect1.left + rect1.width))
    return false;
  if (rect1.left > (rect2.left + rect2.width))
    return false;

  if (rect2.top > (rect1.top + rect1.height))
    return false;
  if (rect1.top > (rect2.top + rect2.height))
    return false;

  return true;
}

#pragma endregion CollisionFunctionality

#pragma region MyFunctions

float GetDistance(const Point2f &point1, const Point2f &point2) {
  const float xDistance{point2.x - point1.x};
  const float yDistance{point2.y - point1.y};

  return sqrt(xDistance * xDistance + yDistance * yDistance);
}

#pragma endregion MyFunctions
} // namespace utils