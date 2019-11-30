#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
      Width, Height, "OpenGL Tutorials - 04. Colored Cube", NULL, NULL);
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

  // A cube has six square faces. Since OpenGL only knowns about triangles, we
  // will have to draw 12 triangles: two for each face.
  const GLfloat vertexBufferData[] = {
      -1.0f, -1.0f, -1.0f,  // triangle 1 - begin
      -1.0f, -1.0f, 1.0f,   //
      -1.0f, 1.0f,  1.0f,   // triangle 1 - end
      1.0f,  1.0f,  -1.0f,  // triangle 2 - begin
      -1.0f, -1.0f, -1.0f,  //
      -1.0f, 1.0f,  -1.0f,  // triangle 2 - end
      1.0f,  -1.0f, 1.0f,   // triangle 3
      -1.0f, -1.0f, -1.0f,  //
      1.0f,  -1.0f, -1.0f,  //
      1.0f,  1.0f,  -1.0f,  // triangle 4
      1.0f,  -1.0f, -1.0f,  //
      -1.0f, -1.0f, -1.0f,  //
      -1.0f, -1.0f, -1.0f,  // 5
      -1.0f, 1.0f,  1.0f,   //
      -1.0f, 1.0f,  -1.0f,  //
      1.0f,  -1.0f, 1.0f,   // 6
      -1.0f, -1.0f, 1.0f,   //
      -1.0f, -1.0f, -1.0f,  //
      -1.0f, 1.0f,  1.0f,   // 7
      -1.0f, -1.0f, 1.0f,   //
      1.0f,  -1.0f, 1.0f,   //
      1.0f,  1.0f,  1.0f,   // 8
      1.0f,  -1.0f, -1.0f,  //
      1.0f,  1.0f,  -1.0f,  //
      1.0f,  -1.0f, -1.0f,  // 9
      1.0f,  1.0f,  1.0f,   //
      1.0f,  -1.0f, 1.0f,   //
      1.0f,  1.0f,  1.0f,   // 10
      1.0f,  1.0f,  -1.0f,  //
      -1.0f, 1.0f,  -1.0f,  //
      1.0f,  1.0f,  1.0f,   // 11
      -1.0f, 1.0f,  -1.0f,  //
      -1.0f, 1.0f,  1.0f,   //
      1.0f,  1.0f,  1.0f,   // 12
      -1.0f, 1.0f,  1.0f,   //
      1.0f,  -1.0f, 1.0f    //
  };

  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData,
               GL_STATIC_DRAW);

#if defined(CUBE_RANDOM_COLORS) || defined(CUBE_RANDOM_COLORS_EACH_FRAME)
  GLfloat colorBufferData[12 * 3 * 3];

  srand((unsigned)time(NULL));
#endif

#if defined(CUBE_RANDOM_COLORS)
  for (int v = 0; v < 12 * 3; v++) {
    colorBufferData[3 * v + 0] = (float)rand() / RAND_MAX;
    colorBufferData[3 * v + 1] = (float)rand() / RAND_MAX;
    colorBufferData[3 * v + 2] = (float)rand() / RAND_MAX;
  }
#elif defined(CUBE_RANDOM_COLORS_EACH_FRAME)
  int colors[12 * 3 * 3];
  for (int v = 0; v < 12 * 3; v++) {
    colors[3 * v + 0] = rand() % 256;
    colors[3 * v + 1] = rand() % 256;
    colors[3 * v + 2] = rand() % 256;
  }
  int count = 0;
