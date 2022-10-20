


Tasks Done
- Find all parts of the Program that will be affected if the size of the Window Changes describe the nessessary changes then implement the changes
- Render Rectangle with Rectangle Mesh

## Date : 15/10/2022 16/10/2022

Available Tasks
- Write Tests for the Program Loader 
- Write Tests for the Shader Loader 
- Find all parts of the Program that will be affected if the size of the Window Changes describe the nessessary changes then implement the changes


## Task Begin

 Find all parts of the Program that will be affected if the size of the Window Changes describe the nessessary changes then implement the changes


In src\impl\sdl_window_wrapper.impl.cpp

At about line 88 Remove SDL_Log on quit
At about line 90
    ADD CASE Where event may be a window resize event
        GET the new window size from the event
        FOR sdl_window SET current width and current height
        Call glViewport TO SET the new colour size
        
In docs\in_dev\Spec\impl\sdl_window_wrapper_impl.spec.md
Add Psuedocode after line 42 to represent this change


New system constraints
docs\in_dev\Spec\full_system\constraints.md
- The graphics matches the window size


docs\in_dev\Design\.$Total System Design.drawio.bkp
- no diagramatic changes


Add task to consider contineous window size changing

## Task Done

## Task Begin



Available Tasks
- Write Tests for the Program Loader 
- Write Tests for the Shader Loader 
- Conteneous Window Size changes
- Add a matrix to objects so that they can bee see on a 640 by 480 box, test it by creating a larger rectangle and larger triangle


## Task Begin

Add a matrix to objects so that they can bee see on a 640 by 480 box, test it by creating a larger rectangle and larger triangle


#### Changes to make


*File: include\mesh.hpp*
Remove matrix from mesh

*File: src\impl\sdl_window_wrapper.impl.cpp*
*Comments: related to changed locations*
- At about line 28 create an orthographic matrix that can represent the opengl coordinates being tranformed to fit a screen of 640 480 called global_matrix
- At about line 61 make the verticies of the triangle large enough to be visible in the screen
- At about line 69 make the position/size of the rectangle large enough to be visible in the screen
- At about line 76 create a rectangle that is large enough to be visible
- At line 113 set matrix to global matrix
- At line 118 set matrix to global matrix

*File: src\mesh_from_rectangle.cpp*
- At line 31 remove matrix setter

*File: docs\in_dev\Spec\full_system\constraints.md
- Add the 640 by 480 screen size constraint

*File: docs\in_dev\Design\Total System Design.drawio*
- Remove matrix from Mesh


- Check if the Traingle and rectangle is till able to be renderer

*File: docs\in_dev\Spec\impl\sdl_window_wrapper_impl.spec.md*
- Update psuedocode as needed

*File: src\impl\sdl_window_wrapper.impl.cpp*
*Comments: removed the comments that make changes*

## Task Done

Available Tasks
- Write Tests for the Program Loader 
- Write Tests for the Shader Loader 
- Conteneous Window Size changes
- Batch render Polygons Shapes
- Batch render Smooth Circles Shapes

## Task Begin

Batch render Polygons Shapes

Ad an object that can be used to render polygon batches

*In a previous project I found out that calling glDrawElements multiple times will slow the program down to a frame rate below 60fps if too many draw calls were made, therefore It would be better to combine the meshes of an object if they were small meshes, that would be rendered based on the same shader program*



*File:CREATE docs\in_dev\Spec\src\mesh_data_from_rectangle.spec.md
- Specification encapsulates  the functionality of src/mesh_from_rectangle.cpp from approximately line 9 to 29


*File:CREATE docs\in_dev\Spec\src\mesh_from_rectangle.spec.md
- Change specification to include mesh_data_from_rectangle informatiom

*File: docs\in_dev\Spec\src\polygon_batcher.spec.md*
Some of the specification
Verticies : the verticies that will be used to build the mesh
indicies : the indicies that will be used to build the model
index_value : To tract the current index of the model
Mesh : The Actual render
MeshGenerator: Generates the mesh from the indicies and verticies
addRectangle: Generates the rectangle verticies and indicies, and adds the rectangle verticies and indicies to the verticies and indicies array
bind: binds the generated mesh
render: renders the
clear: clears the verticies and indicies, in preperation for a new mesh


