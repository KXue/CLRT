#include "camera.hpp"
#include "geometry.hpp"
#include <iostream>

Camera::Camera(int pixelWidth, int pixelHeight, float fov, float aspectRatio,
               float focalLength, bool curved)
    : curved(curved), pixelWidth(pixelWidth), pixelHeight(pixelHeight),
      fov(fov), aspectRatio(aspectRatio), focalLength(focalLength),
      position(Vec_3t(0.0, 0.0, 0.0)), up(Vec_3t(0.0, 1.0, 0.0)),
      direction(Vec_3t(0.0, 0.0, -1.0)) {}

Camera::~Camera() {}

// void Camera::rotate(const Quaternion *first, const Quaternion *second) {}

void Camera::rotate(float dxAxis, float dyAxis, float dzAxis) {}

void Camera::translate(float dx, float dy, float dz) {}

std::vector<Ray> Camera::makePrimaryRays() {
  if (curved) {
    return makeCurvedPrimaryRays();
  } else {
    return makeFlatPrimaryRays();
  }
}
//<editor-fold> Private Methods ************************************************
std::vector<Ray> Camera::makeCurvedPrimaryRays() {
  std::vector<Ray> rays;
  float dx = fov / float(pixelWidth);
  float dy = fov / (float(pixelHeight) * aspectRatio);
  float angleX = (fov / 2) - (dx / 2);
  float angleY = (fov / (2 * aspectRatio)) - (dy / 2);

  for (int i = 0; i < pixelHeight; i++) {
    for (int j = 0; j < pixelWidth; j++) {
    }
  }

  return rays;
};

std::vector<Ray> Camera::makeFlatPrimaryRays() {
  std::vector<Ray> rays;
  Vec_3t left = up.cross(direction);

  float sideLength = focalLength * tan(fov / 2);
  float topLength = sideLength / aspectRatio;

  Vec_3t dy = -(up * topLength * 2 / pixelHeight);
  Vec_3t dx = -(left * sideLength * 2 / pixelWidth);

  Vec_3t topLeft = direction * focalLength + up * topLength + left * sideLength;
  Vec_3t screenPoint;

  for (int i = 0; i < pixelHeight; i++) {
    for (int j = 0; j < pixelWidth; j++) {
      screenPoint = topLeft + dx * j + dy * i;
      rays.push_back(
          Ray(screenPoint, (screenPoint - position).getNormalized()));
    }
  }
  return rays;
};
//</editor-fold>
