#ifndef GEOMETRY_H
#define GEOMETRY_H

class Material;

class Sphere {
  Material *m;
  float pos[3];
  float radius;

public:
  Sphere();
  Sphere(Material *m, float radius);
  Sphere(Material *m, float radius, float pos[3]);
  ~Sphere();
};

class Plane {
  Material *m;
  float normal[3];
  float point[3];

public:
  Plane();
  Plane(Material *m);
  Plane(Material *m, float normal[3], float point[3]);
  ~Plane();
};

class Ray {
  float origin[3];
  float dir[3];

public:
  Ray();
  Ray(float origin[3], float dir[3]);
  ~Ray();
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
