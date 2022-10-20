#version 330
precision mediump float;
in vec3 fcolor;
in vec2 fcoord;
out vec4 color;   
/*
INPUT color
INPUT coordinate 
PROCESS Pixel(Fragment) is visible when 
    -dot product is less than or equal to 1.0;
OUTPUT 
    - color(Input color)
    - where color alpha is the in_circle value
*/ 
void main(){
    float in_circle = float(dot(fcoord, fcoord) <= 1.0f);
    color = vec4(fcolor, in_circle);
}

