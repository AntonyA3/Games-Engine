#ifndef GAMES_ENGINE_MESH_DATA_CONVERTER
#define GAMES_ENGINE_MESH_DATA_CONVERTER
#include <glm/glm.hpp>
#include <vector>
#include <aa_rect.hpp> 
struct MeshDataConverter
{
    std::vector<float> m_vertex_array;
    std::vector<unsigned int> m_index_array;
    unsigned int m_index_offset;

    void create();
    void generate(AARect& rectangle);
    void generateRectWithColorAndUnitCoords(AARect rectangle);
    void clear();    
    struct RectVerticies{
        glm::vec3 top_left;
        glm::vec3 top_right;
        glm::vec3 bottom_left;
        glm::vec3 bottom_right;
        void create(AARect& rect);
    };
    private:
    void generateRectIndicies();
    void pushPosition(glm::vec3 position);
    void pushColor(glm::vec3 color);
    void pushTextureCoordinates(glm::vec2 coords);

    
};
#endif