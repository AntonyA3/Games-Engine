

#include <i_renderer.hpp>
#include <imgui/imgui.h>
struct RadialBricks
{
    int layers = 10;
    int circle_radius = 8.0f;
    int origin_x = 200;
    int origin_y = 200;
    int radial_spacing = 64;
    int block_height = 8;
    int block_width = 32;
    int cycles = 10;

    void edit(){
        ImGui::Begin("Radial Brick Editor");
        ImGui::DragInt("layers", &layers);
        ImGui::DragInt("circle_radius", &circle_radius);
        ImGui::DragInt("origin_x", &origin_x);
        ImGui::DragInt("origin_y", &origin_y);
        ImGui::DragInt("radial_spacing", &radial_spacing);
        ImGui::DragInt("block_height", &block_height);
        ImGui::DragInt("block_width", &block_width);
        ImGui::DragInt("cycles", &cycles);

        ImGui::End();
    }

    template <typename TRenderer>
    void renderControl(TRenderer& renderer){ 
        Circle circle;
        circle.create(glm::vec2(origin_x, origin_y), circle_radius);
        for(int c = 0; c < cycles; c++){
            float angle = c / (float)cycles * (M_PI * 2.0f);

            glm::vec2 direction = glm::vec2(-cosf(angle), sinf(angle));
            for(int i = 0; i < layers; i++){
                glm::vec2 origin = glm::vec2(origin_x, origin_y);;
                SweepedRect sweep_rect;
                sweep_rect.create(
                    origin + direction * (float)(circle_radius + radial_spacing + i * (block_height + radial_spacing)), 
                    block_width / 2.0f, direction * (float)block_width
                );
                Polygon polygon;
                polygon.create(sweep_rect);
                renderer.addPolygon(polygon, glm::vec3(1.0f,0.5, 0.0f));
                
            }

        }
        
        renderer.addCircle(circle, glm::vec3(1.0f, 1.0f, 0.0f));
        
    }


};
