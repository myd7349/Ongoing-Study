#include "vapp.h"
#include "vmath.h"
#include "vutils.h"
#include "LoadShaders.h"

BEGIN_APP_DECLARATION(DrawCommandExample)
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

DEFINE_APP(DrawCommandExample, "Drawing Commands Example")

void DrawCommandExample::Initialize(const char *title) {
  base::Initialize();

  ShaderInfo shaderInfos[] = {{GL_VERTEX_SHADER, "primitive_restart.vs.glsl"},
                              {GL_FRAGMENT_SHADER, "primitive_restart.fs.glsl"},
                              {GL_NONE, NULL}};

  program = LoadShaders(shaderInfos);
  glUseProgram(program);

  renderModelMatrixLocation = glGetUniformLocation(program, "model_matrix");
  renderProjectionMatrixLocation =
      glGetUniformLocation(program, "projection_matrix");

  const GLfloat vertexPositions[] = {
      -1.0f, -1.0f, 0.0f, 1.0f,  //
      1.0f,  -1.0f, 0.0f, 1.0f,  //
      -1.0f, 1.0f,  0.0f, 1.0f,  //
      -1.0f, -1.0f, 0.0f, 1.0f,
  };

  const GLfloat vertexColors[] = {
      1.0f, 1.0f, 1.0f, 1.0f,  //
      1.0f, 1.0f, 0.0f, 1.0f,  //
      1.0f, 0.0f, 1.0f, 1.0f,  //
      0.0f, 1.0f, 1.0f, 1.0f,
  };

  const GLshort vertexIndices[] = {0, 1, 2};

  glGenBuffers(1, ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices,
               GL_STATIC_DRAW);

  glGenVertexArrays(1, vao);
  glBindVertexArray(vao[0]);

  glGenBuffers(1, vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions) + sizeof(vertexColors),
               NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexPositions), vertexPositions);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexPositions),
                  sizeof(vertexColors), vertexColors);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,
                        (const GLvoid *)sizeof(vertexPositions));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
}

void DrawCommandExample::Display(bool autoRedraw) {
  float t = float(app_time() & 0x1FFF) / 0x1FFF;
  static float q = 0.0f;
  static const vmath::vec3 X(1.0f, 0.0f, 0.0f);
  static const vmath::vec3 Y(0.0f, 1.0f, 0.0f);
  static const vmath::vec3 Z(0.0f, 0.0f, 1.0f);
  static const vmath::vec4 black = vmath::vec4(0.0f, 0.0f, 0.0f, 0.0f);

  vmath::mat4 modelMatrix;

  // Setup
  glEnable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);

  glClearBufferfv(GL_COLOR, 0, black);

  // Activate simple shading program
  glUseProgram(program);

  // Set up the model and projection matrix
  vmath::mat4 projectionMatrix(
      vmath::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 500.0f));
  glUniformMatrix4fv(renderProjectionMatrixLocation, 1, GL_FALSE,
                     projectionMatrix);

  // Set up for a glDrawElements call
  glBindVertexArray(vao[0]);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);

  // Draw Arrays
  modelMatrix = vmath::translate(-3.0f, 0.0f, -5.0f);
  glUniformMatrix4fv(renderModelMatrixLocation, 1, GL_FALSE, modelMatrix);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  modelMatrix = vmath::translate(-1.0f, 0.0f, -5.0f);
  glUniformMatrix4fv(renderModelMatrixLocation, 1, GL_FALSE, modelMatrix);
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);

  modelMatrix = vmath::translate(1.0f, 0.0f, -5.0f);
  glUniformMatrix4fv(renderModelMatrixLocation, 1, GL_FALSE, modelMatrix);
  glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL, 1);

  modelMatrix = vmath::translate(3.0f, 0.0f, -5.0f);
  glUniformMatrix4fv(renderModelMatrixLocation, 1, GL_FALSE, modelMatrix);
  glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);

  base::Display(autoRedraw);
}

void DrawCommandExample::Finalize() {
  glUseProgram(0);
  glDeleteProgram(program);
  glDeleteVertexArrays(1, vao);
  glDeleteBuffers(1, vbo);
}

void DrawCommandExample::Resize(int width, int height) {
  glViewport(0, 0, width, height);
  aspect = float(height) / width;
}

// References:
// OpenGL Programming Guide, 9th Ed.
// https://github.com/openglredbook/examples/blob/master/src/03-drawcommands/03-drawcommands.cpp
