*The lower in the document the more granular the requirement*
## Introduction 
As part of the overall business goals of creating fun games, and advanced systems that are useful for engineers. I will be creating a game with 2D graphics that is similar to the game breakout. This game has a ball, a paddle and bricks, that can be destroyed. When they are destroyed you the Player earns some points. When the ball goes below the paddle floor then you lose one of the ball, and if you lose all the balls, then you lose the game. To make the game more exiting Powerups that can be used to double the amount of balls in play or have malls that are able to go through bricks rather than bounce of bricks. Attempt to achieve the ideals of the game within the hardware environments and software environments that this game will work within.



#### Special Requirement Tokens

BEGIN: Large requirements are marked with BEGIN: as a dependancy when begining all the sub requirrement

END: Large requirements are marked with END: as a dependancy when ending all the sub requirrement

DESCRIPTION: A larger requirement will have a description

REMOVE: A requirement that is being removed

CONTRADICTION: An requirement that should be removed as it contradicts with a more important requirement

MISSING DEPENDANCY: For ant requirement with a missing dependancy


ARCHIVE: A requirement that is being removed, but is still useful to remember
## Release Requirements

#### Application Standards Requirement
APR0: A Working Editor to create levels and menues for a breakout style game
- Criteria:
APR0: The game must have a suitable name
- Criteria: Survey potential players of the game in order to find an desirable name of the game
APR1: The Text that is the window name must match the Name of the Game
- CRITERIA: Check if the Window Title Matches the name of the Game "Breakout"
APR2: A Breakout Style Game with multiple levels.

APR3: I will be using prototypical inheritance via dependancy injection so that data that can be iterated can be stored in an array, rather than multiple iterations on similar types with the same functionality
#### Developer & User Hardware Requirements
HR0: A standard laptop or computer keyboard that is either part of the computer or external to the computer<input type="checkbox"></br>
HR1: Requires a mouse or a touchpad to interract with the game and it's editor on a 2d device<input type="checkbox"></br>
HR2: Mouse/Touchpad needs A left button to select an activate thing on a screen<input type="checkbox"></br>
HR3: Mouse/Touchpad needs a right button to select an activate thing on a screen<<input type="checkbox"></br>
HR4: Graphics Processor that supports openGL 3.3<input type="checkbox"></br>
HR5: Performance to utilise the processor in a way that would allow logic to be updated 60 times per second to take inputs and update the logic of the game, in a way that would provide satisfactory gameplay or editorfunctionality for thre user<input type="checkbox"></br>
HR6: Enough memory to run additional software on top of the operating system<input type="checkbox"></br>



#### Editor User Requirements
UR0.1: When the User pressed the X Button on the window, the window should be closed and the program should be finished
- Criteria: The Window closes when X is pressed<input type="checkbox"></br>

UR0.2: If the user Paddle has been clicked on, while the user is holding down the left mouse button The Paddle can be move to any position between the left wall and the right wall, When the user released the mouse the Paddle should still be selected but not moving to change the location of the paddle in the scene

UR0.3 If the user changes a edits a property in the radial brick editor the radial brick that is being edited should be changed 
UR0.4 The user should be able to set the point were the ball will initially be at the start of a game level
UR0.5 The user should be able to set where the Paddle will be at the beginning of a game level
UR0.6 When Editing a brick array, the user should be able to rotate the entire array.
FR0.7: The Background color is initially gray<input type="checkbox"></br>
FR0.8: Create scenes that can be used to generate levels within the game
ER0.9: Tools for modifying bricks within a radial pattern in the game<input type="checkbox"></br>
ER0.10: Each selectable item has a selecttion box

#### Game Rules/Requirements
GR0.0: A Ball has a position<input type="checkbox"></br>
GR0.1: A Paddle has a position<input type="checkbox"></br>
GR0.2: A LeftWall has a x position<input type="checkbox"></br>
GR0.3: A RightWall has a x position<input type="checkbox"></br>