*File: CREATE include\mesh_data_from_rectangle.hpp
*File: CREATE src\mesh_data_from_rectangle.cpp
- Implement the created specification for this struct



*File: include\mesh_from_rectangle.hpp
*File: src\mesh_from_rectangle.cpp
- Create a class to create rectangle mesh data from this function since it's functionality is also needed by the PolygonBatcher
- Edits required at approximately line 8




*File:docs\in_dev\Design\Total System Design.drawio*
- Modify diagramas to fit this new specification

*File:CREATE include\mesh_data_from_rectangle.hpp*
*File:CREATE src\mesh_data_from_rectangle.cpp*
- Create this
- Move functionality related to from src\mesh_from_rectangle.cpp to this class

*File:src\impl\sdl_window_wrapper.impl.cpp*
- At about line 42 Create polygon batcher_data
- At about line 43 Create a polygon_batch_mesh
- And a meshgenerator
    - cre
- At about line 115 after shader_program.use()
    - clear batcher_data
    - create 2 rects
    - add two rectangles
    - update polygon_batch_mesh with mesh_generator
    - set the matrix
    - draw polygon batch mesh
Considerations
- Consider any new generalisation methods, so that some classes can be removed


*File:docs\in_dev\Spec\impl\sdl_window_wrapper_impl.spec.md*
Add the new code as psuedocode

## Task Done

Available Tasks
- Write Tests for the Program Loader 
- Write Tests for the Shader Loader 
- Conteneous Window Size changes
- Batch render Smooth Circles Shapes
- An SDLWindowWrapper is composed of an SDLEventWrapper : the SDLEventWrapper can exist on it's own
- Add clear to thus making the filereader more mutable
- Abstraction for initialising opengl
- 

## Task Begin
SDL_CreateRenderer? Remove the SDL Default renderer as it is not used anywhere

*File:docs\in_dev\Spec\src\sdl_gl_context.spec.md*
- Remove anthing related to SDL_Renderer

*File:docs\in_dev\Design\Total System Design.drawio*
- Remove anthing related to SDL_Renderer in SDLGLContextWrapper uml diagram

*File:include\sdl_gl_context_wrapper.hpp*
- Remove anthing related to SDL_Renderer

*File:src\sdl_gl_context_wrapper.cpp*
- Remove anthing related to SDL_Renderer
## Task End

Available Tasks
- Write Tests for the Program Loader 
- Write Tests for the Shader Loader 
- Conteneous Window Size changes
- Batch render Smooth Circles Shapes
- An SDLWindowWrapper is composed of an SDLEventWrapper : the SDLEventWrapper can exist on it's own
- Add clear to thus making the filereader more mutable
- Abstraction for initialising opengl
- Create SDL_GL_Context_Data to decouple the sdl gl context data from the data data that is used to create the opengl context

## Task Begin

Create SDL_GL_Context_Data to decouple the sdl gl context data from the data data that is used to create the opengl context.

Affected files / objects

*File:CREATE docs\in_dev\Spec\src\sdl_gl_context_data.spec.md*
- a struct with shader major version and minor version

*File:CREATE docs\in_dev\Spec\src\sdl_gl_context.spec.md*
- remove the shader minor version
- remove shader major version
- the create function recieves the SDL Window and the glShader version

*File:docs\in_dev\Design\Total System Design.drawio*
- In UML diagram modify the SDLGLContext Class
- Add a Dependancy on the UML Diagram to SDLGLContextData

*File:include\sdl_gl_context_data.hpp*
- A struct that is able to store the properties related to setting up an opengl context


*File:include\sdl_gl_context_wrapper.hpp*
- Change crate function parametres to take the SDLGlContextData and the window

*File:src\sdl_gl_context_wrapper.cpp*
- Make the basic modifications to the change function

*File:src\impl\sdl_window_wrapper.impl.cpp*
- Add sdlglcontext data to psuedocode

## Task End

