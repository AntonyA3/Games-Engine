
# Dear ImGui Wrapper

## Summary 
A short summary

| Property | Description |
| --- | --- |
| m_io | A reference to Imgui's io |

|Function | Description |
| --- | --- |
| create | Given a **pointer** to an SDL_Window <br> And a **reference** to a gl_context <br> Create Imgui context <br> Set ImGui io property <br> Set Color Theme to default <br> Use ImGui for SDL and OpenGL <br> Then Initialise ImGui with shader version 150|  
| processEvent | Given an SDL_Event <br> Return the boolean results of delegating the SDL_Event for ImGui to process | 
| beginFrame | Given **this** object has access to Imgui <br> Create a new Imgui(Gui) Frame For OpenGL3 <br> And Create a new ImGui (Gui) Frame for SDL2 <br> And create a new Imgui (Gui) frame for OpenGl <br> An Register a Imgui new frame | 
| renderFrame | Given **this** object has access to Imgui through **headers** <br> Prepare ImGui for rendering <br> And use opengl3 to render OpenGl3 | 
