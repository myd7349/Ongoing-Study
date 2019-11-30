#include <stdio.h>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit
// magic.
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"

int main() {
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW.\n");
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);                // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE,
                 GLFW_OPENGL_CORE_PROFILE);  // We don't want the old OpenGL

  GLFWwindow *window = glfwCreateWindow(
      1024, 768, "OpenGL Tutorials - 02. The First Triangle", NULL, NULL);
  if (window == NULL) {
    fprintf(stderr, "Failed to create GLFW window.\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  glewExperimental = true;  // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW.\n");
    glfwTerminate();
    return -1;
  }

  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  GLuint vertexArrayId;
  glGenVertexArrays(1, &vertexArrayId);
  glBindVertexArray(vertexArrayId);

  const GLfloat vertexBufferData[] = {
      -1.0f, -1.0f, 0.0f,  //
      1.0f,  -1.0f, 0.0f,  //
      0.0f,  1.0f,  0.0f,
  };

  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData,
               GL_STATIC_DRAW);

  GLuint program = LoadShaders("SimpleVertexShader.vertexshader",
                               "SimpleFragmentShader.fragmentshader");

  do {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

  glDeleteBuffers(1, &vertexBuffer);
  glDeleteProgram(program);
  glDeleteVertexArrays(1, &vertexArrayId);

  glfwTerminate();

  return 0;
}

// References:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
// https://stackoverflow.com/questions/40372055/cannot-open-source-file-gl-glew-h
// https://github.com/opengl-tutorials/ogl
