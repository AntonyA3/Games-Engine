
#ifndef GAMES_ENGINE_SHADER_PROGRAM
#define GAMES_ENGINE_SHADER_PROGRAM
#include <GL/glew.h>

struct ShaderProgram
{
    GLuint program, uniform_matrix_location;

    void use(){
        glUseProgram(program);
    }

    void setMatrix(float * matrix){
        glUniformMatrix4fv(uniform_matrix_location, 1, GL_FALSE, matrix);

    }

    void enableVertexAttributes(){
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(0 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);   
    }
};

#endif