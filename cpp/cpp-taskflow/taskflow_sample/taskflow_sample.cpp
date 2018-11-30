#include <taskflow/taskflow.hpp>  // Cpp-Taskflow is header-only

int main() {

    tf::Taskflow tf;

    auto[A, B, C, D] = tf.silent_emplace(
        []() { std::cout << "TaskA\n"; },               //  task dependency graph
        []() { std::cout << "TaskB\n"; },               // 
        []() { std::cout << "TaskC\n"; },               //          +---+          
        []() { std::cout << "TaskD\n"; }                //    +---->| B |-----+   
    );                                                 //    |     +---+     |
                                                       //  +---+           +-v-+ 
    A.precede(B);  // A runs before B                  //  | A |           | D | 
    A.precede(C);  // A runs before C                  //  +---+           +-^-+ 
    B.precede(D);  // B runs before D                  //    |     +---+     |    
    C.precede(D);  // C runs before D                  //    +---->| C |-----+    
                                                       //          +---+          
    tf.wait_for_all();  // block until finish

    return 0;
}