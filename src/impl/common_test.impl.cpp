#include <breakout_engine.hpp>
#include <test_abstractions.hpp>

int main(int argc, char const *argv[])
{
    {
        Rect rect = Rect(glm::vec2(0.0f, 0.0f), glm::vec2(128.0f, 128.0f));
        assert(rect.topLeft() == glm::vec2(0.0f, 0.0f));
        assert(rect.topRight() == glm::vec2(128.0f, 0.0f));
        assert(rect.bottomLeft() == glm::vec2(0.0f, 128.0f));
        assert(rect.bottomRight() == glm::vec2(128.0f, 128.0f));
        std::cout << toString(rect) << std::endl;
    }

    
    {
        VertexIndexBatch test_vertex_index_batch = VertexIndexBatch();
        Rect test_rect = Rect(glm::vec2(0.0f, 0.0f), glm::vec2(128.0f, 128.0f));
        glm::vec3 test_color = glm::vec3(1.0f, 0.0f, 0.0f);
        size_t expected_verticies_size = 24;
        size_t expected_indicies_size = 6;
        addRect(test_vertex_index_batch, test_rect, test_color);
        // Verify the first rectangle has been added correctly

        assert(test_vertex_index_batch.indicies.size() == 6);
        assert(test_vertex_index_batch.verticies.size() == expected_verticies_size);
        assert(test_vertex_index_batch.index_offset == 4);
        {
            float values[expected_verticies_size] = {
                0.0f, 128.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                128.0f, 128.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                128.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            };
            bool values_match = true;
            for(size_t i = 0; i < expected_verticies_size; i++){
                values_match = values_match && (test_vertex_index_batch.verticies.at(i) == values[i]);
            }
            assert(values_match);
        }
        {
            bool values_match = true;
            unsigned int values[expected_indicies_size] = {
                0, 1, 2,
                0, 2, 3
            };
            for(size_t i = 0; i < expected_indicies_size; i++){
                values_match = values_match && (test_vertex_index_batch.indicies.at(i) == values[i]);
            }
            assert(values_match);
        }

        test_rect = Rect(glm::vec2(128.0f, 128.0f), glm::vec2(128.0f, 128.0f));
        test_color = glm::vec3(0.0f, 0.0f, 1.0f);
        // Verify that all following rect will be added correctly by induction
        expected_verticies_size = 48;
        expected_indicies_size = 12;

        addRect(test_vertex_index_batch, test_rect, test_color);
        assert(test_vertex_index_batch.indicies.size() == expected_indicies_size);
        assert(test_vertex_index_batch.verticies.size() == expected_verticies_size);
        assert(test_vertex_index_batch.index_offset == 8);

        {
            float values[expected_verticies_size] = {
                0.0f, 128.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                128.0f, 128.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                128.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

                128.0f, 256.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                256.0f, 256.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                256.0f, 128.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                128.0f, 128.0f, 0.0f, 0.0f, 0.0f, 1.0f
            };
            bool values_match = true;

            for(size_t i = 0; i < expected_verticies_size; i++){
                values_match = values_match && (test_vertex_index_batch.verticies.at(i) == values[i]);
            }
            assert(values_match);
        }
        {
            bool values_match = true;
            unsigned int values[expected_indicies_size] = {
                0, 1, 2,
                0, 2, 3,

                4, 5, 6,
                4, 6, 7
            };
            for(size_t i = 0; i < expected_indicies_size; i++){
                values_match = values_match && (test_vertex_index_batch.indicies.at(i) == values[i]);
            }
            assert(values_match);
        }


        test_vertex_index_batch.clear();
        //Verify that the clear action worked correctly
        assert(test_vertex_index_batch.indicies.size() == 0);
        assert(test_vertex_index_batch.verticies.size() == 0);
        assert(test_vertex_index_batch.index_offset == 0);
    }
    return 0;
}