GR0.4: When the Paddle hits the left wall, the paddle should stop<input type="checkbox"></br>
GR0.5: When the Paddle hits the right wall the paddle should stop<input type="checkbox"></br>
GR0.6: When a ball hits a left wall, the Ball should bounce off the left wall with it's velocity reflecting along the x axis<input type="checkbox"></br>
GR0.7: When a ball hits a right wall, the Ball should bounce off the right wall with it's velocity reflecting along the x axis<input type="checkbox"></br>
GR0.8: Get 10 points for every brick destroyed<input type="checkbox"></br>

#### Software Dependancy Requirements

SR0.0: A desktop Operating System<input type="checkbox"></br>
SR0.1: Include SDL2 Headers<input type="checkbox"></br>
SR0.2: Include OpenGL headers<input type="checkbox"></br>
SR0.3: to retrieve input information from the operating system (Parent SR0)<input type="checkbox"></br>
SR0.4: to generate a Windows desktop style window (Parent SR0)<input type="checkbox"></br>
SR0.5: create an opengl context (Parent SR0)<input type="checkbox"></br>
SR0.6: get the position of the mouse relative to the window (Parent SR0)<input type="checkbox"></br>
SR0.7: determine whether the left mouse button is down or up: (Parent SR0)<input type="checkbox"></br>
SR0.8: Determine whether the right mouse button is down or up: (Parent SR0)<input type="checkbox"></br>
SR0.9: determine whether the keyboard buttons {Initially WASD} is down or up (Parent SR0)<input type="checkbox"></br>
SR0.10: glm headers To have access to the matrix data structure And to be able to multiply matrixies with vectors<input type="checkbox"></br>
SR0.11: Rapid XML<input type="checkbox"></br>
SR0.12: Serialise editor data<input type="checkbox"></br>
SR0.13 Include iostream to have access c++ file based input output functionality<input type="checkbox"></br>



#### Editor Functional Requirements
ER0.2: Brick Array Editor has a
| property | description |
| --- | --- |
| position | to represent the position of it's centre in 2d space |
| column count | |
| row count | |
<input type="checkbox"></br>


ER0.2: Brick Radial Editor has a 
| property | description |
| --- | --- |
| position | |
| layer count | |
| brick layer editors | |

#### C++ Negative Rules
R:0.0: c++ strings cannot be wrapped in '' but must be wrapped with ""


ER0.1: An ImGui frame from start to from start to finish for gui rendering<input type="checkbox"></br>
ER0.4: An editor for an array of bricks<input type="checkbox"></br>
ER0.5: Allow some objects to be selected<input type="checkbox"></br>
ER0.6: Allow some objects to be moved<input type="checkbox"></br>
ER0.7: Asset Window<input type="checkbox"></br>
ER0.8: Scene Window<input type="checkbox"></br>
ER0.9: The user can paste radial brick groups into the game<input type="checkbox"></br>
ER0.10: The game is renderered as an image in the Viewport Window<input type="checkbox"></br>
ER0.11: The minimum size of the Window is 640, 480<input type="checkbox"></br>
ER0.12: Initialise the SDL window to the 640 by 480 if there is no ini file
Otherwise initialise the SDL window to the size specificed (Parent SR0)<input type="checkbox"></br>
ER0.13 The user can paste an array brick group into the game<input type="checkbox"></br>



#### File Structure Requirement
FSR 0: All code snippets are stored in a folder called snippet
FSR 1: All files of code snippets end with the extension .template.cpp

#### Paradigm Requirements
PR 1: Member functions should require no additional dependancies
PR 2: Member functions can have parametres if it contains a type that already exists within the class

#### Console App Template Requirements CR.n
CATR 0: console_app template is stored in folder called code snippet
CATR 1: console_app template ends with .template.cpp
CATR 2: console_app has a main function for execution
CATR 3: The console_app will exit when given an exit text as a command
CATR 4: the exit command will set the active variable to false this will end the application loop
CATR 5: All console_app has access to the iostream
CATR 6: All console_app has access to the string
CATR 7: The console app will have a comment to tell you were to insert code
CATR 8: A named console app can be generated with a single command'
CATR 9: This will run a program to insert the nessessary data into the console app.


