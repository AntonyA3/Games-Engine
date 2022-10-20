
# Object Name

## Summary 
This encapsulates everything that is associated to creating and running and SDLWindow with OpenGl and DearImgui

| Property | Description |
| --- | --- |
| sdl_window_wrapper | Encapsulates the SDL_Window |
| sdl_gl_context_wrapper | Encapsulates the GL_Context_Wrapper|
| m_dear_imgui_wrapper | Encapsulates the imgui context|
| m_sdl_event_wrapper | Encapsulates the sdl_event_wrapper|

## Dependancies
| Dependancy | Explaination |
| --- | --- |
| Complete Window Data | The data required to create the SDL Window and the data required to create the sub components |

## Functions
| Function | Description |
| --- | --- |
| create | delegates creating a complete window, to creating the sub components of the window |
| polledEvent | delegates polling to the SDLEventWrapper |
| newxtEvent | delegates getting the next event to SDLEventWrapper |


## Test Cases
- Works if all subcomponents work