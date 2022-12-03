#ifndef GAMES_ENGINE_MESH_DATA
#define GAMES_ENGINE_MESH_DATA
#include <glm/glm.hpp>
#include <vector>
#include <shapes/aa_rect.hpp>  // The rectangle that is used to add a rectangle
#include <rect_verticies.hpp>
#include <shapes/polygon.hpp>
/*
A class to create a opengl shader program and also get the details related tothe status of loading the shader
*/
struct MeshData
{
    std::vector<float> m_vertex_array; // It stores the vertex data for a mesh
    std::vector<unsigned int> m_index_array; //  It stores the index data for a mesh 
    unsigned int m_index_offset;

    
    // struct RectVerticies{
    //     glm::vec3 top_left;
    //     glm::vec3 top_right;
    //     glm::vec3 bottom_left;
    //     glm::vec3 bottom_right;
    //     void create(AARect& rect);
    // };   
    public:
    MeshData();
    void create();
    void pushRectOfColor(AARect& rectangle, glm::vec3 color);  // Push Rectangle with color
    void pushPolygonOfColor(Polygon& polygon, glm::vec3 color); //Push Polygon with color
    void pushRectOfColorAndAreaUnit(AARect rectangle, glm::vec3 color); // Push Rectangle with color and Unit Area
    void clear(); // Clears the vertex data of the batch and resets the index offset to 0
    void generateRectIndicies();
    void pushPosition(glm::vec3 position);
    void pushColor(glm::vec3 color);
    void pushTextureCoordinates(glm::vec2 coords);
    std::vector<float>& getVertexData();
    std::vector<unsigned int>& getIndexData();
    
};
#endif