#ifndef CAMERA_H
#define CAMERA_H
#define _USE_MATH_DEFINES // for C++
#include "geometry.hpp"
#include <cmath>
#include <vector>

class Camera {
  bool curved;
  int pixelWidth;
  int pixelHeight;
  float fov; // in radians of course
  float aspectRatio;
  float focalLength;
  Vec_t position;
  Vec_t up;
  Vec_t direction;

  std::vector<Ray> makeCurvedPrimaryRays();
  std::vector<Ray> makeFlatPrimaryRays();
  Vec_t findTopLeft();

public:
  Camera(int pixelWidth = 800, int pixelHeight = 600, float fov = (M_PI / 2.0),
         float aspectRatio = (4.0 / 3.0), float focalLength = 1.0,
         bool curved = false);
  ~Camera();

  void rotate(float dxAxis, float dyAxis, float dzAxis);
  void translate(float dx, float dy, float dz);
  std::vector<Ray> makePrimaryRays();
};

#endif
