#include <breakout_engine.hpp>
#include <test_abstractions.hpp>
int main(int argc, char const *argv[])
{
    BasicSDLOpenGLTest test_dependancy;
    test_dependancy.initialise();
    Mesh test_mesh = Mesh();
    std::cout << toString(test_mesh) << "\n";
    test_dependancy.cleanup();
    return 0;
}
