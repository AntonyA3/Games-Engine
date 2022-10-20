


# Psuedo Code

CREATE complete_window
CREATE demo_window
CREATE global_matrix
CREATE sdl_gl_context_data


SET opengl viewport to WIDTH of sdl window and HEIGHT of SDL window
CREATE VAR opengl background color
SET Opengl background color to VAR opengl background color

SET CULL BACK FACE
CREATE imgui_wrapper

CREATE polygon_batcher
CREATE polygon_batch_mesh

CREATE mesh_generator

CREATE shader Program from vertex_shader file, fragment_shader file
SET the shader program UNIFORM matrix location from it's name in the shader

CREATE mesh
Generate a triangle mesh with Mesh generator

SET CULL Face as on

   
CREATE RECT render_rect (0,0, 100, 100);
CREATE mesh_from_rectangle from rect applied to mesh_from_rectangle

WHILE SDL Window is active
    WHILE SDL Event has polled an event
        GET The event FROM SDL EVENT Wrapper
        SEND event for imgui to process
        
        SWITCH Event Type:
            CASE QUIT
                LOG Ticks
                TERMINATE SDL WINDOW
            CASE WINDOW EVENT
                SWITCH WINDOW EVENT TYPE
                    CASE RESIZE EVENT
                        SET SDL Window width and window height
                        UPDATE OPENGL Viewport size


    CLEAR WINDOW
    USE SHADER PROGRAM

    CLEAR polygon_batcher for the new polygon
    CREATE 2 Rectangles and add it to polygon batch
    GENERATE mesh from polygon batch
    BIND polygon_batch_mesh
    PREPARE polygon_batch_mesh_verticies and indicies
    SET polygon_batch_mesh_matrix
    DRAW polygon_batch_mesh

    BIND Triangle Mesh
    shader_program SET MATRIX to global_matrix
    DRAW Traiangle Mesh

    BIND Rectangle Mesh
    shader_program SET MATRIX to global_matrix

    DRAW Rectangle Mesh

    USE NO SHADER PROGRAMS

    BEGIN imgui frame
        
        BEGIN imgui window "Cull Face Toggle"
        TOGGLE cull_face with tickbox
        IF TICKED
            ENABLE BACKFACE CULLING
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
