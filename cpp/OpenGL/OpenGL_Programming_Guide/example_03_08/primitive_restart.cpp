#include "vapp.h"
#include "vmath.h"
#include "vutils.h"
#include "LoadShaders.h"

BEGIN_APP_DECLARATION(PrimitiveRestartExample)
virtual void Initialize(const char *title);
virtual void Display(bool autoRedraw);
virtual void Finalize();
virtual void Resize(int width, int height);

float aspect;
GLuint program;
GLuint ebo[1];
GLuint vao[1];
GLuint vbo[1];
GLint renderModelMatrixLocation;
GLint renderProjectionMatrixLocation;
END_APP_DECLARATION()

DEFINE_APP(PrimitiveRestartExample, "Primitive Restart Example")

void PrimitiveRestartExample::Initialize(const char *title) {
  base::Initialize();

  ShaderInfo shaderInfos[] = {{GL_VERTEX_SHADER, "primitive_restart.vs.glsl"},
                              {GL_FRAGMENT_SHADER, "primitive_restart.fs.glsl"},
                              {GL_NONE, NULL}};

  program = LoadShaders(shaderInfos);
  glUseProgram(program);

  renderModelMatrixLocation = glGetUniformLocation(program, "model_matrix");
  renderProjectionMatrixLocation =
      glGetUniformLocation(program, "projection_matrix");

  // 8 corners of a cube, side length 2, centered on the origin
  const GLfloat cubePositions[] = {
      -1.0f, -1.0f, -1.0f, 1.0f,  //
      -1.0f, -1.0f, 1.0f,  1.0f,  //
      -1.0f, 1.0f,  -1.0f, 1.0f,  //
      -1.0f, 1.0f,  1.0f,  1.0f,  //
      1.0f,  -1.0f, -1.0f, 1.0f,  //
      1.0f,  -1.0f, 1.0f,  1.0f,  //
      1.0f,  1.0f,  -1.0f, 1.0f,  //
      1.0f,  1.0f,  1.0f,  1.0f   //
  };

  const GLfloat cubeColors[] = {
      1.0f, 1.0f, 1.0f, 1.0f,  //
      1.0f, 1.0f, 0.0f, 1.0f,  //
      1.0f, 0.0f, 1.0f, 1.0f,  //
      1.0f, 0.0f, 0.0f, 1.0f,  //
      0.0f, 1.0f, 1.0f, 1.0f,  //
      0.0f, 1.0f, 0.0f, 1.0f,  //
      0.0f, 0.0f, 1.0f, 1.0f,  //
      0.5f, 0.5f, 0.5f, 1.0f   //
  };

  // Indices for the triangle strips
  const GLushort cubeIndices[] = {
      0,      1, 2, 3, 6, 7, 4, 5,  // First strip
      0xFFFF,                       // <<-- This is the restart index
      2,      6, 0, 4, 1, 5, 3, 7   // Second strip
  };

  glGenBuffers(1, ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices,
               GL_STATIC_DRAW);

  glGenVertexArrays(1, vao);
  glBindVertexArray(vao[0]);

  glGenBuffers(1, vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubePositions) + sizeof(cubeColors),
               NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cubePositions), cubePositions);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(cubePositions), sizeof(cubeColors),
                  cubeColors);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,
                        (const GLvoid *)sizeof(cubePositions));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void PrimitiveRestartExample::Display(bool autoRedraw) {
  float t = float(app_time() & 0x1FFF) / 0x1FFF;
  static float q = 0.0f;
  static const vmath::vec3 X(1.0f, 0.0f, 0.0f);
  static const vmath::vec3 Y(0.0f, 1.0f, 0.0f);
  static const vmath::vec3 Z(0.0f, 0.0f, 1.0f);

  // Setup
  glEnable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Activate simple shading program
  glUseProgram(program);

  // Set up the model and projection matrix
  vmath::mat4 modelMatrix(vmath::translate(0.0f, 0.0f, -5.0f) *
                          vmath::rotate(t * 360.0f, Y) *
                          vmath::rotate(t * 720.0f, Z));
  vmath::mat4 projectionMatrix(
      vmath::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 500.0f));

  glUniformMatrix4fv(renderModelMatrixLocation, 1, GL_FALSE, modelMatrix);
  glUniformMatrix4fv(renderProjectionMatrixLocation, 1, GL_FALSE,
                     projectionMatrix);

  // Set up for a glDrawElements call
  glBindVertexArray(vao[0]);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);

#ifdef USE_PRIMITIVE_RESTART
  // When primitive restart is on, we can call one draw command
  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(0xFFFF);
  glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, NULL);
#else
  // Without primitive restart, we need to call two draw commands
  glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, NULL);
  glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT,
                 (const GLvoid *)(9 * sizeof(GLshort)));
#endif

  base::Display(autoRedraw);
}

void PrimitiveRestartExample::Finalize() {
  glUseProgram(0);
  glDeleteProgram(program);
  glDeleteVertexArrays(1, vao);
  glDeleteBuffers(1, vbo);
}

void PrimitiveRestartExample::Resize(int width, int height) {
  glViewport(0, 0, width, height);
  aspect = float(height) / width;
}

// References:
// OpenGL Programming Guide, 9th Ed.
// https://github.com/openglredbook/examples/blob/master/src/03-primitiverestart/03-primitiverestart.cpp
