#version 330
precision mediump float;
in vec3 fcolor;
in vec2 fTexcoord;
out vec4 color;
uniform sampler2D uTexture;
void main(){
   color = texture(uTexture, fTexcoord);
}

