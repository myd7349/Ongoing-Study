#include <stdio.h>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit
// magic.
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
      1024, 768, "OpenGL Tutorials - 01. First Window", NULL, NULL);
  if (window == NULL) {
    fprintf(stderr, "Failed to create GLFW window.\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  glewExperimental = true;  // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW.\n");
    return -1;
  }

  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  do {
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

  glfwTerminate();

  return 0;
}

// References:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/
// https://stackoverflow.com/questions/40372055/cannot-open-source-file-gl-glew-h
// https://github.com/opengl-tutorials/ogl
