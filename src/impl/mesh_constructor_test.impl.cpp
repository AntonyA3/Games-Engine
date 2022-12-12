#include <breakout_engine.hpp>
#include <test_abstractions.hpp>
int main(int argc, char const *argv[])
{
    BasicSDLOpenGLTest test_dependancy;
    test_dependancy.initialise();
    Mesh test_mesh = Mesh();
    std::cout << "vertex_buffer_id: " << test_mesh.vertex_buffer << "\n";
    std::cout << "index_buffer_id: " << test_mesh.index_buffer << "\n";
    test_dependancy.cleanup();
    return 0;
}
