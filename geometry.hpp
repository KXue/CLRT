#ifndef GEOMETRY_H
#define GEOMETRY_H

class Material;
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

class Vec_t {
  float x;
  float y;
  float z;

public:
  Vec_t();
  Vec_t(float x, float y, float z);
  ~Vec_t();
  Vec_t operator+(const Vec_t &);
  Vec_t operator*(const Vec_t &);
  Vec_t cross(const Vec_t &);
  Vec_t getNormalized();
  float getLength();
};

Vec_t operator*(const float, const Vec_t &);

Vec_t operator*(const Vec_t &, const float);

class Ray {
  Vec_t origin;
  Vec_t dir;

public:
  Ray();
  Ray(Vec_t origin, Vec_t dir);
  ~Ray();
};

class Body {
public:
  virtual void getMaterial() = 0;
  virtual bool intersects(const Ray &ray) = 0;
  virtual void translate(int dx, int dy, int dz);
  virtual void rotate(int dxAxis, int dyAxis, int dzAxis);

protected:
  Material *m;
};

class Sphere : public Body {
  float pos[3];
  float radius;

public:
  Sphere();
  Sphere(Material *m, float radius);
  Sphere(Material *m, float radius, float pos[3]);
  ~Sphere();
};

class Plane : public Body {
  float normal[3];
  float point[3];

public:
  Plane();
  Plane(Material *m);
  Plane(Material *m, float normal[3], float point[3]);
  ~Plane();
};

class Light {
  float pos[3];
  float dir[3];
  bool directional;
  float color[4];

public:
  Light();
  Light(float pos[3], float dir[3], float color[4], bool directional = false);
  ~Light();
};

#endif
