#include <level_editor_mode.hpp>


void LevelEditorMode::update(float dt){
    // std::cout << "Welcome To Edit Mode" << "You can Move things like game Objects" << std::endl;
    // ImGui::Begin("Edit Mode");
    // {

    //     if(ImGui::Button("Save")){
    //         using namespace rapidxml;
    //         xml_document<> doc;
    //         xml_node<> *paddle_node = doc.allocate_node(node_element, "Paddle");
    //         doc.append_node(paddle_node);

    //         xml_node<> *position_node = doc.allocate_node(node_element, "Position");
    //         paddle_node->append_node(position_node);
    
    //         std::string x_string = std::to_string(primary_paddle->position.x);
    //         xml_node<> *x_node = doc.allocate_node(node_element, "X", x_string.c_str());
    //         position_node->append_node(x_node);
            
    //         std::string y_string = std::to_string(primary_paddle->position.y);
    //         xml_node<> *y_node = doc.allocate_node(node_element, "Y", y_string.c_str());
    //         position_node->append_node(y_node);
            
    //         //File Writer
    //         // Create a file Writer
    //         {
    //             std::stringstream ss;
    //             ss << doc;
    //             std::ofstream my_write_file;
    //             my_write_file.open("data\\scenarios\\save_scenario.xml");
    //             if(my_write_file.is_open()){
    //                 my_write_file << ss.rdbuf();
    //             }
    //         }
    //     }
    // }
    // ImGui::End();
}