#include <polygon_renderer.hpp>

void PolygonRenderer::addQuad(AARect &rect, glm::vec3 color){
    refMeshData().pushRectOfColor(rect, color);
}

void PolygonRenderer::addPolygon(Polygon& polygon, glm::vec3 color){
    refMeshData().pushPolygonOfColor(polygon, color);
}

