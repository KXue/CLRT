#ifndef CAMERA_H
#define CAMERA_H
#define _USE_MATH_DEFINES // for C++
#include "geometry.hpp"
#include <cmath>
#include <vector>

class Camera {
  bool m_curved;
  int m_pixelWidth;
  int m_pixelHeight;
  float m_fov; // in radians
  float m_aspectRatio;
  float m_focalLength;
  Vec_3t m_position;
  Vec_3t m_up;
  Vec_3t m_direction;

  std::vector<Ray> MakeCurvedPrimaryRays();
  std::vector<Ray> MakeFlatPrimaryRays();
  Vec_3t FindTopLeft(Vec_3t left);

public:
  Camera(int pixelWidth = 800, int pixelHeight = 600, float fov = (M_PI / 2.0),
         float aspectRatio = (4.0 / 3.0), float focalLength = 1.0,
         bool curved = false);
  ~Camera();

  void Rotate(float dxAxis, float dyAxis, float dzAxis);
  void Translate(float dx, float dy, float dz);
  std::vector<Ray> MakePrimaryRays();
};

#endif
