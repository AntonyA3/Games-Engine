#version 330
layout (location = 0) in vec3 vpos;
layout (location = 1) in vec3 vcolor;
layout (location = 2) in vec2 vcoord;

uniform mat4 u_view_mat;
out vec3 fcolor;
out vec2 fcoord;

void main(){
    fcolor = vcolor;
    fcoord = vcoord;
    gl_Position = u_view_mat * vec4(vpos, 1.0f);
}