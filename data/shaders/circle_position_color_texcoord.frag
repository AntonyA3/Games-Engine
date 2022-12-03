#version 330
precision mediump float;
in vec3 fcolor;
in vec2 fcoord;
out vec4 color;   

void main(){
    float in_circle = float(dot(fcoord, fcoord) <= 1.0f);
    color = vec4(fcolor, in_circle);
}

