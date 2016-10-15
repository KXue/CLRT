#include "geometry.hpp"
#include <math.h>
#include <sstream>

Vec_3t::Vec_3t(float x, float y, float z) : x(x), y(y), z(z){};

Vec_3t::Vec_3t(const Vec_3t &obj) : x(obj.x), y(obj.y), z(obj.z){};

Vec_3t Vec_3t::operator-() const { return Vec_3t(-x, -y, -z); };

Vec_3t Vec_3t::operator+(const Vec_3t &obj) const {
  return Vec_3t(x + obj.x, y + obj.y, z + obj.z);
};
Vec_3t Vec_3t::operator-(const Vec_3t &obj) const {
  return Vec_3t(x - obj.x, y - obj.y, z - obj.z);
};
float Vec_3t::operator*(const Vec_3t &obj) const {
  return (x * obj.x + y * obj.y + z * obj.z);
};

Vec_3t Vec_3t::operator*(const float f) const {
  return Vec_3t(f * x, f * y, f * z);
};

Vec_3t Vec_3t::operator/(const float f) const {
  return Vec_3t(x / f, y / f, z / f);
};

Vec_3t Vec_3t::cross(const Vec_3t &obj) const {
  return Vec_3t(y * obj.z - z * obj.y, z * obj.x - x * obj.z,
                x * obj.y - y * obj.x);
};

Vec_3t Vec_3t::getNormalized() const {
  float magnitude = getLength();
  const double epsilon = 5.96e-08;
  if (fabs(magnitude) > epsilon) {
    return Vec_3t(x / magnitude, y / magnitude, z / magnitude);
  }
  return Vec_3t();
};

float Vec_3t::getLength() const { return sqrt(x * x + y * y + z * z); };

Vec_3t operator*(const float f, const Vec_3t &obj) { return obj * f; };
Vec_3t operator/(const float f, const Vec_3t &obj) { return obj / f; };

std::string Vec_3t::toString() const {
  std::stringstream retStream;
  retStream << "x: " << x << " y: " << y << " z: " << z;
  return retStream.str();
}
