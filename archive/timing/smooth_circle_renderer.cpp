#include <smooth_circle_renderer.hpp>

void SmoothCircleRenderer::addQuad(AARect& rect, glm::vec3 color){
    refMeshData().pushRectOfColorAndAreaUnit(rect, color);
}