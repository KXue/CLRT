#ifndef MESH_H
#define MESH_H
#include <glm/glm.hpp>

class Vertex {
public:
protected:
private:
};

class Mesh {
public:
  Mesh();

  void Draw();

  virtual ~Mesh();

private:
  Mesh(const Mesh &other) {}
  void operator=(const Mesh &other) {}
};

#endif
