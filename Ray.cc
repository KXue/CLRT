#include "geometry.hpp"
#include <iostream>

Ray::Ray(Vec_3t origin, Vec_3t dir) : m_origin(Vec_3t(origin)), m_dir(Vec_3t(dir)){};
Ray::~Ray(){};

Vec_3t Ray::GetDirection() const { return m_dir; };
Vec_3t Ray::GetOrigin() const { return m_origin; };
