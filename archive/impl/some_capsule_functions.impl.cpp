#include <shapes/capsule.hpp>
#include <iostream>
int main(int argc, char const *argv[])
{
    Capsule capsule;
    capsule.create(glm::vec2(0.0f,0.0f), 5.0f, glm::vec2(0.0f,0.0f));

    std::cout << "Before Sweep" << std::endl;
    capsule.sweepUpdate(glm::vec2(5.0f, 0.0f));
    std::cout << capsule.toString() << std::endl;

    std::cout << "After Sweep" << std::endl;
    capsule.sweepUpdate(glm::vec2(5.0f, 0.0f));
    std::cout << capsule.toString() << std::endl;

    return 0;   
}