#else
  const GLfloat colorBufferData[] = {
      0.583f, 0.771f, 0.014f,  //
      0.609f, 0.115f, 0.436f,  //
      0.327f, 0.483f, 0.844f,  //
      0.822f, 0.569f, 0.201f,  //
      0.435f, 0.602f, 0.223f,  //
      0.310f, 0.747f, 0.185f,  //
      0.597f, 0.770f, 0.761f,  //
      0.559f, 0.436f, 0.730f,  //
      0.359f, 0.583f, 0.152f,  //
      0.483f, 0.596f, 0.789f,  //
      0.559f, 0.861f, 0.639f,  //
      0.195f, 0.548f, 0.859f,  //
      0.014f, 0.184f, 0.576f,  //
      0.771f, 0.328f, 0.970f,  //
      0.406f, 0.615f, 0.116f,  //
      0.676f, 0.977f, 0.133f,  //
      0.971f, 0.572f, 0.833f,  //
      0.140f, 0.616f, 0.489f,  //
      0.997f, 0.513f, 0.064f,  //
      0.945f, 0.719f, 0.592f,  //
      0.543f, 0.021f, 0.978f,  //
      0.279f, 0.317f, 0.505f,  //
      0.167f, 0.620f, 0.077f,  //
      0.347f, 0.857f, 0.137f,  //
      0.055f, 0.953f, 0.042f,  //
      0.714f, 0.505f, 0.345f,  //
      0.783f, 0.290f, 0.734f,  //
      0.722f, 0.645f, 0.174f,  //
      0.302f, 0.455f, 0.848f,  //
      0.225f, 0.587f, 0.040f,  //
      0.517f, 0.713f, 0.338f,  //
      0.053f, 0.959f, 0.120f,  //
      0.393f, 0.621f, 0.362f,  //
      0.673f, 0.211f, 0.457f,  //
      0.820f, 0.883f, 0.371f,  //
      0.982f, 0.099f, 0.879f   //
  };
#endif

  GLuint colorBuffer;
  glGenBuffers(1, &colorBuffer);
#ifndef CUBE_RANDOM_COLORS_EACH_FRAME
  glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData,
               GL_STATIC_DRAW);
#endif

  GLuint program = LoadShaders("SimpleVertexShader.vertexshader",
                               "SimpleFragmentShader.fragmentshader");

  // Projection matrix
  glm::mat4 projectionMatrix = glm::perspective(
      glm::radians(45.0f), static_cast<float>(Width) / Height, 0.1f, 100.0f);

  // Camera matrix
  glm::mat4 viewMatrix = glm::lookAt(
      glm::vec3(4.0f, 3.0f, -3.0f),  // Camera is at (4, 3, 3), in world space
      glm::vec3(0.0f, 0.0f, 0.0f),   // and looks at the origin
      glm::vec3(0.0f, 1.0f,
                0.0f)  // Head is up (set to (0, -1, 0) to look upside-down)
  );

  // Model matrix: an identity matrix (model will be at the origin)
  glm::mat4 modelMatrix = glm::mat4(1.0f);

  glm::mat4 modelViewProjectionMatrix =
      projectionMatrix * viewMatrix * modelMatrix;

  // Get a handle for our "MVP" uniform
  GLuint matrixId = glGetUniformLocation(program, "MVP");

#ifdef CUBE_ENABLE_DEPTH_TEST
  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);
#endif

  do {
    glClear(GL_COLOR_BUFFER_BIT
#ifdef CUBE_ENABLE_DEPTH_TEST
            | GL_DEPTH_BUFFER_BIT
#endif
    );

    glUseProgram(program);

    // Send our transformation to the currently bound shader, in the "MVP"
    // uniform. This is done in the main loop since each model will have a
    // different MVP matrix (At least for the M part);
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &modelViewProjectionMatrix[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);

#ifdef CUBE_RANDOM_COLORS_EACH_FRAME
    if (count++ == 20) {
      for (int v = 0; v < 12 * 3; v++) {
        colors[3 * v + 0] = (colors[3 * v + 0] + 1) % 256;
        colors[3 * v + 1] = (colors[3 * v + 1] + 1) % 256;
        colors[3 * v + 2] = (colors[3 * v + 2] + 1) % 256;

        colorBufferData[3 * v + 0] = colors[3 * v + 0] / 256.0f;
        colorBufferData[3 * v + 1] = colors[3 * v + 1] / 256.0f;
        colorBufferData[3 * v + 2] = colors[3 * v + 2] / 256.0f;
      }

      glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData,
                   GL_STATIC_DRAW);

      count = 0;
    }
#endif

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glfwSwapBuffers(window);
    glfwPollEvents();
  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(1, &colorBuffer);
  glDeleteProgram(program);
  glDeleteVertexArrays(1, &vertexArrayId);

  glfwTerminate();

  return 0;
}

// References:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/
// https://github.com/opengl-tutorials/ogl
// https://stackoverflow.com/questions/3430789/where-points-opengl-z-axis
