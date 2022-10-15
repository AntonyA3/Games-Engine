#version 330
layout (location = 0) in vec3 vpos;
layout (location = 1) in vec3 vcolor;
uniform mat4 u_view_mat;

out vec3 fcolor;
void main(){
    fcolor = vcolor;
    gl_Position = u_view_mat * vec4(vpos, 1.0f);
}