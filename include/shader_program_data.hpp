#ifndef GAMES_ENGINE_SHADER_PROGRAM_DATA_HPP
#define GAMES_ENGINE_SHADER_PROGRAM_DATA_HPP
#include <GL/glew.h>
#include <vector>
#include <vertex_attribute_data.hpp>
#include <string>
struct ShaderProgramData
{
    std::string vertex_file;
    std::string fragment_file;
    std::vector<VertexAttributeData> vertex_attributes;
};
#endif