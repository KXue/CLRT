#include "camera.hpp"
#include "geometry.hpp"
#include <iostream>

Camera::Camera(int pixelWidth, int pixelHeight, float fov, float aspectRatio,
               float focalLength, bool curved)
    : m_curved(curved), m_pixelWidth(pixelWidth), m_pixelHeight(pixelHeight),
      m_fov(fov), m_aspectRatio(aspectRatio), m_focalLength(focalLength),
      m_position(Vec_3t(0.0, 0.0, 0.0)), m_up(Vec_3t(0.0, 1.0, 0.0)),
      m_direction(Vec_3t(0.0, 0.0, -1.0)) {}

Camera::~Camera() {}


void Camera::Rotate(float dxAxis, float dyAxis, float dzAxis) {}

void Camera::Translate(float dx, float dy, float dz) {}

std::vector<Ray> Camera::MakePrimaryRays() {
  if (m_curved) {
    return MakeCurvedPrimaryRays();
  } else {
    return MakeFlatPrimaryRays();
  }
}
//<editor-fold> Private Methods ************************************************
std::vector<Ray> Camera::MakeCurvedPrimaryRays() {
  std::vector<Ray> rays;
  float dx = m_fov / float(m_pixelWidth);
  float dy = m_fov / (float(m_pixelHeight) * m_aspectRatio);
  float angleX = (m_fov / 2) - (dx / 2);
  float angleY = (m_fov / (2 * m_aspectRatio)) - (dy / 2);

  for (int i = 0; i < m_pixelHeight; i++) {
    for (int j = 0; j < m_pixelWidth; j++) {
    }
  }

  return rays;
};

std::vector<Ray> Camera::MakeFlatPrimaryRays() {
  std::vector<Ray> rays;
  Vec_3t left = cross(m_up, m_direction);


  float sideLength = m_focalLength * tan(m_fov / 2);
  float topLength = sideLength / m_aspectRatio;

  Vec_3t dy = -(m_up * topLength * 2 / m_pixelHeight);
  Vec_3t dx = -(left * sideLength * 2 / m_pixelWidth);


  Vec_3t topLeft = m_direction * m_focalLength + m_up * topLength + left * sideLength;
  Vec_3t screenPoint;


  for (int i = 0; i < m_pixelHeight; i++) {
    for (int j = 0; j < m_pixelWidth; j++) {
      screenPoint = topLeft + dx * j + dy * i;
      rays.push_back(
          Ray(screenPoint, (screenPoint - m_position).GetNormalized()));
    }
  }
  return rays;
};
//</editor-fold>
