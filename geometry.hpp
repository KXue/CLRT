#ifndef GEOMETRY_H
#define GEOMETRY_H

class Material;
class Quaternion {
  float a;
  float b;
  float c;
  float d;

public:
  Quaternion();
  Quaternion(float a, float b, float c, float d);
  ~Quaternion();
};

class Ray {
  float origin[3];
  float dir[3];

public:
  Ray();
  Ray(float origin[3], float dir[3]);
  ~Ray();
};

class Body {
public:
  virtual void getMaterial() = 0;
  virtual bool intersects(const Ray &ray) = 0;
  virtual void translate(int dx, int dy, int dz);
  virtual void rotate(int dxAxis, int dyAxis, int dzAxis);
  virtual void rotate(const Quaternion &first, const Quaternion &second);

protected:
  Material *m;
  float transform[16];
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
