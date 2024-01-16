#pragma once
#include <citro2d.h>

struct Point2f {
  float x;
  float y;
};

struct Rectf {
  float left;
  float top;
  float width;
  float height;
};

struct Color4f {
  float r;
  float g;
  float b;
  float a;
};

struct Circlef {
  Point2f center;
  float radius;
};

struct Ellipsef {
  Point2f center;
  float radiusX;
  float radiusY;
};

namespace utils {
struct Texture {
  C2D_Image image;
  float width;
  float height;
};
} // namespace utils
