Requirements
- A user can Change the window size with the pulleys
- A user can move the Paddle using the A key of the keyboard, inside the game this will affect the game
- A player can move the paddle using the right key


Program Construction Guide


Program needs a new ImGui Frame and an End ImGui Frame in the window and swap window buffer: **Done**
need to clear the frame: **Done**

Have a global function designed to alway show the demo window this must be after begin frame but before end frame and assigned before main: **Done**

since the window is resizable I need to assign the width and height as default width and height : **Done**


Create an inspector window between imgui begin and imgui end to show the width and the height of the current window value, expect this to match the default until the ability to track the window size has properly been implemented, make the names of the imgui text the same ad the variable name seperate the value eith colones: **Done**



tHEN CREATE A width and height variable, Check if this matches the new width and height only after resizinfg has been detected

Resizing a window can be detected with SDL2 within the map to base event function, 
- create a new enum value in base event for the window resize base event: **Done**
- find the conditions to detect a resize in map event use a cout statement to verify that window resize events are being detected: **Done**
- try setting the base event to window resize event, though this partically complets the task, I can veriify that the windoe even check is correct: **Done**
- SDLEvent should be passed in by reference rather than copied: **Done**
- Finish this by setting th base even to window resize if the internal window SDL Event is a resize event: **Done**


Prepend all base events with Base event to prevent future name conflicts: **Done**

Now I need to update the size of the width and height based on only if the event is a windoe resize event
- However I do not want to have to have a reference to the width and height as a parametre for map to base event, as this would mean that all base events that modify state would need a parametre, which would make some parametres unnessessary : **Done**

remove the function map to base event, instead copy the functionality to line 103 after ImGui_ImplSDL2_ProcessEvent: **Done**

Create a variable that stores the base event and use it inside the switch statement: **Done**

In the case statement add another case for the resize event: **Done**

When that case occurs updae the variable width and the variable height based on this: **Done**

The current height and the current width affects the glViewport: **Done**

Remove the old makeBaseEventFunction: **Done**

The gl background color is black but must be stored in top scope
- Include glm headers: **Done**
- make Color type a synonym of vec4 after Button State Enum: **Done**
- the background color should be stored in a Color variable : **Done**
- before app loop et the background color to grey: **Done**
- Create a constant for the color gray at the top of main: **Done**

- The backgtound color at line 89 is equal to the grey constant: **Done**

- Move th clearColor function call from line 114 to  line 89 + 1: **Done**
- call clear color with the background color: **Done**

At the Top of the file prepare some comments for contents: **Done**

Move glViewport from line 117 to lines (112 + 1, line 92 + 1): **Done**

Remove comments: **Done**

Add a global variable called  render_matrix, this will be used for rendering this is defined after backgtound color: **Done**


File Reading
- include filestram after string stream include : **Done**

- declare readfile ater color is defined and also readfile implementation followed by this: **Done**
- Test whether a copy of this function works within the circumstances I need it in a read file test file: **Done**


A player can move the paddle using the left key
- I need a variable to state of the left button: **Done**
- A variable to store the key that is assigned to the left button: **Done**
- Declare update button after read file implement it after read file implementation: **Done**
- I need to be able to update the left button state based on the previous logic for updating a button. This can occur before Beginning a new imgui frame,  I can create a function to update the button to a new button state Given whether the button is down and it's current state: **Done**

It will match this Table when implemented
| State | is Down | New state |
| --- | --- | --- |
| ButtonState_Pressed | true | ButtonState_Down |
| ButtonState_Down | true | ButtonState_Down |
| ButtonState_Up | true | ButtonState_Pressed |
| ButtonState_Released | true | ButtonState_Pressed |
| ButtonState_Pressed | false | ButtonState_Released |
| ButtonState_Down | false | ButtonState_Released |
| ButtonState_Up | false | ButtonState_Up |
| ButtonState_Released | false | ButtonState_Up |

Actually test all these to fit this table after implementation in a seperate file: **Done**

Button state convertable to a string in test: **Done**

boolean convertable to a string in test: **Done**

Button state convertable to a string in game insert after update button: **Done**

boolean convertable to a string in game insert after update button: **Done**



