#ifndef GAMES_ENGINE_SMOOTH_CIRCLE_RENEDERER
#define GAMES_ENGINE_SMOOTH_CIRCLE_RENEDERER
#include <mesh_data.hpp>
#include <mesh.hpp>
#include <shader_program.hpp>
#include <sub_renderer.hpp>

class SmoothCircleRenderer : public SubRenderer
{   
    public:
    void addQuad(AARect& rect, glm::vec3 color);
};
#endif