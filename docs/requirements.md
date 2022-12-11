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
Test for the change and the tag after updating the button later: **Todo**
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
- create a checkpoint to mark that I have created the header file but I am about to move functions to breakout_engine.cpp
- create a breakout_engine.cpp file which includes breakout engine.hpp file
- comment out and copy all functions other than main to the file, while maintaing the order that the functions were written
- Test if the program still works after this, if not it might be a problem with the makefile


*Test Design: For the integration of button changed and button tag*
update_button_test
Dependancies: SDL Headers included

Button_State copy, Button Copy: Update Button Functions, UpdateButtonState toString(bool) toString(ButtonState)

Inputs: Button(Scancode: SDL_Scancode_A, Tag: "test key") where the default state is up
Action: (Update with A button Down)
Expected Output: Expect 