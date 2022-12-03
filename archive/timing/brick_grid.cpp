#include <brick_grid.hpp>


std::vector<Bricks::Brick> BrickGrid::makeBrick(){
    std::vector<Bricks::Brick> bricks;
    for(int row = 0; row < this->row; row++){
        for(int column = 0; column <  this->column; column++){    
            AARect rect;
            rect.m_position.x =  this->column_offset + column * ( this->brick_width +  this->column_pixel_space);
            rect.m_position.y =  this->row_offset + row * ( this->brick_height +  this->row_pixel_space);
            rect.m_size.x =  this->brick_width;
            rect.m_size.y =  this->brick_height;
            Bricks::Brick brick;
            brick.rect = rect;
            brick.active = true;
            bricks.push_back(brick);
        }
    }
    return bricks;
}

void BrickGrid::edit(){
    ImGui::DragInt("row_offset", &this->row_offset);
    ImGui::DragInt("column_offset", &this->column_offset);
    ImGui::DragInt("Row Count", &this->row);
    ImGui::DragInt("Column Count", &this->column);
    ImGui::DragInt("row_pixel_space", &this->row_pixel_space);
    ImGui::DragInt("column_pixel_space", &this->column_pixel_space);
    ImGui::DragInt("brick_width", &this->brick_width);
    ImGui::DragInt("brick_height", &this->brick_height);
}

