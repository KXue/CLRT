#include <fstream>
#include <iostream>
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#include <OpenGL/glu.h>
#else
#include <CL/cl.h>
#include <GL/glu.h>
#endif

#include "camera.hpp"
#include "display.hpp"
#include "geometry.hpp"
#include "material.hpp"
#include <vector>

void Update(){

}

void Render(){

}

int main() {
  Display display(800, 600, "Testing123");

  Camera testCamera = Camera();

  Material testMaterial = Material();

  Sphere testSphere = Sphere(testMaterial, 2, Vec_3t(0, 0, -10), Vec_3t(0, 0, 1), Vec_3t(0, 1, 0));

  unsigned char *buffer = new unsigned char[600 * 4 * 800];
  Vec_3t testVect;
  float* outMat;
  std::vector<Ray> rays;
  while (!display.IsClosed()) {
    rays = testCamera.MakePrimaryRays();
    for (int i = 0; i < 600 * 800; i++) {
      if (testSphere.Intersects(rays[i], testVect)) {
        outMat = testSphere.GetMaterial().GetColor();
        buffer[i * 4] = outMat[0] * 255;
        buffer[i * 4 + 1] = outMat[1] * 255;
        buffer[i * 4 + 2] = outMat[2] * 255;
        buffer[i * 4 + 3] = 1;
      } else {
        buffer[i * 4] = 0;
        buffer[i * 4 + 1] = 0;
        buffer[i * 4 + 2] = 0;
        buffer[i * 4 + 3] = 1;
      }
    }
    rays.clear();
    display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
    display.DrawTexture(buffer, 800, 600);
    display.Update();
  }

  delete[] buffer;
  return 0;
  /*

  std::cout << "Getting Platform" << std::endl;
  // Get platform
  cl_platform_id platform;

  clGetPlatformIDs(1, &platform, NULL);

  std::cout << "Finding GPU" << std::endl;
  // Find GPU
  cl_device_id device;

  clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);

  std::cout << "Creating Context and Command Queue" << std::endl;
  // Create context and command queue
  cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
  cl_command_queue queue = clCreateCommandQueue(context, device, 0, NULL);

  std::cout << "Performing Runtime Compilation" << std::endl;
  // perform runtime source compilation
  // obtain kernel entry point
  std::string source;
  std::ifstream file("adder.cl");

  while (!file.eof()) {
    char line[256];
    file.getline(line, 255);
    source += line;
  }
  std::cout << "kernel code:" << std::endl;
  std::cout << source << std::endl;
  std::cout << "end kernel code" << std::endl;

  const char *str = source.c_str();
  cl_program program = clCreateProgramWithSource(context, 1, &str, NULL, NULL);
  cl_int result = clBuildProgram(program, 1, &device, NULL, NULL, NULL);

  if (result) {
    std::cout << "Error during compilation! (" << result << ")" << std::endl;

    // Shows the log
    char *build_log;
    size_t log_size;
    // First call to know the proper size
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL,
                          &log_size);
    build_log = new char[log_size + 1];
    // Second call to get the log
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size,
                          build_log, NULL);
    build_log[log_size] = '\0';
    std::cout << build_log << std::endl;
    delete[] build_log;
  }

  cl_kernel kernel = clCreateKernel(program, "adder", NULL);

  */
}
