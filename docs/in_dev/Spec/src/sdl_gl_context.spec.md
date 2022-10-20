
# SDL GL Conetext 

## Summary 
An abstraction to store the SDLGLContext and it's initial properties
| Property | Description |
| --- | --- |
| m_gl_context | Stores The opengl context for SDL|


|Function | Description |
| --- | --- |
| The function Name | The function specification | 
| create | Given the properties of **this** <br> And a **pointer** to an SDL_Window <br> Set the opengl version of the window <br> Initialise the SDLGL_Context <br> And Initialise the SDLRenderer <br> GetOpenGL Functions with GLEW <br> |
| getGLContext | Return a **reference** to the SDLGLContext |


## Dependancies
| Dependancy | Explaination |
| --- | --- |
| SDL2_GLContext | The actual opengl context from SDL2 |

## Functions
| Function | Description |
| --- | --- |
| create | Creates the GL context for an SDL Window given Open gl version data |
| getGLContext | Gets the reference to the glContext |


## Test Cases
-