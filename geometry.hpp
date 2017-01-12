#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <string>
#include "material.hpp"

class Vec_3t {
  float m_x;
  float m_y;
  float m_z;

public:
  Vec_3t(float x = 0, float y = 0, float z = 0);
  Vec_3t(const Vec_3t &obj);
  ~Vec_3t();
  Vec_3t& operator=(const Vec_3t &obj);
  Vec_3t operator-() const;
  Vec_3t GetNormalized() const;
  float GetLength() const;
  std::string ToString() const;

  friend Vec_3t operator+(const Vec_3t &obj, const Vec_3t &obj2);
  friend Vec_3t operator-(const Vec_3t &obj, const Vec_3t &obj2);
  friend float operator*(const Vec_3t &obj, const Vec_3t &obj2);
  friend Vec_3t operator*(const Vec_3t &obj, const float);
  friend Vec_3t operator/(const Vec_3t &obj, const float);
  friend Vec_3t operator*(const float, const Vec_3t &);
  friend Vec_3t operator/(const float, const Vec_3t &);
  friend Vec_3t cross(const Vec_3t &obj, const Vec_3t &obj2);
};

class Qua_t {
  float a;
  float b;
  float c;
  float d;

public:
  Qua_t();
  Qua_t(const Vec_3t &first, const Vec_3t &second);
  Qua_t(float a, float b, float c, float d);
  ~Qua_t();
};

class Ray {
  Vec_3t m_origin;
  Vec_3t m_dir;

public:
  Ray(Vec_3t origin = Vec_3t(), Vec_3t dir = Vec_3t(0, 0, 1));
  ~Ray();
  Vec_3t GetDirection() const;
  Vec_3t GetOrigin() const;
};

class Body {
public:
  virtual Material GetMaterial() = 0;
  virtual bool Intersects(const Ray &ray, Vec_3t &point) = 0;
  virtual void Translate(int dx, int dy, int dz) = 0;
  virtual void Rotate(int dxAxis, int dyAxis, int dzAxis) = 0;
};

class Sphere : public Body {
  Vec_3t m_position;
  Vec_3t m_direction;
  Vec_3t m_up;
  float radius;
  Material m_material;

public:
  Sphere(Material material, float radius = 1, Vec_3t position = Vec_3t(), Vec_3t direction = Vec_3t(0, 0, 1), Vec_3t up = Vec_3t(0, 1, 0));
  Sphere(Material material, float radius = 1, float x = 0, float y = 0, float z = 0, float dx = 0, float dy = 0, float dz = 1, float ux = 0, float uy = 1, float uz = 0);
  ~Sphere();
  Material GetMaterial();
  bool Intersects(const Ray &ray, Vec_3t &point);
  void Translate(int dx, int dy, int dz);
  void Rotate(int dxAxis, int dyAxis, int dzAxis);
};

class Plane : public Body {
  Vec_3t m_normal;
  Vec_3t m_point;
  Material m_material;

public:
  Plane();
  Plane(Material m);
  Plane(Material m, Vec_3t normal, Vec_3t point);
  ~Plane();
};

class Light {
  Vec_3t m_position;
  Vec_3t m_direction;
  Vec_3t m_up;
  bool directional;
  float color[4];

public:
  Light();
  Light(Vec_3t position, Vec_3t direction, float color[4], bool directional = false);
  ~Light();
};

#endif
