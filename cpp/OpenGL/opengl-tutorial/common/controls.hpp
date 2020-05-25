#pragma once

#include <glm/glm.hpp>

typedef struct GLFWwindow GLFWwindow;

void computeMatricesFromInputs(GLFWwindow *window);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
