#ifndef CAMERA_H
#define CAMERA_H
#define _USE_MATH_DEFINES // for C++
#include <cmath>

class Ray;
class Quaternion;

class Camera {
  bool curved;
  int pixelWidth;
  int pixelHeight;
  float fov; // in radians of course
  float aspectRatio;
  float focalLength;
  float transform[16];

public:
  Camera();
  Camera(int pixelWidth = 800, int pixelHeight = 600, float fov = (M_PI / 2.0),
         float aspectRatio = (4.0 / 3.0), bool curved = false);
  ~Camera();

  void rotate(Quaternion *first, Quaternion *second);
  void rotate(float dxAxis, float dyAxis, float dzAxis);
  void translate(float dx, float dy, float dz);
  void shootPrimaryRays(Ray (&rays)[]);
};

#endif
