#include <breakout_engine.hpp>

int main(int argc, char const *argv[])
{
    glm::mat4 test_matrix;
    transform(test_matrix, 640, 480);
    std::cout << glm::to_string(test_matrix) << std::endl;
    return 0;
}
