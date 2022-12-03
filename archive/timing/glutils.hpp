#ifndef GAMES_ENGINE_GLUTILS
#define GAMES_ENGINE_GLUTILS
#include <GL/glew.h>
#include <string>
#include <loader/file_reader.hpp>

#include <assert.h>

#define ENABLE_DEBUG_LOGGER
#include <macros/debug_logger.hpp>
struct GLutils
{
    GLuint makeProgram(std::string vertex_file, std::string fragment_file);
    GLuint makeShader(std::string shader_file, GLenum shader_type);
    GLuint makeProgramFromContent(const char *  vertex_content, const char * fragment_content);
    GLuint makeShaderFromContent(const char * shader_content, GLenum shader_type);
    GLuint attachShadersAndLinkProgram(GLuint& vertex_shader, GLuint& fragment_shader);
};
#endif

