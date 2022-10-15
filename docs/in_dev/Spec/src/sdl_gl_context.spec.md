
# SDL GL Conetext 

## Summary 
An abstraction to store the SDLGLContext and it's initial properties
| Property | Description |
| --- | --- |
| gl_minor_version  | Stores the open gl minor version **on initialisation** |
| gl_major_version | Stores the opengl major version **on initialisation** |
| m_gl_context | Stores The opengl context for SDL|
| m_renderer | Stores an **allocated reference** to the SDL's renderer for the programs lifetime |


|Function | Description |
| --- | --- |
| The function Name | The function specification | 
| create | Given the properties of **this** <br> And a **pointer** to an SDL_Window <br> Set the opengl version of the window <br> Initialise the SDLGL_Context <br> And Initialise the SDLRenderer <br> GetOpenGL Functions with GLEW <br> |
| getGLContext | Return a **reference** to the SDLGLContext |