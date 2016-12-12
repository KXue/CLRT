#include "geometry.hpp"

Ray::Ray() : origin(new Vec_3t()), dir(new Vec_3t(0, 0, 1)){};
Ray::Ray(Vec_3t origin, Vec_3t dir) : origin(new Vec_3t(origin)), dir(new Vec_3t(dir)){};
Ray::~Ray(){
	delete origin;
	delete dir;
};

Vec_3t Ray::getDir() const { return *dir; };
Vec_3t Ray::getPosition() const { return *origin; };
