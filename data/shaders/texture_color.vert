#version 330
layout (location = 0) in vec3 vpos;
layout (location = 1) in vec3 vcolor;
layout (location = 2) in vec2 vTexcoord;
uniform mat4 uViewmat;
out vec3 fcolor;
out vec2 fTexcoord;
void main(){
   fcolor = vcolor;
   fTexcoord = vTexcoord;
   gl_Position = uViewmat * vec4(vpos, 1.0f);
}