#### Gui App Template Requirements GR.n
GATR 1: gui_app template is stored in a folder called code snippet
GATR 2: gui_app has a main function for execution
GATR 3: gui_app uses ImGui
GATR 4: gui_app template ends with .template.cpp


FDR0.2.1: When command reads an input, the word 'exit' will terminate the console program

FDR0.0: There is a template file for console applications
FDR0.0: Integration tests that only require the console window should be able to be created with a single command
FDR0.1: In thegenerated source code, there should be comments based on what has been input into the commands
FDR0.2: There should be a command that will automatically generate the boiler plate that is required to create an application with an SDL2 Window and An ImGui Frame
FDR0.3:
#### Functional Requirements
All functional requirements are in the order ofimplementation

Key: Requirement_ID : d_Dependancy0_ID,

#### FIOD: BEGIN: File Input Output Declerations**<input type="checkbox"></br>

#### FIOD: END: File Input Output Declerations**<input type="checkbox"></br>


#### FIOI: BEGIN: File Input Output Implementation**<input type="checkbox"></br>

#### FIOI: END: File Input Output Implementation**<input type="checkbox"></br>


#### 2DGS: BEGIN: 2D Geometric Structs**<input type="checkbox"></br>
2DGS: DESCRIPTION: This section is identified 2D Geometric functions 

2DGS 0: A Linear Res is an object that is used to return the results of a linear based operation.</br>

2DGS 0: A Quadratic is an object that is used to return the results of a quadratic based operation.</br>

2DGS 1:  A quadratic object has an int called solution set to 0, 1, or 2 solutions for a quadratic equation.<input type="checkbox"></br>

2DGS 2: A quadritic object has 2 floats to represent the solution<input type="checkbox"></br>

2DGS 3: The first float represents the first numerical solution<input type="checkbox"></br>

2DGS 4: The second float represnts the second numerical solution<input type="checkbox"></br>

2DGS 5: If there is only one solution to a quadritic equation, then the first float and the second float is set to the solution.<input type="checkbox"></br>

2DGS 6: It has a function to get the maximum of it's own two float values<input type="checkbox"></br>

2DGS 7: When trying to get the maximum of the two values if there is no solution the assert a failure<input type="checkbox"></br>

2DGS 8: Can get the minimum of the two values only if there are two solutions<input type="checkbox"></br>

2DGS 9: A Rect is an object that represents a rectangle<input type="checkbox"></br>

2DGS 10: A Rect has a position<input type="checkbox"></br>

2DGS 11: A Rect has a size<input type="checkbox"></br>

2DGS 12: the size cannot be negative<input type="checkbox"></br>

2DGS 13: By default a rect is at position (0, 0) with size (1 , 1)<input type="checkbox"></br>

2DGS 14: Check if program asserts a failure in debug mode when trying to set the size of a rectangle to 0<input type="checkbox"></br></br>

2DGS 15: Can be initialised with a position and a size<input type="checkbox"></br>

2DGS 16: A Circle is an object that represents a circle has a position and a radius<input type="checkbox"></br>

2DGS 17: Radius cannot be negative

2DGS 18: By default it is at position (0, 0) with radius of 1

2DGS 19: A Capsule has a position a radius and a direction<input type="checkbox"></br>

2DGS 20: Radius cannot be negative<input type="checkbox"></br>

2DGS 21: By default it is at position (0, 0) the radius is 1 and the direction is (1, 1)<input type="checkbox"></br>

2DGS 22: A Polygon has one to many verticies in an anticlockwise order<input type="checkbox"></br>

2DGS 23: An Ellipse has a position and a size<input type="checkbox"></br>

2DGS 24: An Edge has a start point and an end point<input type="checkbox"></br>

2DGS 25: The starft point cannot be equal to the end point

2DGS 26: A Slice has a position, radius a start angle in radians, an end angle in radians

