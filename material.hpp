#ifndef MATERIAL_H
#define MATERIAL_H

class Material {
  int computeColorType;
  float color[4];
  float reflectivity;
  float refractivity;

public:
  Material();
  Material(int computeColorType = 0, float reflectivity = 0,
           float refractivity = 0);
  Material(float color[4], int computeColorType = 0, float reflectivity = 0,
           float refractivity = 0);
  ~Material();
  int getComputeColorType();
  const float &getColor() const;
  float getReflectivity();
  float getRefractivity();
};

#endif
