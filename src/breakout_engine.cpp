#include <breakout_engine.hpp>


Rect::Rect(glm::vec2 position, glm::vec2 size){
    this->position = position;
    this->size = size;
}

glm::vec2 Rect::topLeft(){
    return this->position;
}

glm::vec2 Rect::topRight(){
    return glm::vec2(position.x + size.x, position.y);
}

glm::vec2 Rect::bottomLeft(){
    return glm::vec2(position.x, position.y + size.y);
}

glm::vec2 Rect::bottomRight(){
    return position + size;
}

Button::Button(SDL_Scancode scancode, std::string tag){
    this->state_change = true; // Presume that initialisation is a state change
    this->tag = tag;
    this->scancode = scancode;
    this->state = ButtonState_Up;
}

Cursor::Cursor(){
    this->position = glm::ivec2(0, 0);
    this->delta = glm::ivec2(0, 0);
}

void VertexIndexBatch::clear(){
    this->verticies.clear();
    this->indicies.clear();
    this->index_offset = 0;
}

Mesh::Mesh(){
    glGenBuffers(1, &this->vertex_buffer);
    glGenBuffers(1, &this->index_buffer);
}

std::string readFile(std::string filename){
    std::stringstream ss;
    std::ifstream my_read_file;
    my_read_file.open(filename);
    char read_buffer[2048];
    bool open = my_read_file.is_open();
    assert(open);
    if(open){
        while (!my_read_file.eof())
        {
            my_read_file.getline(read_buffer, 2048);
            ss << read_buffer;
            if(!my_read_file.eof()){
                ss << "\n";
            }
        }  
        my_read_file.close();
    }
    return ss.str();
} 

void update(glm::mat4& matrix, int width, int height){
    matrix = glm::ortho(0.0f, (float)width, (float)height, 0.0f);
}

ButtonState update(ButtonState state, bool down){
    ButtonState new_state = (state == ButtonState_Pressed && down) ? ButtonState_Down : state;
    new_state = (state == ButtonState_Down && down) ? ButtonState_Down : new_state;
    new_state = (state == ButtonState_Up && down) ? ButtonState_Pressed : new_state;
    new_state = (state == ButtonState_Released && down) ? ButtonState_Pressed : new_state;
    new_state = (state == ButtonState_Pressed && !down) ? ButtonState_Released : new_state;
    new_state = (state == ButtonState_Down && !down) ? ButtonState_Released : new_state;
    new_state = (state == ButtonState_Up && !down) ? ButtonState_Up : new_state;
    new_state = (state == ButtonState_Released && !down) ? ButtonState_Up : new_state;
    return new_state;
}

void update(Button& button, const Uint8 * keyboard_state){
    ButtonState new_state = update(button.state, keyboard_state[button.scancode]);
    button.state_change = new_state != button.state;
    button.state = new_state;
}

void update(Cursor& cursor){
    glm::ivec2 new_position;
    SDL_GetMouseState(&new_position.x, &new_position.y);
    cursor.delta = new_position - cursor.position;
    cursor.position = new_position;
}

void update(Mesh& mesh, VertexIndexBatch& batch){
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, batch.verticies.size() * sizeof(float), &batch.verticies.front(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, batch.indicies.size() * sizeof(unsigned int), &batch.indicies.front(), GL_DYNAMIC_DRAW);
    mesh.index_count = batch.indicies.size();
}

std::string toString(bool value){
    return (value) ? "true" : "false";
}



std::string toString(ButtonState value){
    switch (value)
    {
    case ButtonState_Pressed:
        return "ButtonState_Pressed";
    case ButtonState_Down:
        return "ButtonState_Down";
    case ButtonState_Up:
        return "ButtonState_Up";
    case ButtonState_Released:
        return "ButtonState_Released";    
    }
    return "";
}

std::string toString(Rect& rect){
    std::stringstream ss;
    ss << "Rect: {\n";
    ss << "   position: " << toString(rect.position) << "\n";
    ss << "   size: " << toString(rect.size) << "\n";
    ss << "}\n";
    return ss.str();

}


std::string toString(Button& button){
    std::stringstream ss;
    ss <<"Button: {\n";
    ss <<"   state_change: " << toString(button.state_change) << "\n";
    ss <<"   tag: " << button.tag << "\n";
    ss <<"   scancode: " << SDL_GetScancodeName(button.scancode) << "\n";
    ss <<"   button_state: " << toString(button.state) << "\n";
    ss << "}\n";
    return ss.str();
}

std::string toString(Cursor& cursor){
    std::stringstream ss;
    ss << "Cursor: {\n";
    ss << "   position: " << toString(cursor.position) << "\n";
    ss << "   delta: " << toString(cursor.delta) << "\n";
    ss << "}\n";
    return ss.str();
}

std::string toString(Mesh& mesh){
    std::stringstream ss;
    ss << "Mesh: {\n";
    ss << "   vertex_buffer: " << std::to_string(mesh.vertex_buffer) << "\n";
    ss << "   index_buffer: " << std::to_string(mesh.index_buffer) << "\n";
    ss << "}\n";
    return ss.str();
}

GLuint makeShader(GLenum shader_type, const char * shader_text){
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_text, NULL);
    glCompileShader(shader);

    return shader;
}

GLuint makeShader(GLenum shader_type, std::string filename){
    std::string content = readFile(filename);
    return makeShader(shader_type, content.c_str());
}

// Make program and delete the shaders that were provided as inputs
GLuint makeProgram(GLuint vertex_shader, GLuint fragment_shader){
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return program;
}

GLuint makeProgram(std::string vertex_shader_file, std::string fragment_shader_file){
    GLuint vertex_shader = makeShader(GL_VERTEX_SHADER, vertex_shader_file);
    GLuint fragment_shader = makeShader(GL_FRAGMENT_SHADER, fragment_shader_file);
    return makeProgram(vertex_shader, fragment_shader);
}

void addRect(VertexIndexBatch& vertex_index_batch, Rect& rect, Color3& color){
    float r = color.r;
    float g = color.g;
    float b = color.b;
    glm::vec2 bottom_left = rect.bottomLeft();
    glm::vec2 bottom_right = rect.bottomRight();
    glm::vec2 top_right = rect.topRight();
    glm::vec2 top_left = rect.topLeft();

    vertex_index_batch.verticies.insert(vertex_index_batch.verticies.end(),{
        bottom_left.x, bottom_left.y, 0.0f, r, g, b,
        bottom_right.x, bottom_right.y, 0.0f, r, g, b,
        top_right.x, top_right.y, 0.0f, r, g, b,
        top_left.x, top_left.y, 0.0f, r, g, b
    });

    unsigned int indicies[6] = {
        0, 1, 2,
        0, 2, 3
    };
    for(size_t i = 0; i < 6; i++){
        indicies[i] += vertex_index_batch.index_offset;
    }
    
    vertex_index_batch.indicies.insert(vertex_index_batch.indicies.end(), indicies, indicies + 6);
    vertex_index_batch.index_offset += 4;
}

void displayShaderCompileStatus(GLuint shader_object){
    GLint status;
    GLchar info_log[1000];
    glGetShaderiv(shader_object, GL_COMPILE_STATUS, &status);
    glGetShaderInfoLog(shader_object, 1000, NULL, &info_log[0]);
    if(!status){
        std::cout << info_log << '\n';
    }
}

void alwaysShowDemo(){
    bool show = true;
    ImGui::ShowDemoWindow(&show);
}
