#include "geometry.hpp"
#include <math.h>
#include <sstream>
#include <iostream>

const static double epsilon = 5.96e-08;

Vec_3t::Vec_3t(float x, float y, float z) : x(x), y(y), z(z){};

Vec_3t::Vec_3t(const Vec_3t &obj) : x(obj.x), y(obj.y), z(obj.z){};

Vec_3t& Vec_3t::operator=(const Vec_3t &obj){
  x=obj.x;
  y=obj.y;
  z=obj.z;
  return *this;
};

Vec_3t Vec_3t::operator-() const { return Vec_3t(-x, -y, -z); };

Vec_3t Vec_3t::getNormalized() const {
  float magnitude = getLength();
  if (fabs(magnitude) > epsilon) {
    return Vec_3t(x / magnitude, y / magnitude, z / magnitude);
  }
  return Vec_3t();
};

float Vec_3t::getLength() const { return sqrt(x * x + y * y + z * z); };

std::string Vec_3t::toString() const {
  std::stringstream retStream;
  retStream << "x: " << x << " y: " << y << " z: " << z;
  return retStream.str();
};

Vec_3t operator+(const Vec_3t &obj, const Vec_3t &obj2){
  return Vec_3t(obj.x + obj2.x, obj.y + obj2.y, obj.z + obj2.z);
};

Vec_3t operator-(const Vec_3t &obj, const Vec_3t &obj2){
  return Vec_3t(obj.x - obj2.x, obj.y - obj2.y, obj.z - obj2.z);
};

float operator*(const Vec_3t &obj, const Vec_3t &obj2){
  return (obj.x * obj2.x + obj.y * obj2.y + obj.z * obj2.z);
}
Vec_3t operator*(const Vec_3t &obj, float f){
  return Vec_3t(obj.x * f, obj.y * f, obj.z * f);
};
Vec_3t operator*(float f, const Vec_3t &obj){
  return Vec_3t(obj.x * f, obj.y * f, obj.z * f);
}

Vec_3t operator/(const Vec_3t &obj, float f){
  if(f > epsilon){
    return Vec_3t(obj.x / f, obj.y / f, obj.z / f);
  }
  return Vec_3t();
}
Vec_3t operator/(float f, const Vec_3t &obj){
  if(f > epsilon){
    return Vec_3t(obj.x / f, obj.y / f, obj.z / f);
  }
    return Vec_3t();
};

Vec_3t cross(const Vec_3t &obj, const Vec_3t &obj2){
  return Vec_3t(obj.y * obj2.z - obj.z * obj2.y, obj.z * obj2.x - obj.x * obj2.z,
              obj.x * obj2.y - obj.y * obj2.x);
};