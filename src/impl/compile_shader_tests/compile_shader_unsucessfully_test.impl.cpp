#include <breakout_engine.hpp>

int main(int argc, char const *argv[])
{
    BasicSDLOpenGLTest test_dependancies;
    
    test_dependancies.initialise();
    GLuint shader_content = makeShader(GL_VERTEX_SHADER, "random text");
    displayShaderCompileStatus(shader_content);
    test_dependancies.cleanup();
    return 0;
}
