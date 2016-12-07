#include "display.hpp"
#include <iostream>

Display::Display(int width, int height, const std::string &title) {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_OPENGL);
  m_glContext = SDL_GL_CreateContext(m_window);

  m_isClosed = false;

  glEnable(GL_TEXTURE_2D);
}

Display::~Display() {
  SDL_GL_DeleteContext(m_glContext);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

bool Display::IsClosed() { return m_isClosed; }

void Display::Update() {
  SDL_GL_SwapWindow(m_window);
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      m_isClosed = true;
    }
  }
}

void Display::Clear(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);
  glClear(GL_COLOR_BUFFER_BIT);
}
void Display::DrawTexture(unsigned char *buffer, int width, int height) {
  glBindTexture(GL_TEXTURE_2D, 13);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, buffer);

  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex3f(-1.0, -1.0, 0.0);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(1.0, -1.0, 0.0);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(1.0, 1.0, 0.0);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-1.0, 1.0, 0.0);
  glEnd();
}
