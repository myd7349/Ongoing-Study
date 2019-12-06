#include <iostream>

#include <symengine/expression.h>

int main() {
  using SymEngine::Expression;

  Expression x("x");
  auto ex = pow(x + sqrt(Expression(2)), 10);
  std::cout << ex << std::endl;
  std::cout << expand(ex) << std::endl;

  return 0;
}

// References:
// https://notebooks.gesis.org/binder/jupyter/user/symengine-symengine-8fylat23/notebooks/notebooks/symengine.ipynb
