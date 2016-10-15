#include "geometry.hpp"

Ray::Ray() : origin(Vec_3t()), dir(Vec_3t(0, 0, 1)){};
Ray::Ray(Vec_3t origin, Vec_3t dir) : origin(origin), dir(dir){};
Vec_3t Ray::getDir() const { return dir; };
Vec_3t Ray::getPosition() const { return origin; };
