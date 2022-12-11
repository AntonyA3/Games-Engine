
Dec GLUTILS

Imp GLUTILS

FR3.4: Make opengl program give the vertex shader and fragment shader file path<input type="checkbox"></br>
FR3.4: Make opengl program give the vertex shader and fragment shader string content<input type="checkbox"></br>


FR3.5: Make opengl shader given the shader type and the shader file path<input type="checkbox"></br>
FR3.5: Make opengl shader given the shader type and the shader string content<input type="checkbox"></br>

DEC Intersector

FR3.6: Check if a rectangle intersects a rectangle<input type="checkbox"></br>
FR3.7: Check if a rectangle intersects a circle<input type="checkbox"></br>
FR3.8: Check if a circle intersects a circle<input type="checkbox"></br>
FR3.9: Check if a polygon intersects a polygon<input type="checkbox"></br>
FR4.0: Check if a polygon intersects a circle<input type="checkbox"></br>
FR4.1: Check if a polygon intersects a rect<input type="checkbox"></br>
 
Impl Intersector

--- ---
Physics Bounce Decleration

FR4.2: Resolve Circle from Rect for Ball intersecting a Paddle<input type="checkbox"></br>

--- --- 
Physics Solving decleartion

FR4.3: Resolve Rectangle between Left Boundary and right boundary for Paddle intersects left wall and paddle intersects right wall<input type="checkbox"></br>

FR4.4: Find the first object that was hit from all the object hit in the iterative update step<input type="checkbox"></br>

--- ---
Timing Related Struct Declerations
FR4.5: A Time Controller has a time and a delta time<input type="checkbox"></br>

Timeing Related member functions

FR9.9: Given a the previous time (in milliseconds) and the current time (in milliseconds), update the delta time as the diffrence between the current time and previous time, then converted into sectonds <input type="checkbox"></br>
--- ---

Time Related Free Functions
FR4.6: Update the time controller to calculate the delta time and the current time given a new time<input type="checkbox"></br>


-- --- muiltishape composition based member functions
FR5.1: AddCircle to the multishape group<input type="checkbox"></br>
FR5.2: Add rect to the multishape group<input type="checkbox"></br>


--- ---
Graphics  Related Struct Declerations
FR5.0: A Mesh has a vertex buffer and an Index buffer
FR5.6: A polygon renderer has a Mesh <input type="checkbox"></br>
FR5.7: A circle renderer has a Mesh<input type="checkbox"></br>
FR5.8: A texture renderer has a Mesh<input type="checkbox"></br>
FR7.2: Initialise the Rect Circle and Texture renderer<input type="checkbox"></br>
FR7.3: Initialise Frame buffer<input type="checkbox"></br>
FR7.4: Initialise background color as grey <input type="checkbox"></br>


Graphics Related Free Functions

FR5.4: Add an arc to the polygon renderer</br>
FR5.5: Add a circle slice to a polygon renderer</br>
FR6.3: add slice to a  Slices<input type="checkbox"></br>


Scene Object Selection Related Requirments
FR8.6: When select button is released, unselect all selected objects<input type="checkbox"></br>



Geometric Inheritance Template

FR4.8: ShapeGroup to operate shape functions on a list of all available shapes if, they have been combined, including checking if any shape is inside and FR4.9: also moving all shapes in the group.<input type="checkbox"></br>


Geometric Function Delerations 
FR1.6: It is possible to get the bounding rectangle of a circle
- Criteria: A circle with position and radius data is converted to the correct rectangle<input type="checkbox"></br>
FR2.0: Create a Polygon, given a rectangle<input type="checkbox"></br>
FR3.2: Get the Circle that represents the start of the Capsule<input type="checkbox"></br>
FR3.2: Get the Circle that represents the end of the Capsule<input type="checkbox"></br>


Geometric Related Free FUnctions
FR9.0: Add ball to circle rendering batch<input type="checkbox"></br>


Game Related Structs
FR6.0: Arc Brick has a position an inner radius and an outer radius<input type="checkbox"></br>