Actually check if the button actually updates in an imgui window by finding the previous state of the button. If there is a new button state print the button.
Temporarily store the previous left button state and if the previous button state is diffent then print the new button state life "Left Button: ButtonState": **Done**

I also need to add the right button state and the right button scancode: **Done**
- a right button Scancode 
- a right button state
- for each button state update the button state in the same way that the left button has been updated
- expect to semantically compress this

The semantic compression of the : **Done**
- (left button scancode, left button state)
- (right button scancode, right button state)

Based on the semantics it might be better to have a: **Done**
 - concrete type that contains the Scancode and the button state called Button: **Done**
 - The button should be crated after Button State containing the scancode and button state: **Done**
 - The scancode should be received through a constructor, but the button state will be set to Up in the constructor: **Done**
 - implement the constructor after the Button has been initialised: **Done**
 - include the vector: **Done**
- create the references for lft button scancode, right button scancode, left button state, right button state: **Done**
- Update the buttons by iterating through the buttons: **Done**
- It might be easier to identify the Buttons with an enum: **Done**


I don't need to peint the button name, but I will need to eventually detect the change event of a button, this should occur within update: **Done**

Print a button 
- There is another to String method for button, so at line 51 declare a button toString operation, in the cpp file after buttonState implement the toString function :
It should look like this exactly
Button: {
    state_change: boolean_value,
    tag: string_value,
    scancode: scancode_to_string
    button_state: button_state_to_string
}
 **Done**
- it depends on the toString for bool for state change: **Done**
- the tag can be easily printed: **Done**
- the state can be printed based on the toString for button state: **Done**
- Check whether scancode has a toString method, if it doesn't then create my own toString method, There is a way to get the scancode name but I will need to get the name , then print it: **Done**
- Test this in a file that just prints an example button called button_to_string.impl.test: **Done**
- I forgot to add the & from button reference in the implementation file so test again: **Done**
- But it spat out random results so try to see if it works without the tostring method: **Done**
- I noticed that I printed the string rather than returne the string, Therefore replace std::cout with the sstring stream insertion and create a temporary variable for a stringstream return the string, then build and run teh test fire again: **Done**
- It works: **Done**



Adding change detection within a button and the tag within a button
- In a button there is a new bool for change
- There is a tag that is a string for storing it's name
- The updatButton and it's decleration will be renamed to updatebuttonstate
- the updateButton function will now update the entire button with a void return but with a mutation, it depends on the updateButtonState Function therefore declare this after this function
- Update Buttonrequires that the keyboardstate be a parametre
- before the button state is changed, the new button state will be retrieved by the updateButton function
- the value of the button change is equal to whether the new button state is equl to the old buttonState
- The button tag will be set in the constructor which means I need to change the Constructor decleration and implementation and call
- Test whther the button update is correct by
Test for the change and the tag after updating the button later use the working tostring method: **Done**
- Rename function updateButton to updateButtonState in the integration test: **Done**
- rename update_button_test to update_button_state_test


**Refactoring Task**: Make a hpp file that represents the main file with all headers and a cpp file for all the implementations of whats' in the headers, so that they can be used by any of the testing related executables
- With git create a checkpoint: **Done**
- file called 
breakout_engine.hpp: **Done**
    - Needs all headers
    - Base Event 
    - Button State
    - Button
    - Color
    - read file decleration
    - update button staate decleration
    - update button decleration
    - toString bool decleration
    - to stringButton Decelration
    - always show demo decleration
- Comment out all the structs and declerations: **Done**
- Insert the header file: **Done**
- If the program compiles then this has been done correctly, otherwise the changes must be reverted, or the makefile must be changed so that the header file is in a valid folder:  **Done**
- Remove all unnessessary comments: **Done**

**Refactor Task**: Move all functions other than main to breakout engine.cpp
- create a checkpoint to mark that I have created the header file but I am about to move functions to breakout_engine.cpp : **Done**
- create a breakout_engine.cpp file which includes breakout engine.hpp file : **Done**
- comment out and copy all functions other than main to the file, while maintaing the order that the functions were written: **Done**
- Test if the program still works after this, if not it might be a problem with the makefile: **Done**
- I found an error  with the function signature that was implemented therefore in the updateButtonFunction in breakout_game.hpp I need to add the parametre const Uint8 * keyboard_state: **Done**
- Test again if the program still works after this, if not it might be a problem with the makefile: **Done**

