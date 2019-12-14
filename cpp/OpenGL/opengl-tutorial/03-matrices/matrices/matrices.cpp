#include <stdio.h>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit
// magic.
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

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

  const int Width = 1024;
  const int Height = 768;
  GLFWwindow *window = glfwCreateWindow(
      Width, Height, "OpenGL Tutorials - 03. Matrices", NULL, NULL);
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

  // Projection matrix
  glm::mat4 projectionMatrix = glm::perspective(
      glm::radians(45.0f), static_cast<float>(Width) / Height, 0.1f, 100.0f);

  // Camera matrix
  glm::mat4 viewMatrix = glm::lookAt(
      glm::vec3(4.0f, 3.0f, 3.0f),  // Camera is at (4, 3, 3), in world space
      glm::vec3(0.0f, 0.0f, 0.0f),  // and looks at the origin
      glm::vec3(0.0f, 1.0f,
                0.0f)  // Head is up (set to (0, -1, 0) to look upside-down)
  );

  // Model matrix: an identity matrix (model will be at the origin)
  glm::mat4 modelMatrix = glm::mat4(1.0f);

  glm::mat4 modelViewProjectionMatrix =
      projectionMatrix * viewMatrix * modelMatrix;

  // Get a handle for our "MVP" uniform
  GLuint matrixId = glGetUniformLocation(program, "MVP");

  do {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);

    // Send our transformation to the currently bound shader, in the "MVP"
    // uniform. This is done in the main loop since each model will have a
    // different MVP matrix (At least for the M part);
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &modelViewProjectionMatrix[0][0]);

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
  glUseProgram(0);
  glDeleteProgram(program);
  glDeleteVertexArrays(1, &vertexArrayId);

  glfwTerminate();

  return 0;
}

// References:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
// https://github.com/opengl-tutorials/ogl