Available Tasks
- Write Tests for the Program Loader 
- Write Tests for the Shader Loader 
- Conteneous Window Size changes
- Batch render Smooth Circles Shapes
- An SDLWindowWrapper is composed of an SDLEventWrapper : the SDLEventWrapper can exist on it's own
- Add clear to thus making the filereader more mutable
- Decouple SDL Window Data from SDLWindowWrapper

## Task Begin
Decouple SDL Window Data from SDLWindowWrapper

*File: CREATE docs\in_dev\Spec\src\sdl_window_data.spec.md*
- Create this, move nessessary properties from SDLWindowWrapper to SDLWindowData

*File: docs\in_dev\Spec\src\sdl_window_wrapper.spec.md*
- There should only be a create window function that takes SDLWindowData as an argument

*File:docs\in_dev\Design\Total System Design.drawio*
- modify UML based on spec

*File:include\sdl_window_wrapper.hpp*
- Remove some properties

*File:include\sdl_window_data.hpp*
- Create this data 

*File:src\sdl_window_wrapper.cpp*
- Modify this 


*File:src\impl\sdl_window_wrapper.impl.cpp*
- Add changes to psuedocode

- Check if the program is still woring

## Task End

Available Tasks
- Write Tests for the Program Loader 
- Write Tests for the Shader Loader 
- Conteneous Window Size changes
- Batch render Smooth Circles Shapes
- An SDLWindowWrapper is composed of an SDLEventWrapper : the SDLEventWrapper can exist on it's own
- Add clear to thus making the filereader more mutable
- A Class that can be used to create an SDLWindow and an ImGui GUI in a single create command for fast integration testing
## Task Begin

A Class that can be used to create an SDLWindow and an ImGui GUI in a single create command for fast integration testing

*File:docs\in_dev\Design\Total System Design.drawio*
- Create the Complete Window Class
- Create the Complete Window Data class

*File:CREATE docs\in_dev\Spec\impl\complete_window_impl.spec.md*
- Describes the Complete window class


*File:CREATE include\complete_window.hpp*
*File:CREATE src\complete_window.cpp*


*File:docs\in_dev\Spec\impl\sdl_window_wrapper_impl.spec.md*
- Refactor to use the Complete Window to implement same behaviour
## Task End

Available Tasks
- Write Tests for the Program Loader 
- Write Tests for the Shader Loader 
- Conteneous Window Size changes
- Batch render Smooth Circles Shapes
- Add clear to thus making the filereader more mutable

## Task Begin
Batch render Smooth Circles Shapes


SubTasks
- Refactor to create a polygonRenderer
- Create a circle Renderer

## Sub Task Begin
Refactor to create a polygonRenderer
*File:docs\in_dev\Design\Total System Design.drawio*
- Create the polygon Renderer object using polygonBatcher and shader program
- Check for syntax errors, fully test later
## Sub Task End
SubTasks
- Refactor to create a polygonRenderer
- Create a circle Renderer
- A shader to shade any polygon as a circle

## Sub Task Begin
- create a circle datatype
- create a circle_position_color_shader.vert and frag
- enable opengl transparancy
- try using circle shader on polygon object

Changed Files
*data\shaders\circle_position_color.frag*
- A new fragment shader
*data\shaders\circle_position_color.vert*
- A new Vertex shader


glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

Consideration
- Shaders themselves are likely to have their own abstractions
## Sub Task End


## Sub Task Begin

- Generalise shader program to support  (xyz, rgb, uv) layouts and (xyz, rgb) layout and more

*File:docs\in_dev\Design\Total System Design.drawio*
- A ShaderProgram should store information about it's vertex attributes
- Because the circle Shader has more and diffrent vertex attributes to the Polygon Shader

*File:Edit docs\in_dev\Spec\impl\shader_program.spec.md*

*File:Edit include\shader_program.hpp*
- Add a vertex attributes vector as a property

*File:Edit src\shader_program.cpp*
- edit enable vertex attributes, so that it can enable an array of attributes

*File:Create include\vertex_attribute_data.hpp*
- The plain data for the vertex attribute

*File:docs\in_dev\Spec\impl\sdl_window_wrapper_impl.spec.md*

