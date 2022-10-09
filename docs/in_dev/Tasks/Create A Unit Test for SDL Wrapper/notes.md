## 6 Create A Unit Test For SDLWindowWrapper 09/10/2022
 - SDL headers and library file object
 - An Initialising an SDL Window

## Summary
I will need to find what is testable in the SDLWindow abstraction, 
it is presumed that the abstraction is likely to have been implemented correctly
As the risk of there being hidden errors is low.
Check for errors, if they are small fix them as part of this task, if they are major,
Fix them as part of a new task
Then commit these changes


## What I did or will do
I will
- Add Libcester to the project library folder
- Create a test file for the SDL Window Wrapper
- Create a makefile to build a test by name
- I have decided to seperate the unit tests from the source folder, as they actually require a seperate executable
- Therefore in tests I will create a unit test file for each testable component


# Analysis Implications
 - None
# Implementation Implications
 - Check for errors

# Testing Implications
    - The Window Should be active after initialisation 
    - Window should be inactive before initialisation
    - The window should be inactive after it has been terminated

![The Path of the libcester library](../../../../vendors/libcester-0.4/)
![Test File](../../../../tests/Unit/sdl_window_wrapper.test.cpp)

# Maintenance Implications
 - These tests may change as new functionality is added or decoupled

# Evaluation
- This took longer than Ideal as There was a bug because I forgot to define SDL_MAIN_HEADER, I decided to make sure that it is defined in any SDL related abstraction, in order to prevent similar error from ever occuring.