**Isolate the SDL Sequence loop for testing purposes



*Test Design: For the integration of button changed and button tag*
update_button_test
Dependancies: SDL Headers included

Button_State , Button : UpdateButton, UpdateButtonState, toString(bool), toString(ButtonState), SDL keyboard state,

Sequence Dependancies: The SDL Update loop
- Make checkpoint: **Done**
- In there is a section at line 11 For the Window
- Line 39 to initialise SDL in video mode
- Line 42 for initialising the window
- Line 52 for swap interval
- Line 79-80 Polling the SDL Event
- Line 85 Process the Quit Event

Maybe there should be an abstraction for testing with minimum viable SDL2 the problem is that this abstraction would be leaky in other circumstances.
Therefore
- Create a header file for objects that are only useful for testing: **Done**
- There should be a cpp object that goes with this as well: **Done**
- There should be a function for create BasicSDLTest (But with comments that notify the leaks in the abstraction): **Done**
- This abstraction could be stored in an Object a member of a class called BasicSDLTest **Done**
    - Initialising the window with a width of 640 height of 480 and window name of Test
    - The update function for polling events and quitting the program with the input for the active variable
    - The test setup should work: **Done**
- Test the update button Function: **Done**
- Since the test is dependant on events that happens many times per second, it would be too fast to measure: How about I create a small system to delay something within a faster loop:
for example do something every second within a loop that happend every 1/60th of a second:  **Done**
    -  I will need to store a value for accumulated time for time, as an unsigned int, this variable will increase until until 1000 milliseconds
    - And I will need to store the current time
    - I then get the new time at the end of the frame and the diffrence between the new time and the current time, should be added to the deltatime.
    - There is an if statement to chech if the accumulated time is over 1000 (therefore one second has elapsed), if it is then the button is printed then Updated and the accumulated time is subtrated by a second
    - Considers how I would formalise these ideas for later usage


Inputs: Button(Scancode: SDL_Scancode_A, Tag: "test key") where the default state is up
Action: (Update with A button Down)
Expected Output: Expect 



**A New Task**: Within the context of the Button Object button states can be expanded into multiple boolean values, for when the change of the state of something within the loop relies on the button state because only one button state can occur at a time for a button it is based on a predicate
| Action | States |
| --- | --- |
| pressed | ButtonState_Pressed |
| down | ButtonState_Down |
| pressedOrDown | ButtonState_Pressed OR ButtonState_Down |
| released | ButtonState_Released |
| up | ButtonState_Up |
| releasedOrUp | ButtonState_Released OR ButtonState_Up |
| flippling | ButtonState_Pressed OR ButtonState_Released |

**A Refactor Task**: 
- Make a checkpoint
The function updateButton and updateButtonState should be renamed to update in both the header file and implementation file, also change any instances of this in the update_button_state test and update_button_test 
 the executables: breakout_game_2.impl.exe**Done**, update_button_test **Done**, update_button_state_test is able to run this has been complete
- The update Function for button state's decleraration should match the implementation: **Done**
- The update function in updateButtonState no longer has a toString method to show a psuedo truth table, create this method at the top of the file**Done**.
- Update Button_state_test uses it's own implementation of the function so it failed to compile Remove the implementations,
and test if the executable: update_button_state_test works as intended**Done**.
- End Checkpoint: **Done**.


**Potential Task**: A function for printing a truth table

**A New Task**:  In the breakout Game and Engine, the user can use the Cursor to interract with things: 
- The current position of the mouse should be known
- The mouse's delta position, how much the user has moved the mouse in the frame
- They are operated on together so these properties can be combined into an object
- The mouse would need to be able to be converted to a string for testing purposes:

**Implementation**
- After button define a struct called Cursor, it will have the variables position and delta, with the types glm::vec2(integers): **Done**
- declare an updateFunction that takes the cursor as an input: **Done**
-Mark a checkpoint if I have to revert to this then delete the class for cursor and the update cursor decleration: **Done**
- Withtin the update function implementation get the new Cursor position, then calculate the Cursor delta, then set the Cursor position to the new 
value: **Done**
- A to String method for glm::ivec2 before Button toString **Done**
- A to String method for Cursor after Button tostring **Done**


