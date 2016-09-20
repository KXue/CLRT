#include <fstream>
#include <iostream>
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>

#include "camera.hpp"
#include "geometry.hpp"
#include "material.hpp"

#endif

int main() {
  //<editor-fold> OPENCL BOILERPLATE *******************************************

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

  //</editor-fold>

  //<editor-fold> DEFINE GEOMETRY **********************************************
  // for now start simple

  //</editor-fold>
}