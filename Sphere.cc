#include "geometry.hpp"
#include "material.hpp"
#include <cmath>

Sphere::Sphere(Material *m, float radius, Vec_3t pos)
    : pos(pos), radius(radius), m(m){};
Sphere::~Sphere() { delete m; };

Material *Sphere::getMaterial() { return m; };
bool Sphere::intersects(const Ray &ray, Vec_3t &point) {
  Vec_3t rayPos = ray.getPosition();
  Vec_3t rayDir = ray.getDir();
  Vec_3t lenVector = rayPos - pos;
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
    point = rayPos + smallD * rayDir.getNormalized();
  } else {
    point = rayPos + largeD * rayDir.getNormalized();
  }
  return true;
};
void Sphere::translate(int dx, int dy, int dz) {
  pos = pos + Vec_3t(dx, dy, dz);
};
void Sphere::rotate(int dxAxis, int dyAxis, int dzAxis){};
