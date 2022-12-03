#ifndef GAMES_ENGINE_BRICK_GRID
#define GAMES_ENGINE_BRICK_GRID

#include <breakout_game/bricks.hpp>
#include <imgui/imgui.h>
#include <renderer.hpp>
struct BrickGrid{
    int row_offset = 0;
    int column_offset = 0;
    int row = 5;
    int column = 5;
    int row_pixel_space = 4;
    int column_pixel_space = 4;
    int brick_width = 8;
    int brick_height = 8;

    std::vector<Bricks::Brick> makeBrick();
    void edit();

    template <typename TRenderer>
    void renderControl(TRenderer& renderer){
        for(int row = 0; row < this->row; row++){
            for(int column = 0; column < this->column; column++){
                AARect rect;
                rect.m_position.x = this->column_offset + column * (this->brick_width + this->column_pixel_space);
                rect.m_position.y = this->row_offset + row * (this->brick_height + this->row_pixel_space);
                rect.m_size.x = this->brick_width;
                rect.m_size.y = this->brick_height;
                renderer.addRect(rect, glm::vec3(1.0f, 0.0f, 1.0f));
            }
        }
    }
};
#endif