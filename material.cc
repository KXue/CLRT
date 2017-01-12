#include "material.hpp"

Material::Material(float r, float g, float b, int computeColorType): computeColorType(computeColorType){
	color[0] = r;
	color[1] = g;
	color[2] = b;
}
int Material::getComputeColorType(){
	return computeColorType;
}
float* Material::GetColor(){
	return color;
}