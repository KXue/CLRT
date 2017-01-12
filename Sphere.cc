#include "geometry.hpp"
#include "material.hpp"
#include <cmath>

Sphere::Sphere(Material material, float radius, Vec_3t position, Vec_3t direction, Vec_3t up)
    : m_position(Vec_3t(position)), m_direction(direction), m_up(up), radius(radius), m_material(material){};

Sphere::Sphere(Material material, float radius, float x, float y, float z, float dx, float dy, float dz, float ux, float uy, float uz)
    : m_position(Vec_3t(x, y, z)), m_direction(Vec_3t(dx, dy, dz)), m_up(Vec_3t(ux, uy, uz)), radius(radius), m_material(material){};

Sphere::~Sphere() {};

Material Sphere::GetMaterial() { return m_material; };

bool Sphere::Intersects(const Ray &ray, Vec_3t &point) {
  Vec_3t rayPos = ray.GetOrigin();
  Vec_3t rayDir = ray.GetDirection();
  Vec_3t lenVector = rayPos - m_position;
  float b = (rayDir * lenVector);
  float c = (lenVector * lenVector) - (radius * radius);

  const double epsilon = 5.96e-08;
  float det = b * b - c;
  
  if (det < epsilon) {
    return false;
  }
  
  float largeD = -b + sqrt(b * b - c);
  
  if (largeD < epsilon) {
    return false;
  }
  // slight cause for concern here (scoping)
  float smallD = -b - sqrt(b * b - c);
  
  if (epsilon < smallD) {
    point = rayPos + smallD * rayDir.GetNormalized();
  } else {
    point = rayPos + largeD * rayDir.GetNormalized();
  }
  
  return true;
};
void Sphere::Translate(int dx, int dy, int dz) {
  m_position = m_position + Vec_3t(dx, dy, dz);
};
void Sphere::Rotate(int dxAxis, int dyAxis, int dzAxis){};
