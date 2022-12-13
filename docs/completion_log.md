A user is able to change the window size

An ImGui Frame is displayed

There is a function to always show the demo window

There is an inspector window to display some information

The width and height of the window is kept up to date with the window size

The application is able to detect window size changes as part of the SDL event loop

Can store the background color so that it can be used while running

The color has been assigned so that the color is grey by default

There is a constant for the color grey

glViewport is updated everytime that the window size changes


The render matrix is updated along with the width and the height

A file can be read given a file name

Can convert a keypress boolean to 4 keystates of pressed, down, released or up 

I can update a keyboard button.

Can convert a button state to a string

Can convert a boolean to a string

Every frame a button is updated so that the state is changed

Created a button struct to abstract the key scancode and the key

Can print the button struct

Added a variable called tag to the button, to store a custom name for printing

Seperated the program into breakout_engine.hpp and breakout_engine.cpp

Created an abstration for testing parts of the application that require SDL

Create an abstraction for testing parts of the application that occur at time intervals

Tested the button update 

Implmented a cursor so that a user can move the cursor to a diffrent position and gwt how much it was moved by in the frame

Created then renamed the transform function to update, for updating the matrix every time it is required


Created a function to update the matrix to be used every time the width or height of the window changes

Integrated the cursor into the breakout game

Created the mesh datatype

Created an abstration for testing parts of the application that require SDL with OpenGL as well