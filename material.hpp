#ifndef MATERIAL_H
#define MATERIAL_H

class Material {
  float color[3];
  int computeColorType;
public:
  Material(float r = 0.0f, float g = 1.0f, float b = 0.0f, int computeColorType = 0);
  int getComputeColorType();
  float* GetColor();
};

#endif