**Testing**: 
- test that the toString(glm::ivec2) method returns the expected output. The output should look like this: **Done**

[x: x, y: y] 
- test that the toString(Cursor) method returns the expected output. The output should look like this**Done**
<code>

    Cursor: {</br>
    &nbsp;position: [x: pos_x, y: pos_y]</br>
    &nbsp;delta: [x: x, y: y]</br>
    }</br>
</code>

- Formalise the method of delaying an update, the first place this will be implemented is update_button_test.impl.cpp, call it TimeTicker
**Done**
    - This should be put in test abstractions since it is not yet needed in the game. then tested again **Done**
- The Cursor is 0 initialised:  therefore add constructor to decleration file and implement it after Button implementations in the cpp file **Done**
- Test that the Cursor Constructor is zero initialised: **Done**
- Test that a Cursor can update in an SDL environment,  this works by creating a console application using the basic SDL setup, every second the Cursor should be updated, this will display the current position of the Cursor and the delta of the Cursor: **Done**

Remove Compiler Warnings at breakout_engine lines 28 and 78: **Done**
I changed the update button state function retest to verify correctness **Done**



***I should be able to relie on the checkpoint that is created at the end of each task, rather than create one at the beginning***

**A Refactor Task**: 
Align the function declerations with their implementation order: **Done**
    - Button constructor
    - Cursor Constructor
    - readfile
    - update(ButtonState)
    - update(Button)
    - update(Cursor)
    - toString(bool)
    - toString(ButtonState)
    - toString(ivec2)
    - toString(Button)
    - toString(Cursor)
    - alwaysShowDemo
- Test this by running the breakout_game_2 file, since it incorporated most of the functionality of the breakoutengine: **Done**

**Requirement**: Given a context for rendering, such as a rendering context that is 640 x 480 pixels, it should be possible of a user to see objects on the screen.
- Using openGL the drawable entities must be stored in a vertex, and an index.

**Rendering Epic**


| Order | Task |
| --- | --- |
| 1 | In the breakout engine create a function that will convert the matrix to an orthographic matrix given the screen height and the screen width **Test:** THe orthographic matrix function is able to create a matrix that will convert opengl coordinates to screen coordinate 

**Design**
Expect this matrix when given an orthographic matric for a  640 by 480 screen

NotThis below
| | | | |
| --- | --- | --- | --- |
| 320 | 0 | 0 | 0 |</br>
| 0 | 240 | 0 | 0 |</br>
| 0 | 0 | 0 | 0 |</br>
| 320 | 240 | 0 | 0 |</br>

But this is what it looks like in column matrix order
| | | | |
| --- | --- | --- | --- |
| 0.003125 | 0 | 0 | 0 |</br>
| 0 | -0.004167  | 0 | 0 |</br>
| 0 | 0 | -1 | 0 |</br>
| -1 | 1 | 0 | 1 |</br>

0.003125 = 1/320
-0.004167 = -1/240 because the y axis is flipped

-1, 1 in the last row makes sure that after scaling the 640 x 480 to a window in an area starting at [x: 0, y: 0] [x: 2, y: -2] the position of the window is translated to [x: -1, y: -1] [x: 1, y: 1]

**Implementation**
- In breakout engine.hpp create a function for transform(Matrix) immediately after readfile **Done**
- In breakout engine.cpp implement this **Done**
- Test this in transform_matrix.impl.cpp and check if this matrix is returned when given the width 640 and given the height 480 **Done**

| Task |
| --- |
| **Done** |
| Every time that the width and height of the screen changes in breakout game, the render matrix must be changed, including at initialisation | 
|**Implementation**:  checkpoint the previous task of transform function, then at line 74 & line 95 use the transform function on the render matrix: **Done** (Changes applied at line 75 and line 97)|
**Testing**: Verify this within the imgui insepector window act about line 117 ImGui::Text call for height create an imgui text called render matrix*, the matrix should change aalong with the width and height of the window. **Done**: (A new task will be created to improve the format by creating my own matrix to String method, a checkpoint is made) |