2DGS 27: The size of an Ellipse cannot be negative

2DGS 28: An arc has a position, start_radius, end_radius, start angle, end angle

2DGS 29: Assert that the start radius must be less than the end radius

2DGS 30: This assertion will crash a program if it is invalid
| case | status |
| --- | --- |
| start: 10 end: 11 | is valid |
| start: 10 end: 10 (boundary) | invalid |
| start: 11 end: 10 | invalid |

2DGS 31: A sweeped rect has a start point, a half height and a direction

2DGS 32: A ShapeGroup has a position, an array of rectangles and an array of circles
<!-- CONSTRAINT: 0 to many of each shape -->

2DGS 33: An Entity has a 2D position and velocity No longer exists, however The information needs to be remembered

**2DGS: END: 2D Geometric Structs**</br>

**MFGS 0: BEGIN: Member Functions of Geometric Structs**</br>
MFGS 1: The maximum of the two values of a QuadraticRes 'quadratic result'
MFGS 2: The minimum of the two values of a QuadraticRes 'quadratic result'

**MFGS: End: Member Functions of Geometric Structs**</br>

**FFGD: BEGIN: Geometric Free Functions Decleration**</br>
FFGS 0: A rectangle can be checked for if a point is inside it

FFGS 1: A capsule can be checked for if a point is inside it

FFGS 2: A polygon can be checked for if a point is inside it

FFGS 2: 2 rectangles can be combined as a geometric union

**FFGD: END: Geometric Free Functions Decleration**</br>

**FFGI 0: BEGIN: Geometric Free Functions Implementation**</br>
FFGI 1: Given a rectangle and a point check if the point is in the rectangle<input type="checkbox"></br>

FRGI 2: Given a Polygon and a point check if it contains a point<input type="checkbox"></br>

FRGI 2: Given 2 rectangles and an output rectanfle, join this rectangle into a single rectangle that is the geometric union of both rectangles<input type="checkbox"></br>

**FFGI 0: END: Geometric Free Functions Implementation**</br>

FR0.12.1(Temporary): All properties and functions in entity must be moved to Paddles to maintain it's functionality but to remove entity Both Decleration and Implementation
FR0.12.2(Temporary): All properties and functions in entity must be moved to Ball to maintain it's functionality but to remove entity Both Decleration and Implementation


FR 0.13: REMOVE: ARCHIVE: The RectVerticies had 3d vectors of top_left, top_right_bottom_left_ bottom_right 

TEST: Given that the rectangle is renderered correctly and the mouse position in the window is accurate, Use the mouse position to check whether it is inside the rects at various points on the screen <input type="checkbox"></br>


FR0.0 The verticies of a Polygon are relative to the origin in the local polygon space so that the whole polygon can be moved, by just moving it's position


FR0.0: Any Object Or with a position that has no objects with a position property can be moved with a single function

IMPLICATION: Implied A circle can be moved as it has a position<input type="checkbox"></br>

IMPLICATION: Implied A rectangle can be moved as it has a position<input type="checkbox"></br>

IMPLICATION: Implied A capsule can be moved as it has a position<input type="checkbox"></br>

IMPLICATION: Implied A capsule can be moved as it has a position<input type="checkbox"></br>

IMPLICATION: Implied A polygon can be moved as it has a position<input type="checkbox"></br>

IMPLICATION: Implied All previous examples can be verified to be working graphicaly<input type="checkbox"></br>



**SR: BEGIN: Sized Object Template Functions**</br>

SR0.0 For any Sized object with the property size it is possible to get its's width
<!-- - CRITERIA: This applies to an elipses -->
<!-- - CRITERIA: This applies to a rect -->

SR0.0 For any Sized object with the property size it is possible to get its's height
<!-- - CRITERIA: This applies to an elipses -->
<!-- - CRITERIA: This applies to a rect -->

**SR: END: Sized Object Template Functions**</br>

**GLTD: BEGIN: GL Utils Decleration**</br>
GLTD 1: It is possible to make a shader program Given the vertex shader file and the fragment shader file#

