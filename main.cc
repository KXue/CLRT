#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
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
#include "geometry.hpp"
#include "material.hpp"
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

SDL_Window *gWindow = NULL;
SDL_GLContext gGlContext;

void SetOpenGLVersion() {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
  // SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
}

void Display_InitGL() {
  glShadeModel(GL_SMOOTH);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

int Display_SetViewport(int width, int height) {
  GLfloat ratio;

  if (height == 0) {
    height = 1;
  }

  ratio = GLfloat(width) / GLfloat(height);
  glViewport(0, 0, GLsizei(width), GLsizei(height));
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f, ratio, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  return true;
}

void Display_Render(unsigned char *pixels) {
  glBindTexture(GL_TEXTURE_2D, 1);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, pixels);

  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, 1, -1, 1, 100);
  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();

  glBegin(GL_QUADS);
  glTexCoord2f(0, 1);
  glVertex3f(-1, -1, -1);
  glTexCoord2f(0, 0);
  glVertex3f(-1, 1, -1);
  glTexCoord2f(1, 0);
  glVertex3f(1, 1, -1);
  glTexCoord2f(1, 1);
  glVertex3f(1, -1, -1);
  glEnd();
}

void close() {
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  SDL_Quit();
}

int main() {
  //<editor-fold> BOILERPLATE *******************************************
  Camera testCamera = Camera();

  Sphere testSphere = Sphere(nullptr, 2, Vec_3t(0, 0, -5));

  std::vector<Ray> rays = testCamera.makePrimaryRays();

  unsigned char *buffer = new unsigned char[600 * 4 * 800];
  Vec_3t testVect;
  for (int i = 0; i < 600 * 800; i++) {
    if (testSphere.intersects(rays.at(i), testVect)) {
      buffer[i * 4] = 255;
      buffer[i * 4 + 1] = 255;
      buffer[i * 4 + 2] = 0;
      buffer[i * 4 + 3] = 1;
    } else {
      buffer[i * 4] = 0;
      buffer[i * 4 + 1] = 0;
      buffer[i * 4 + 2] = 0;
      buffer[i * 4 + 3] = 1;
    }
  }
  /*
  for (int i = 0; i < 600; i++) {
    for (int j = 0; j < 800; j++) {
      buffer[i][j] = testSphere.intersects(rays.at(j + i * 600), testVect);
      if (buffer[i][j]) {
        std::cout << "Intersect: " << testVect.toString() << std::endl;
      }
    }
  }
  */
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL cannot init with error " << SDL_GetError() << std::endl;
    return -1;
  }

  // set opengl version to use in this program
  SetOpenGLVersion();

  // create window
  gWindow = SDL_CreateWindow(
      "Opengl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
      SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (gWindow == NULL) {
    std::cout << "Cannot create window with error " << SDL_GetError()
              << std::endl;
    return -1;
  }

  // create opengl context
  gGlContext = SDL_GL_CreateContext(gWindow);
  if (gGlContext == NULL) {
    std::cout << "Cannot create OpenGL context with error " << SDL_GetError()
              << std::endl;
    return -1;
  }

  // initialize opengl
  Display_InitGL();
  // set camera
  Display_SetViewport(SCREEN_WIDTH, SCREEN_HEIGHT);
  bool quit = false;
  SDL_Event sdlEvent;

  // clear bg color and depth buffer
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // render stuff here
  Display_Render(buffer);
  delete[] buffer;

  // swap window inorder to update opengl
  // SDL_GL_SwapWindow(gWindow);

  // clear resource
  SDL_Delay(10000);

  close();

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
  //</editor-fold>

  //<editor-fold> DEFINE GEOMETRY **********************************************

  //</editor-fold>

  //<editor-fold> CAST RAYS ****************************************************

  //</editor-fold>

  //<editor-fold> RENDER ****************************************************
  //</editor-fold>

  /*
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
      return 1;
    }

    SDL_Window *win =
        SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
      std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
      SDL_Quit();
      return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(
        win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
      SDL_DestroyWindow(win);
      std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
      SDL_Quit();
      return 1;
    }
    SDL_Delay(10000);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    */
}
