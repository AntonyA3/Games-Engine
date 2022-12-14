#include <breakout_engine.hpp>
#include <test_abstractions.hpp>

void displayTable(ButtonState state, bool down){
    std::string state_string = toString(state);
    std::string bool_string = toString(down);
    std::string new_state_string = toString(update(state, down));
    std::cout << "state: " << state_string << "| down: " << bool_string << " | new state: " << new_state_string << "|\n";
}

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
    {
        std::cout << "========Update Button State========\n ";
        std::cout << "| Previous State | down | new state|\n ";
        displayTable(ButtonState_Pressed, true);
        displayTable(ButtonState_Down, true);
        displayTable(ButtonState_Up, true);
        displayTable(ButtonState_Released, true);
        displayTable(ButtonState_Pressed, false);
        displayTable(ButtonState_Down, false);
        displayTable(ButtonState_Up, false);
        displayTable(ButtonState_Released, false);     

    }
    {
        std::cout << "========Cursor Construction Test========\n ";

        Cursor cursor = Cursor();
        std::cout << toString(cursor) << std::endl;
        Cursor cursor1;
        std::cout << toString(cursor1) << std::endl;

    }
    {
        std::cout << "========Update Matrix Test========\n ";
        glm::mat4 test_matrix;
        update(test_matrix, 640, 480);
        std::cout << glm::to_string(test_matrix) << std::endl;
    }
    {
        std::cout << "========Button To String Test========\n ";
        Button a_button = Button(SDL_SCANCODE_A, "A Button");
        std::cout << "Button Test:===========" << std::endl;
        std::cout << toString(a_button) << std::endl;
    }
    {
        std::cout << "========Cursor To String Test========\n ";

        Cursor cursor;
        cursor.position = glm::ivec2(40, 40);
        cursor.delta = glm::ivec2(-80, -20);

        std::cout << toString(cursor) << std::endl;
    }
    {
        std::cout << "========glm::ivec2 To String Test========\n ";
        glm::ivec2 vector = glm::ivec2(100, 40);
        std::cout << toString(vector) << std::endl;
    }
    return 0;
}