GLTD 2: It is possible to create a make a shader program from the raw vertex shader texT content and fragment shader text content

GLTD 3: It is possible to make a shader when given its text file and the GLenum for either a fragment shader of a vertex shader type

GLTD 4: It is possible to make a shader when given the shader content and the shader type

GLTD 5: It is possible make the program after linking the program when given the vertex shader and the fragment shader
**GLTD: END: GL Utils Declearation**</br>

**GLTD: BEGIN: GL Utils Implementation**</br>
GLTI 1: GLTD 1: GLTD 5: A Shader program is made with a vertex shader and a fragment shader that is linked to a sshader program 

GLTI 2: GLTD 2: GLTD 5: A Shader program is made with a vertex shader and a fragment shader that is linked to a sshader program

GLTI 3: GLTD 2: MISSING DEPENDANCY: A shader program can be made from reading the content from a text file then using this 

GLTI 4: MISSING DEPENDANCY: A shader is made by Compiling a shader Then returning the shader after checking whether it compiled successfull.

GLTI 5: A program can be made by Attaching the two shaders, linking the program checking the success of linking then deleting the shader
**GLTD: END: GL Utils Implementation**</br>

**IND: BEGIN: Intersector Decleration**</br>
IND 1: It is possible to check if two rectangles intersect each other

IND 2: It is possible to check if a circle intersects a rectangle

IND 3: It is possible to check if a circle intersects a polygon

IND 4: It is possible to check if a polygon intersects a polygon

IND 5: It is posible to check if a capsule intersects a rect

IND 6: It is possible to check if a polygon intersects a rect

**IND: END: Intersector Decleration**</br>

**INI: BEGIN: Intersector Implementation**</br>
INI 1: Given a two rects, determine whether they intersect each other by determining whether they intersect along the x axis and intersect along the y axis.

INI 2: Given a circle and a rect, the rectangle can be converted to a polygon so that it is possible to change this to a circle intersects polygon function.

INI 3: It is possible to check is a polygon intersects a circle by checking if each edge has a point that is inside a circle.

INI 4: It is possible to check if a polygon intersects a polygon by checking whether each polygon intersects the other polygons edges.

INI 5: It is possible to check is a polygon intersects a polygon edge by using the seperate axis therorem

INI 6: It is possible to check whether a capsule intersect rect, by checking if a capsule intersects the start and end circle of the capsule or it's polygon.

**INI: END: Intersector Implementation**</br>

**EMD: BEGIN: Extra Math Deceleration**</br>
**EMD: END: Extra Math Deceleration**</br>

**EMD: BEGIN: Extra Math Implementation**</br>
**EMD: END: Extra Math Implementation**</br>

**TRS: BEGIN: Time Related Structs**</br>


**TRS: END: Time Related Structs**</br>

**TRS: BEGIN: Time Related Member Functions**</br>


**TRS: END: Time Related Member Functions**</br>


**TRFF: BEGIN: Time Related Free Function Declerations**</br>


**TRFF: END: Time Related Free Function Declerations**</br>

**TRTFI: BEGIN: Time Related Template Function Implementations**</br>


**TRTFI: END: Time Related Free Template Function Implementations**</br>

**BSOTF: BEGIN: Boxed Circle Object Template Functions**</br>
BSOTF 1: If an object only has a radius and a position one can get the top as a float
BSOTF 2: If an object only has a radius and a position one can get the bottom as a float
BSOTF 3: If an object only has a radius and a position one can get the left as a float
BSOTF 4: If an object only has a radius and a position one can get the right as a float
BSOTF 5: This should not be able to box a capsule

BSOTF 6: If an object only has a radius and a position one can get the topPoint as a 2D vector

BSOTF 7: If an object only has a radius and a position one can get the bottomPoint as a 2D vector

BSOTF 8: If an object only has a radius and a position one can get the leftPoint as a 2D vector

BSOTF 9: If an object only has a radius and a position one can get the rightPoint as a 2D vector