## Sub Task End

SubTasks
- Refactor to create a polygonRenderer
- Create a circle Renderer
- A shader to shade any polygon as a circle
- Generalise MeshDataConverter to be Just a class for generating Mesh data from anything, unencapsulated

## Sub Task Begin
- Generalise MeshDataConverter to be Just a class for generating Mesh data from anything, unencapsulated
- create Methods for generating diffrent types of meshes, for position_color, for position_color_coords


*All files: Find MeshDataConverter and rename it to MeshDataConverter*

## Sub Task End


## Sub Task Begin
- Merge PolygonBatch into the class MeshDataConverter

Expect no changes to behavior
Archive 
    docs\in_dev\Spec\src\polygon_batcher.spec.md
    include\polygon_batcher.hpp
    src\polygon_batcher.cpp

Modify
    include\mesh_data_converter.hpp
        - add index_offset variable
        - add create function
    src\mesh_data_converter.cpp
        - remove index_stride from all functions
        - resetindex offset to 0 on clear
        - add create functions
        - index stride += 4 for all rectangle indicies that are pushed

        - made and fixed an error relating to adding indicies to the index array of the Mesh Data Generator
    
    include\polygon_renderer.hpp   
        - replace polygon batcher with mesh dataconverter
        - create the mesh_data_converter

    src\polygon_renderer.cpp
        -delegate to mesh data converter, not the polygon_batcher


    docs\in_dev\Spec\impl\sdl_window_wrapper_impl.spec.md

    -remove all polygon_batcher inclusion


    
## Sub Task End

SubTasks
- Rename PolygonRenderer to Renderer
- The polygon renderer is composed of a 
- Create an add perfect circle to the render

## Sub Task Begin
- Rename PolygonRenderer to Renderer


## Sub Task End
SubTasks
- Create a Renderer that uses that is able to draw from a rect that was generated from a circle

## Sub Task Begin
Create a Renderer that uses that is able to draw from a rect that was generated from a circle

docs\in_dev\Spec\impl\sdl_window_wrapper_impl.spec.md
- Create a new shader program for circle
- create a new renderer for circle
- Try the circle shader with a circle at 400, 400 radius 50
- Done
## Sub Task End
## Task End

Some Tasks
- Clean up the code
- Test some of the components
- write a specification for some aspects of the renderer
- Fix the issue, where the size of the screen stretches what is show in the viewport
- Reorganise the UML diagram and seperate them by High level goals
- Write the Breakout Game Engine
    - A renderer
        - Define certain rendererds ad  sub renderers
        - Render a capsule
        - Render any arbitrary polygon
        - Render from a texture / sprite
    - Write the minimally required physics engine
        - Rects on rects
            - write intersection between axis aligned rects
            - Write physics on Axis aligned rectangles
        - Rect on circles
            - write intersection between a rect and a circle
            - Write physics on rects and circles
        - Wall test
    -Write the Game Logic
        - Ball hits a paddle
        - Ball hits a wall

    -Write the Game editor

## Consider implementing source code in a more to dow approach

## Task Begin
Use a better design technique to model parts of the code, maintain the uml diagram for archival reasons

- Archive MeshFromRectangle
- make the MeshGenerator a part of the mesh, by making it a methos called setData
## Task End
Some Tasks
- Test some of the components
- Fix the issue, where the size of the screen stretches what is show in the viewport
- Write the Breakout Game Engine
    - A renderer
        - Define certain rendererds ad  sub renderers
        - Render a capsule
        - Render any arbitrary polygon
        - Render from a texture / sprite
    - Write the minimally required physics engine
        - Rects on rects
            - write intersection between axis aligned rects
            - Write physics on Axis aligned rectangles
        - Rect on circles
            - write intersection between a rect and a circle
            - Write physics on rects and circles
        - Wall test
    -Write the Game Logic
        - Ball hits a paddle
        - Ball hits a wall

    -Write the Game editor
## Task Begin
- Create the renderer that encapsulated the subRenderer.
- create the circle subrenderer
- create the rectangle subrenderer
## Task End



## Task Begin

## Task End