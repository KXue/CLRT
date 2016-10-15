#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <string>
class Material;

// typedef float vec_t;
// typedef vec_t vec_3t[3];
// typedef vec_t vec_4t[4];
// typedef vec_t qua_t[4];

class Qua_t {
  float a;
  float b;
  float c;
  float d;

public:
  Qua_t();
  Qua_t(float a, float b, float c, float d);
  ~Qua_t();
};

class Vec_3t {
  float x;
  float y;
  float z;

public:
  Vec_3t(float x = 0, float y = 0, float z = 0);
  Vec_3t(const Vec_3t &obj);
  Vec_3t operator-() const;
  Vec_3t operator+(const Vec_3t &obj) const;
  Vec_3t operator-(const Vec_3t &obj) const;
  float operator*(const Vec_3t &obj) const;
  Vec_3t operator*(const float)const;
  Vec_3t operator/(const float) const;
  Vec_3t cross(const Vec_3t &obj) const;
  Vec_3t getNormalized() const;
  float getLength() const;
  std::string toString() const;
};

Vec_3t operator*(const float, const Vec_3t &);
Vec_3t operator/(const float, const Vec_3t &);

class Ray {
  Vec_3t origin;
  Vec_3t dir;

public:
  Ray();
  Ray(Vec_3t origin, Vec_3t dir);
  Vec_3t getDir() const;
  Vec_3t getPosition() const;
};

class Body {
public:
  virtual Material *getMaterial() = 0;
  virtual bool intersects(const Ray &ray, Vec_3t &point) = 0;
  virtual void translate(int dx, int dy, int dz) = 0;
  virtual void rotate(int dxAxis, int dyAxis, int dzAxis) = 0;
};

class Sphere : public Body {
  Vec_3t pos;
  float radius;
  Material *m;

public:
  Sphere(Material *m = nullptr, float radius = 1, Vec_3t pos = Vec_3t());
  ~Sphere();
  Material *getMaterial();
  bool intersects(const Ray &ray, Vec_3t &point);
  void translate(int dx, int dy, int dz);
  void rotate(int dxAxis, int dyAxis, int dzAxis);
};

class Plane : public Body {
  Vec_3t normal;
  Vec_3t point;
  Material *m;

public:
  Plane();
  Plane(Material *m);
  Plane(Material *m, Vec_3t normal, Vec_3t point);
  ~Plane();
};

class Light {
  Vec_3t pos;
  Vec_3t dir;
  bool directional;
  float color[4];

public:
  Light();
  Light(Vec_3t pos, Vec_3t dir, float color[4], bool directional = false);
  ~Light();
};

#endif
