#include <fstream>
#include <iostream>
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif
int main() {
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
  std::ifstream file("kernel.txt");

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

  std::cout << "Creating Data Buffers" << std::endl;
  // create data buffers
  cl_mem output =
      clCreateBuffer(context, CL_MEM_WRITE_ONLY, 10 * sizeof(cl_int), NULL, 0);
  cl_mem buffer1 =
      clCreateBuffer(context, CL_MEM_READ_WRITE, 10 * sizeof(cl_int), NULL, 0);
  cl_mem buffer2 =
      clCreateBuffer(context, CL_MEM_READ_WRITE, 10 * sizeof(cl_int), NULL, 0);

  clSetKernelArg(kernel, 0, sizeof(output), (void *)&output);
  clSetKernelArg(kernel, 1, sizeof(buffer1), (void *)&buffer1);
  clSetKernelArg(kernel, 2, sizeof(buffer2), (void *)&buffer2);

  // fill data buffers
  std::cout << "Filling Data Buffers" << std::endl;

  cl_int *buffer1Ptr =
      (cl_int *)clEnqueueMapBuffer(queue, buffer1, CL_TRUE, CL_MAP_WRITE, 0,
                                   10 * sizeof(cl_int), 0, NULL, NULL, NULL);

  cl_int *buffer2Ptr =
      (cl_int *)clEnqueueMapBuffer(queue, buffer2, CL_TRUE, CL_MAP_WRITE, 0,
                                   10 * sizeof(cl_int), 0, NULL, NULL, NULL);

  for (int i = 0; i < 10; i++) {
    buffer1Ptr[i] = i;
    buffer2Ptr[i] = i;
  }

  clEnqueueUnmapMemObject(queue, buffer1, buffer1Ptr, 0, 0, 0);
  clEnqueueUnmapMemObject(queue, buffer2, buffer2Ptr, 0, 0, 0);

  size_t global_work_size = 10;

  // execute kernel
  std::cout << "Executing Kernel" << std::endl;

  clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_work_size, NULL, 0,
                         NULL, NULL);

  // look at results
  std::cout << "Printing Results" << std::endl;

  cl_int *resultBufferPtr =
      (cl_int *)clEnqueueMapBuffer(queue, output, CL_TRUE, CL_MAP_READ, 0,
                                   10 * sizeof(cl_int), 0, NULL, NULL, NULL);

  for (int i = 0; i < 10; i++) {
    std::cout << "ptr[" << i << "] = " << resultBufferPtr[i] << std::endl;
  }
  return 0;
}
