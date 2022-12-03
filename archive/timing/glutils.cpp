#include <glutils.hpp>


GLuint GLutils::attachShadersAndLinkProgram(GLuint& vertex_shader, GLuint& fragment_shader){
    GLuint program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    
    LOG(
        int status;
        GLchar info_log[1000]; 
        glGetProgramiv(program, GL_LINK_STATUS, &status);
        glGetProgramInfoLog(program, 1000, NULL, &info_log[0]);
        if (!status){
            std::cout << "Shader status compile failed" << "\n";       
            std::cout << info_log << "\n";
        }
    );
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return program;

}


GLuint GLutils::makeProgramFromContent(const char *  vertex_content, const char * fragment_content){

    GLuint vertex_shader = this->makeShaderFromContent(vertex_content, GL_VERTEX_SHADER);
    GLuint fragment_shader = this->makeShaderFromContent(fragment_content, GL_FRAGMENT_SHADER);
    
    return GLutils::attachShadersAndLinkProgram(vertex_shader, fragment_shader);

    
}

GLuint GLutils::makeProgram(std::string vertex_file, std::string fragment_file){
    GLuint program = glCreateProgram();
    LOG(
        std::cout << "Begin Make Vertex Shader" << std::endl;
    );
    GLuint vertex_shader = makeShader(vertex_file, GL_VERTEX_SHADER);
    GLuint fragment_shader = makeShader(fragment_file, GL_FRAGMENT_SHADER);
    return GLutils::attachShadersAndLinkProgram(vertex_shader, fragment_shader);


    // // Duplicate
    // glAttachShader(program, vertex_shader);
    // glAttachShader(program, fragment_shader);
    // glLinkProgram(program);
    
    // LOG(
    //     int status;
    //     GLchar info_log[1000]; 
    //     glGetProgramiv(program, GL_LINK_STATUS, &status);
    //     glGetProgramInfoLog(program, 1000, NULL, &info_log[0]);
    //     if (!status){
    //         std::cout << "Shader status compile failed" << "\n";       
    //         std::cout << info_log << "\n";
    //     }
    // );
    // glDeleteShader(vertex_shader);
    // glDeleteShader(fragment_shader);
    // return program;
}



GLuint GLutils::makeShaderFromContent(const char * shader_content, GLenum shader_type){
    GLuint shader = glCreateShader(shader_type);

    glShaderSource(shader, 1, &shader_content, NULL);
    glCompileShader(shader);

    LOG(
        int status;
        GLchar info_log[1000];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        glGetShaderInfoLog(shader, 1000, NULL, &info_log[0]);
        if(!status){
            std::cout << "failed to load this vertex shader" << std::endl;
            std::cout << info_log << '\n';
        }
    );
    return shader;
}


GLuint GLutils::makeShader(std::string shader_file, GLenum shader_type){
    FileReader file_reader;
    file_reader.read(shader_file);
    const char * shader_src = file_reader.refContent().c_str();
    return makeShaderFromContent(shader_src, shader_type);
}
