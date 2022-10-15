
# Program Loader

## Summary 
A class to create a opengl shader program and also get the details related tothe status of loading the shader

| Property | Description |
| --- | --- |
| m_program | The output shader program |
| m_vertex_shader_content | The output vertex shader information|
| m_fragment_shader_content | The output fragment shader information |

## Dependancies
| Dependancy | Explaination |
| --- | --- |
| ShaderLoader | To be used to load each of the individual shaders |
| GLEW | Shader compilation relies on functions in OpenGl |

## Functions
| Function | Description |
| --- | --- |
| load | Loads a shader based on the given vertex shader file path and fragment shader file path |


## Test Cases
- load with valid vertex shader and fragment shader 
- load with invalid vertex shader
- double loading progrma/
