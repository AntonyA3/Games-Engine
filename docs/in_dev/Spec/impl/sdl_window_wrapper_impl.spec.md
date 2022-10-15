


# Psuedo Code

SDLWindowWrapper sdl_window;
CREATE sdl_window
CREATE sdl_event_wrapper
CREATE sdl_gl_context With major version 3 minor version 3

CREATE demo_window


SET opengl viewport to WIDTH of sdl window and HEIGHT of SDL window
CREATE VAR opengl background color
SET Opengl background color to VAR opengl background color

SET CULL BACK FACE
CREATE imgui_wrapper

CREATE shader Program from vertex_shader file, fragment_shader file
SET the shader program UNIFORM matrix location from it's name in the shader

CREATE mesh
Generate a triangle mesh with Mesh generator

SET CULL Face as on

   
CREATE RECT render_rect
CREATE mesh_from_rectangle from rect applied to mesh_from_rectangle

WHILE SDL Window is active
    WHILE SDL Event has polled an event
        GET The event FROM SDL EVENT Wrapper
        SEND event for imgui to process
        
        SWITCH Event Type:
            CASE SDL QUIT
                LOG Ticks
                TERMINATE SDL WINDOW


    CLEAR WINDOW
    USE SHADER PROGRAM

    BIND Triangle Mesh
    DRAW Traiangle Mesh

    BIND Rectangle Mesh
    DRAW Rectangle Mesh



    USE NO SHADER PROGRAMS

    BEGIN imgui frame
        
        BEGIN imgui window "Cull Face Toggle"
        TOGGLE cull_face with tickbox
        IF TICKED
            ENABKE BACKFACE CULLING
        ELSE
            TURN OFF FACE CULLING
        End Imgui Window

    SHOW DEMO WINDOW    
    RENDER imgui frame
    SWAP FRAME
    SDL_GL_SwapWindow(sdl_window.getWindow());
DESTROY SDL WINDOW
QUIT SDL
END PROGRAM