| Task |
| --- |
| **Done** |
| Rename transform as it is doesn't explain what the function does well enough |
| **Implementation**: Search for all transform implementations and declerations, then rename it to update, in only cpp an hpp files, add some comments above to explain what is does **Done** |
| **Testing**: Expect the matrix to update correctly, therefore no logic change in the breakout_game_2 executable **Done** |


| Task |
| --- |
| Integrating Cursor into BreakoutGame 2 **Done**|
| **Implementation**: At line 23 create a cursor variable **Done**, at line 111 update the cursor **Done**, at line 122 call a to string for the cursor position **Done**, at line 123 call a to_string method for the cursor delta **Done**
| **Testing** :Check whether the cursor updates are displayed in the imgui window for position and delta **Done**
Display the mouse position in the imgui windoe **Done**|


Task

---

Create a data type called mesh, this will store a vertex_buffer and an index_buffer  on Initialisation, these objects should be created, test this by verifying that these properties are not 0 **ToDo**

--- 

**Sub Requirement**

The exact datatype for a vertex buffer object or index buffer object should be *GLuint*

Before testing find out the minimum required functionality to create a mesh within the mesh_constructor_test file**ToDo**

---

**Implementation**

In breakout engine hpp after Cursor, declare struct Mesh with a varible of type GLuint for vertex_buffer and index_buffer both of types GLuint and declare an Constructor **Done**

In breakout engine cpp after all implementation of Cursor functions implement the Mesh Constructor **Done**

In the breakout game 2 make sure that the Mesh is constructed after line 61 as this is after openGL initialised call it polygon_batch_mesh **Done** (at line 62)

Create a file for testing the mesh constructor **Done**

By trial and error find the test dependancies of the Mesh **Done**


For testing create a function or a class to encapsulate the test dependancies for testing a Mesh. in test_abstractions.hpp call it BasicSDLOpenGLTest, it only needs an initialise and cleanup function to be declared **Done**

Include OpenGl into test_abstraction.hpp **Done**

Implement the initialise and clean up function in test_abstactions implementation file after BasicsSDLTest implementations **Done**

Implement the BasicOpenGLSDL test absttraction in the mesh test **Done**
Check whether the mesh_constructor_test works **Done**

Add then make a commit **ToDo**

Basic SDL test needs a function for cleanup aswell **ToDO**


Update the comments int test abstraction header **ToDo**

Add cleanup function in all tiles that use BasicSDLTest for testing
**Todo**

BasicSDLTest to BasicSDLApplicationLoopTest, for better naming **ToDo**

Create a to string function for the mesh **ToDo**

Implement this in test_abstractions.cpp **ToDo**

**Testing**

In a seperate executable test if the Mesh Constructor initialises the Mesh buffers to an non zero value **ToDo**








| Task |
| --- |
| In breakout engine include the string related functions for glm::mat4, see if it doesn't cause errors **Done** |


| Task |
| --- |
| A shader does not need to be stored, but there needs to be a function to compile the shader based on the shader text content called make shader **ToDo** |

| Task |
| --- |
| The polygon shader text content had two files, the vertex shader and the fragment shader **ToDo** |

| Task |
| --- |
| The verticies should have a matrix that scale the objects to be viewed on a screen that matches the current width and current height of the screen.  **Done** |

| Task |
| --- |
| It should be possible to make a shader when just given the filename,  given the filename it is possible to read the shader content from the file, then make the shader  **ToDo** |

- Checking whether the shader compiled successfully is a seperate function that will be used to test whether the shader has been written correctly **ToDo**
- Create a datatype called polygon renderer, it should have a variable for the program with a default value of 0 **ToDo**

**A New Task**:  Needs to see things within the game/editor
- Most objects should be rendered as polygons
- A shader is required, which is plain text that is able to be interpreted by graphics hardware with openGL support
- A mesh has a vertex buffer and an index buffer
**Implementation**

**A new Task**: Formalise the idea of ticks that happen between the frames.

**A new Task:** I will expect to have a test abstraction that would include Work for An SDL Test that requires both SDL and ImGui with OpenGl