Game Related free Functions
FR9.1: Add left wall, right wall and pallde to the polygon rendering batch<input type="checkbox"></br>


Game Related frendering functions

Find out if therer is a way that any game object can be added to the polygon renderer based on a template functiomn rather than a function for each type

FR9.3: Render brick arrays<input type="checkbox"></br>
FR9.4: Render radial bricks<input type="checkbox"></br>
FR9.5: Render the polygon circle batch<input type="checkbox"></br>

Input Hardware related enums

FR0.0: A button can be in the state {Pressed, Down, Released, Up}<input type="checkbox"></br>


Input Hardware Related Struct declerations

FR0.2: Initialise the {Up, Left, Right, Down } Buttons to use the keys on the keyboard {W, A, S, D} With it's state as released<input type="checkbox"></br>
FR0.3: Update the Button State of the {Left, Right, Up, Down, Left Mouse, Right Mouse} Given wheter each of these buttons is pressed or not pressed<input type="checkbox"></br>

whether it is {pressed or not pressed} to {Pressed, Down, Released, Up} Where if a button is pressed or a button is released, this can only occur for a single frame<input type="checkbox"></br>


Input Hardware related member functions
FR6.5: Get additional states of the button, based on the properties that it walready has available e.g isPressed(), is pressed or Down<input type="checkbox"></br>


Input Hardware related free functions

FR6.4: Update the state of a button so that it is either {Up, Down, Pressed or Released}<input type="checkbox"></br>

--- ---
Free Functions related to inserting Verticies and indicies into the renderer

FR6.1: Add and arc to the Polygon renderer<input type="checkbox"></br>
FR6.2: Add a rectangle to the polygon renderer <input type="checkbox"></br>

-- Free functions related to loading game objects from am XML file format

FR7.0: Load Paddle from XML data<input type="checkbox"></br>
FR7.1: Load Ball from XML data<input type="checkbox"></br>


GUI Requirementd
FR6.7: Initialise Imgui<input type="checkbox"></br>
FR7.5: Initialise the editor window<input type="checkbox"></br>

FR8.1: Layout Dockspace panels to seperate the game window<input type="checkbox"></br>

-- Functions to get fixed size position vertex data of shapes
FR1.9: Get the verticies of a Rectangle<input type="checkbox"></br>


-- File IO related Requirements
FR0.4: Given a filename of a file that exists, retrieve the content of the file<input type="checkbox"></br>
- CRITERIA: assert a failure with an invalid filename
- CRITERIA: Check if the content retrieved from the file is exactly the same as what is in the file

FR0.9: Check if a file exists, given it's filename<input type="checkbox"></br>
- CRITERIA: return false if the file does not exist
- CRITERIA: return true if the files does exist

Initialisation Properties from constants
FR6.6: Initialise and SDLWindow of size 640, 480 using the opengl version 3.3<input type="checkbox"></br>


The Imperrative Flow Requiremnts
FR7.8: Step 1: Process SDL Events<input type="checkbox"></br>
End of frame: 
FR8.5: Update buttons after the end of a frame<input type="checkbox"></br>
FR9.6: Set frame to default frame after having rendered all other frame buffer related frames<input type="checkbox"></br>
FR9.10: When the program is finished, Free memory related to SDL2, ImGui and Opengl<input type="checkbox"></br>
FR8.8: resolve all physics operations that occurs between the time at the start of a frame and end of a frame<input type="checkbox"></br>


FR8.9: Switch rendering to frame buffer for rendering to a texture<input type="checkbox"></br>


Game User Requirements
FR7.9: Enable quitting the game<input type="checkbox"></br>


Editor User Requirements

FR10.1: When clicking on a radial Brick Group in the game scene
    Open the Radial Brick Group Editor
    Make the radial brick group selected
    Make the radial brick group movable<input type="checkbox"></br>

Object Selection Requirement

FR9.2: For each selected item, and a bounding box surrounding the object<input type="checkbox"></br>


Delegating SDL Events

FR0.6: Map An SDL event to one of the primary events<input type="checkbox"></br>

