#include <breakout_engine.hpp>
#include <test_abstractions.hpp>

int main(int argc, char const *argv[])
{
    BasicSDLOpenGLTest test_dependancies;
    
    test_dependancies.initialise();
    GLuint shader_content = 0;
    shader_content = makeShader(GL_VERTEX_SHADER, std::string("data/shaders/polygon_position_color.vert"));

    assert(shader_content != 0);
    std::cout << "shader: " << shader_content << std::endl;

    test_dependancies.cleanup();
    return 0;
}
