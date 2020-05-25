#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit
// magic.
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "controls.hpp"
#include "shader.hpp"
#include "texture.hpp"

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
      Width, Height, "OpenGL Tutorials - 05. Textured Cube", NULL, NULL);
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

#ifdef BMP_TEXTURE
  GLuint texture = loadBMP_custom("uvtemplate.bmp");
#else
  GLuint texture = loadDDSEx("uvtemplate.dds");
#endif

  if (texture == 0) {
    fprintf(stderr, "Failed to load texture.\n");
    glfwTerminate();
    return -1;
  }

  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // Set the mouse at the center of the screen
  glfwPollEvents();
  glfwSetCursorPos(window, Width / 2.0, Height / 2.0);

  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // Cull triangles which normal is not towards the camera
  glEnable(GL_CULL_FACE);

  GLuint vertexArrayId;
  glGenVertexArrays(1, &vertexArrayId);
  glBindVertexArray(vertexArrayId);

  GLuint program = LoadShaders("TransformVertexShader.vertexshader",
                               "TextureFragmentShader.fragmentshader");

  // Get a handle for our "myTextureSampler" uniform
  GLuint textureID = glGetUniformLocation(program, "myTextureSampler");

  // Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive
  // vertices give a triangle. A cube has 6 faces with 2 triangles each, so this
  // makes 6*2=12 triangles, and 12*3 vertices
  const GLfloat vertexBufferData[] = {
      -1.0f, -1.0f, -1.0f,  //
      -1.0f, -1.0f, 1.0f,   //
      -1.0f, 1.0f,  1.0f,   //
      1.0f,  1.0f,  -1.0f,  //
      -1.0f, -1.0f, -1.0f,  //
      -1.0f, 1.0f,  -1.0f,  //
      1.0f,  -1.0f, 1.0f,   //
      -1.0f, -1.0f, -1.0f,  //
      1.0f,  -1.0f, -1.0f,  //
      1.0f,  1.0f,  -1.0f,  //
      1.0f,  -1.0f, -1.0f,  //
      -1.0f, -1.0f, -1.0f,  //
      -1.0f, -1.0f, -1.0f,  //
      -1.0f, 1.0f,  1.0f,   //
      -1.0f, 1.0f,  -1.0f,  //
      1.0f,  -1.0f, 1.0f,   //
      -1.0f, -1.0f, 1.0f,   //
      -1.0f, -1.0f, -1.0f,  //
      -1.0f, 1.0f,  1.0f,   //
      -1.0f, -1.0f, 1.0f,   //
      1.0f,  -1.0f, 1.0f,   //
      1.0f,  1.0f,  1.0f,   //
      1.0f,  -1.0f, -1.0f,  //
      1.0f,  1.0f,  -1.0f,  //
      1.0f,  -1.0f, -1.0f,  //
      1.0f,  1.0f,  1.0f,   //
      1.0f,  -1.0f, 1.0f,   //
      1.0f,  1.0f,  1.0f,   //
      1.0f,  1.0f,  -1.0f,  //
      -1.0f, 1.0f,  -1.0f,  //
      1.0f,  1.0f,  1.0f,   //
      -1.0f, 1.0f,  -1.0f,  //
      -1.0f, 1.0f,  1.0f,   //
      1.0f,  1.0f,  1.0f,   //
      -1.0f, 1.0f,  1.0f,   //
      1.0f,  -1.0f, 1.0f    //
  };

  // Two UV coordinatesfor each vertex. They were created with Blender.
  // (I copied these lines from
  // https://github.com/opengl-tutorials/ogl/blob/master/tutorial05_textured_cube/tutorial05.cpp)
  const GLfloat uvBufferData[] = {
      0.000059f, 1.0f - 0.000004f,  //
      0.000103f, 1.0f - 0.336048f,  //
      0.335973f, 1.0f - 0.335903f,  //
      1.000023f, 1.0f - 0.000013f,  //
      0.667979f, 1.0f - 0.335851f,  //
      0.999958f, 1.0f - 0.336064f,  //
      0.667979f, 1.0f - 0.335851f,  //
      0.336024f, 1.0f - 0.671877f,  //
      0.667969f, 1.0f - 0.671889f,  //
      1.000023f, 1.0f - 0.000013f,  //
      0.668104f, 1.0f - 0.000013f,  //
      0.667979f, 1.0f - 0.335851f,  //
      0.000059f, 1.0f - 0.000004f,  //
      0.335973f, 1.0f - 0.335903f,  //
      0.336098f, 1.0f - 0.000071f,  //
      0.667979f, 1.0f - 0.335851f,  //
      0.335973f, 1.0f - 0.335903f,  //
      0.336024f, 1.0f - 0.671877f,  //
      1.000004f, 1.0f - 0.671847f,  //
      0.999958f, 1.0f - 0.336064f,  //
      0.667979f, 1.0f - 0.335851f,  //
      0.668104f, 1.0f - 0.000013f,  //
      0.335973f, 1.0f - 0.335903f,  //
      0.667979f, 1.0f - 0.335851f,  //
      0.335973f, 1.0f - 0.335903f,  //
      0.668104f, 1.0f - 0.000013f,  //
      0.336098f, 1.0f - 0.000071f,  //
      0.000103f, 1.0f - 0.336048f,  //
      0.000004f, 1.0f - 0.671870f,  //
      0.336024f, 1.0f - 0.671877f,  //
      0.000103f, 1.0f - 0.336048f,  //
      0.336024f, 1.0f - 0.671877f,  //
      0.335973f, 1.0f - 0.335903f,  //
      0.667969f, 1.0f - 0.671889f,  //
      1.000004f, 1.0f - 0.671847f,  //
      0.667979f, 1.0f - 0.335851f   //
  };

  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData,
               GL_STATIC_DRAW);

  GLuint uvBuffer;
  glGenBuffers(1, &uvBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(uvBufferData), uvBufferData,
               GL_STATIC_DRAW);

  // Get a handle for our "MVP" uniform
  GLuint matrixId = glGetUniformLocation(program, "MVP");

  do {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(program);

    // Compute the MVP matrix from keyboard and mouse input
    computeMatricesFromInputs(window);
    glm::mat4 projectionMatrix = getProjectionMatrix();
    glm::mat4 viewMatrix = getViewMatrix();
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 modelViewProjectionMatrix =
        projectionMatrix * viewMatrix * modelMatrix;

    // Send our transformation to the currently bound shader, in the "MVP"
    // uniform. This is done in the main loop since each model will have a
    // different MVP matrix (At least for the M part);
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &modelViewProjectionMatrix[0][0]);

    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(texture, 0);

    // 1st attribute buffer: vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    // 2nd attribute buffer: UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glVertexAttribPointer(1,
                          2,  // U+V => 2
                          GL_FLOAT, GL_FALSE, 0, (void *)0);

    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glfwSwapBuffers(window);
    glfwPollEvents();
  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(1, &uvBuffer);
  glUseProgram(0);
  glDeleteProgram(program);
  glDeleteTextures(1, &texture);
  glDeleteVertexArrays(1, &vertexArrayId);

  glfwTerminate();

  return 0;
}

// References:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/
// https://github.com/opengl-tutorials/ogl
