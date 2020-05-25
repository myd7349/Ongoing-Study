#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "controls.hpp"

namespace {
glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;
}  // namespace

glm::mat4 getViewMatrix() { return viewMatrix; }

glm::mat4 getProjectionMatrix() { return projectionMatrix; }

namespace {
// Initial position: on +Z
glm::vec3 position = glm::vec3(0, 0, 5);
// Initial horizontal angle: toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle: none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f;  // 3 units/second
float mouseSpeed = 0.005f;
}  // namespace

void computeMatricesFromInputs(GLFWwindow *window) {
  // glfwGetTime() is called only once.
  static double lastTime = glfwGetTime();

  // Compute time difference between current and last frame
  double currentTime = glfwGetTime();
  float deltaTime = float(currentTime - lastTime);

  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);

  int width, height;
  glfwGetWindowSize(window, &width, &height);

  // Reset mouse position for next frame
  glfwSetCursorPos(window, width / 2.0, height / 2.0);

  // Compute new orientation
  horizontalAngle += mouseSpeed * float(width / 2.0 - xpos);
  verticalAngle += mouseSpeed * float(height / 2.0 - ypos);

  // Direction: Spherical coordinates to Cartesian coordinates conversion
  glm::vec3 direction(glm::cos(verticalAngle) * glm::sin(horizontalAngle),
                      glm::sin(verticalAngle),
                      glm::cos(verticalAngle) * glm::cos(horizontalAngle));

  // Right vector
  glm::vec3 right =
      glm::vec3(glm::sin(horizontalAngle - glm::pi<float>() / 2.0f), 0.0f,
                glm::cos(horizontalAngle - glm::pi<float>() / 2.0f));

  // Up vector
  glm::vec3 up = glm::cross(right, direction);

  // Move forward
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    position += direction * deltaTime * speed;
  }
  // Move backward
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    position -= direction * deltaTime * speed;
  }
  // Strafe right
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    position += right * deltaTime * speed;
  }
  // Strafe left
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    position -= right * deltaTime * speed;
  }

  float FoV = initialFoV;

  // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit
  // <-> 100 units
  projectionMatrix =
      glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
  // Camera matrix
  viewMatrix = glm::lookAt(
      position,  // Camera is here
      position +
          direction,  // and looks here : at the same position, plus "direction"
      up              // Head is up (set to 0,-1,0 to look upside-down)
  );

  // For the next frame, the "last time" will be "now"
  lastTime = currentTime;
}

// References:
// https://github.com/opengl-tutorials/ogl/blob/master/common/controls.cpp
