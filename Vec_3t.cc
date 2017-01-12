#include "geometry.hpp"
#include <math.h>
#include <sstream>
#include <iostream>

const static double epsilon = 5.96e-08;

Vec_3t::Vec_3t(float x, float y, float z) : m_x(x), m_y(y), m_z(z){};

Vec_3t::Vec_3t(const Vec_3t &obj) : m_x(obj.m_x), m_y(obj.m_y), m_z(obj.m_z){};

Vec_3t::~Vec_3t(){
};

Vec_3t& Vec_3t::operator=(const Vec_3t &obj){
  m_x=obj.m_x;
  m_y=obj.m_y;
  m_z=obj.m_z;
  return *this;
};

Vec_3t Vec_3t::operator-() const { return Vec_3t(-m_x, -m_y, -m_z); };

Vec_3t Vec_3t::GetNormalized() const {
  float magnitude = GetLength();
  if (fabs(magnitude) > epsilon) {
    return Vec_3t(m_x / magnitude, m_y / magnitude, m_z / magnitude);
  }
  return Vec_3t();
};

float Vec_3t::GetLength() const { return sqrt(m_x * m_x + m_y * m_y + m_z * m_z); };

std::string Vec_3t::ToString() const {
  std::stringstream retStream;
  retStream << "m_x: " << m_x << " m_y: " << m_y << " m_z: " << m_z;
  return retStream.str();
};

Vec_3t operator+(const Vec_3t &obj, const Vec_3t &obj2){
  return Vec_3t(obj.m_x + obj2.m_x, obj.m_y + obj2.m_y, obj.m_z + obj2.m_z);
};

Vec_3t operator-(const Vec_3t &obj, const Vec_3t &obj2){
  return Vec_3t(obj.m_x - obj2.m_x, obj.m_y - obj2.m_y, obj.m_z - obj2.m_z);
};

float operator*(const Vec_3t &obj, const Vec_3t &obj2){
  return (obj.m_x * obj2.m_x + obj.m_y * obj2.m_y + obj.m_z * obj2.m_z);
}
Vec_3t operator*(const Vec_3t &obj, float f){
  return Vec_3t(obj.m_x * f, obj.m_y * f, obj.m_z * f);
};
Vec_3t operator*(float f, const Vec_3t &obj){
  return Vec_3t(obj.m_x * f, obj.m_y * f, obj.m_z * f);
}

Vec_3t operator/(const Vec_3t &obj, float f){
  if(f > epsilon){
    return Vec_3t(obj.m_x / f, obj.m_y / f, obj.m_z / f);
  }
  return Vec_3t();
}
Vec_3t operator/(float f, const Vec_3t &obj){
  if(f > epsilon){
    return Vec_3t(obj.m_x / f, obj.m_y / f, obj.m_z / f);
  }
    return Vec_3t();
};

Vec_3t cross(const Vec_3t &obj, const Vec_3t &obj2){
  return Vec_3t(obj.m_y * obj2.m_z - obj.m_z * obj2.m_y, obj.m_z * obj2.m_x - obj.m_x * obj2.m_z,
              obj.m_x * obj2.m_y - obj.m_y * obj2.m_x);
};