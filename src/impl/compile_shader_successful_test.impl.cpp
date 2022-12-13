#include <breakout_engine.hpp>
#include <test_abstractions.hpp>

int main(int argc, char const *argv[])
{
    BasicSDLOpenGLTest test_dependancies;
    
    test_dependancies.initialise();
    GLuint shader_content = makeShader(GL_VERTEX_SHADER, std::string("data/shaders/polygon_position_color.vert"));
    displayShaderCompileStatus(shader_content);
    test_dependancies.cleanup();
    return 0;
}
