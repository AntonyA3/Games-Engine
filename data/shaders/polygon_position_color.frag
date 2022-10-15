#version 330
precision mediump float;
in vec3 fcolor;
out vec4 color;    
void main(){
    color = vec4(fcolor, 1.0f);
}