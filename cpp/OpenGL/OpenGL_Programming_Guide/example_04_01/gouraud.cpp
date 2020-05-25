#include "vapp.h"
#include "LoadShaders.h"

BEGIN_APP_DECLARATION(GouraudExample)
virtual void Initialize(const char *title);
virtual void Display(bool autoRedraw);
virtual void OnKey(int key, int scanCode, int action, int mods);
virtual void Finalize();

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0, vColor = 1 };

static const GLuint NumVertices = 6;

GLuint program_;
GLenum mode_ = GL_FILL;
GLuint VAOs_[NumVAOs];
GLuint Buffers_[NumBuffers];
END_APP_DECLARATION()

DEFINE_APP(GouraudExample, "Gouraud Example")

void GouraudExample::Initialize(const char *title) {
  base::Initialize(title);

  glGenVertexArrays(NumVAOs, VAOs_);
  glBindVertexArray(VAOs_[Triangles]);

  struct VertexData {
    GLubyte color[4];
    GLfloat position[4];
  };

  VertexData vertices[NumVertices] = {
      {{255, 0, 0, 255}, {-0.90f, -0.90f}},  // Triangle 1
      {{0, 255, 0, 255}, {0.85f, -0.90f}},
      {{0, 0, 255, 255}, {-0.90f, 0.85f}},
      {{10, 10, 10, 255}, {0.90f, -0.85f}},  // Triangle 2
      {{100, 100, 100, 255}, {0.90f, 0.90f}},
      {{255, 255, 255, 255}, {-0.85f, 0.90f}}};

  glGenBuffers(NumBuffers, Buffers_);
  glBindBuffer(GL_ARRAY_BUFFER, Buffers_[ArrayBuffer]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  ShaderInfo shaders[] = {{GL_VERTEX_SHADER, "gouraud.vert"},
                          {GL_FRAGMENT_SHADER, "gouraud.frag"},
                          {GL_NONE, NULL}};

  program_ = LoadShaders(shaders);
  glUseProgram(program_);

  glVertexAttribPointer(vColor, 4, GL_UNSIGNED_BYTE, GL_TRUE,
                        sizeof(VertexData), BUFFER_OFFSET(0));
  glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData),
                        BUFFER_OFFSET(sizeof(vertices[0].color)));

  glEnableVertexAttribArray(vColor);
  glEnableVertexAttribArray(vPosition);
}

void GouraudExample::OnKey(int key, int scanCode, int action, int mods) {
  if (action == GLFW_PRESS) {
    switch (key) {
      case GLFW_KEY_M:
        mode_ = (mode_ == GL_FILL ? GL_LINE : GL_FILL);
        glPolygonMode(GL_FRONT_AND_BACK, mode_);
        return;
      default:
        break;
    }
  }

  base::OnKey(key, scanCode, action, mods);
}

void GouraudExample::Display(bool autoRedraw) {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glBindVertexArray(VAOs_[Triangles]);
  glDrawArrays(GL_TRIANGLES, 0, NumVertices);

  base::Display(autoRedraw);
}

void GouraudExample::Finalize() {
    glUseProgram(0);
    glDeleteProgram(program_);
    glDeleteVertexArrays(NumVAOs, VAOs_);
    glDeleteBuffers(NumBuffers, Buffers_);
}

// References:
// OpenGL Programming Guide, 9th Ed.
// https://github.com/openglredbook/examples/blob/master/src/04-gouraud/04-gouraud.cpp
