#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

void TranslateVectorInTheXDirection() {
  // According to g-truc/glm#809:
  // glm::mat4() initialization is deprecated.
  // So glm::mat4() won't give you an identity matrix since GLM 0.9.9.
  glm::mat4 identityMatrix(1.0);
  glm::mat4 myMatrix =
      glm::translate(identityMatrix, glm::vec3(10.0f, 0.0f, 0.0f));
  glm::vec4 myVector(10.0f, 10.0f, 10.0f, 1.0f);
  glm::vec4 transformedVector = myMatrix * myVector;

  std::cout << "Identity matrix: " << glm::to_string(identityMatrix)
            << std::endl;
  std::cout << "Translation matrix: " << glm::to_string(myMatrix) << std::endl;
  std::cout << "Original vector: " << glm::to_string(myVector) << std::endl;
  std::cout << "Transformed vector: " << glm::to_string(transformedVector)
            << std::endl;
}

void ScalingMatrixTest() {
  glm::mat4 scalingMatrix = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f));

  std::cout << "Scaling matrix: " << glm::to_string(scalingMatrix) << std::endl;
}

int main() {
  TranslateVectorInTheXDirection();
  ScalingMatrixTest();

  return 0;
}

// References:
// [0] http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
// [1] https://github.com/opengl-tutorials/ogl
// [2] https://stackoverflow.com/questions/11515469/how-do-i-print-vector-values-of-type-glmvec3-that-have-been-passed-by-referenc
// [3] http://www.c-jump.com/bcc/common/Talk3/Math/GLM/GLM.html
// [4] https://github.com/g-truc/glm/issues/809
