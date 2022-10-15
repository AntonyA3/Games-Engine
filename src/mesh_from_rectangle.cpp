#include <mesh_from_rectangle.hpp>

Mesh MeshFromRectangle::generate(AARect& rectangle){
    Mesh out_mesh;
    out_mesh.create();
    int float_count = 44;
    int index_count = 6;

    glm::vec2 top_left = rectangle.getTopLeft();
    glm::vec2 top_right = rectangle.getTopRight();

    glm::vec2 bottom_left = rectangle.getBottomLeft();
    glm::vec2 bottom_right = rectangle.getBottomRight();
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);


    float vertex_array[float_count] = {
        bottom_left.x, bottom_left.y, 0.0f, color.r, color.g, color.b,
        bottom_right.x, bottom_right.y, 0.0f, color.r, color.g, color.b,
        top_right.x, top_right.y, 0.0f, color.r, color.g, color.b,
        top_left.x, top_left.y, 0.0f, color.r, color.g, color.b
    };


    unsigned int index_array[index_count] = {
        0, 1, 2,
        0, 2, 3
    };

    mesh_generator.generate(out_mesh,vertex_array, float_count, index_array, index_count);
    out_mesh.m_matrix = glm::ortho(-1.0f, 1.0f, 1.0f, -1.0f);
    return out_mesh;
    
}