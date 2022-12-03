#include <catch_amalgamated.hpp>

#define GLEW_STATIC
#include <GL/glew.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <glutils.hpp>
#include <complete_window.hpp>
#include <complete_window_data.hpp>


class testRunListener : public Catch::EventListenerBase {
public:
    using Catch::EventListenerBase::EventListenerBase;

    void testRunStarting(Catch::TestRunInfo const&) override {
        CompleteWindowData complete_window_data = {
            {
                SDL_INIT_VIDEO, 
                std::string("Breakout Game"),
                640,
                480,
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                true,
                true,
                SDL_FALSE
            },
            {
                3, 
                3
            }
        };
        CompleteWindow complete_window;
        complete_window.create(complete_window_data);
    }
};

CATCH_REGISTER_LISTENER(testRunListener)

TEST_CASE("Expect The Shader  to be correct", "[Shader]"){
    int status;
    GLuint shader = GLutils().makeShader("data\\shaders\\circle_position_color_texcoord.frag", GL_VERTEX_SHADER);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    REQUIRE(status == GL_TRUE);
    glDeleteShader(shader);
}

TEST_CASE("Expect The Program to be correct", "[Shader]"){
    int status;
    GLuint program = GLutils().makeProgram("data\\shaders\\circle_position_color_texcoord.vert", "data\\shaders\\circle_position_color_texcoord.frag");
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    REQUIRE(status == GL_TRUE);
    glDeleteProgram(program);
}