BSOTF 10: This should not be able to box a capsule
**BSOTF: END: Boxed Circle Object Template Functions**</br>

**BOTF: BEGIN: Boxed Object Template Functions**</br>
BOTF 1: You can create any boxed object given a position and a size

BOTF 2: You can get the top of any BoxedObject with only a position and a size property

BOTF 3: This implies this is true for Elipses Boxed Objects

BOTF 4: This implies is true for a Rect

BOTF 5 You can get the bottom of any BoxedObject with only a position and a size property
<!-- - CRITERIA: This applies to an elipses -->
<!-- - CRITERIA: This applies to a rect -->

BOTF 6: You can get the left of any BoxedObject with only a position and a size property
<!-- - CRITERIA: This applies to an elipses -->
<!-- - CRITERIA: This applies to a rect -->

BOTF 7: You can get the right of any BoxedObject with only a position and a size property
<!-- - CRITERIA: This applies to an elipses
- CRITERIA: This applies to a rect -->

BOTF 8: You can get the topLeft of any BoxedObject with only a position and a size property
<!-- - CRITERIA: This applies to an elipses
- CRITERIA: This applies to a rect -->

BOTF 9: You can get the bottomLeft of any BoxedObject with only a position and a size property
<!-- - CRITERIA: This applies to an elipses
- CRITERIA: This applies to a rect -->

BOTF 10: You can get the topRight of any BoxedObject with only a position and a size property
<!-- - CRITERIA: This applies to an elipses
- CRITERIA: This applies to a rect -->

BOTF 11: You can get the bottomRight of any BoxedObject with only a position and a size property
<!-- - CRITERIA: This applies to an elipses
- CRITERIA: This applies to a rect -->

BOTF 12: You can get the centre of any BoxedObject with only a position and a size property
<!-- - CRITERIA: This applies to an elipses
- CRITERIA: This applies to a rect -->

**BR: END: Boxed Object Template**</br>

**MTF: BEGIN: Move Template Functions**</br>
DESCRIPTION: For moving objects with properties like a position, rather than move semantics

MTF 1: Any Movable object has a vector 2 called position it's position can be moved when given a movement

MTF 2: Any Movable object has a vector called position and it can be moved when given a velocity and a delta time

MTF 3: Any Velocity Movable object has the properties of position and velocity, it can be moved when only ther time is given

**MTF: END: Move Template Functions**</br>



**RSD: BEGIN: Renderer Struct Declearations**</br>

**RSD: END: Renderer Struct Declearations**</br>

**RMF: BEGIN: Renderer Member Functions**</br>

**RMF: END: Renderer Member Functions**</br>


**RFFD: BEGIN: Renderer Free Function Decleration**</br>

**RFFD: END: Renderer Free Function Decleration**</br>


**RFFD: BEGIN: Renderer Free Function Implementation**</br>

**RFFD: END: Renderer Free Function Implementation**</br>









FR2.3: Projecting a point to the line. Given a point on a line , the line normal, and a point away from the line, find the distance between the point and the line <input type="checkbox"></br>
FR2.4: Clamping a point on a line and  the start of the line and the end of the line
if the point is greater than the end of the line, clamp the point to the end
If the point is less than the start of the line, clamp the point to thre beginning<input type="checkbox"></br>
FR2.5: From a sweeped rect create an equivalent polygon<input type="checkbox"></br>
FR2.6: Check if a rectangle intersects a line<input type="checkbox"></br>
FR2.7: Given a point on a line find where it is based on the relative point on a line between 0.0f, and 1.0f if the point is on the line<input type="checkbox"></br>
FR2.8: Given a list of points, and a vector, find the point that is furthest along the vector<input type="checkbox"></br>
FR2.9: Given a list of points find the point that is further in the opposite direction of the vector<input type="checkbox"></br>


**Memory Layout**

1. A boolean for whether the application is active
2. 
3. A pointer to the SDL Window
4. A pointer to the SDL GL Context

