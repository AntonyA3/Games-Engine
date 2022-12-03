
# Task 5 SDL Event Wrapper
## Summary

The aim of this task was to create an abstraction, useful for initialise a window using the SDL library.

## What I did
- I created an struct called SDLWindowWrapper and SDLWindowEvent
- The sample program open an SDL2 window, closed as an integrationTest
- I created a unit test to make sure that the Created window was never null;
# Analysis Implications
- I whill have to add the relationships between these new structs and classes
# Design Implications
 ![UML Subset](./Total%20System%20Design-Page-2.drawio.png) 


# Implementation Implications
- See source code
![SDLWindowWrapper Header](../../../../include/sdl_window_wrapper.hpp)
![SDLWindowWrapper Implementation](../../../../src/sdl_window_wrapper.cpp)
![SDLWindowEventWrapper Header](../../../../include/sdl_event_wrapper.hpp)
![SDLWindowEventWrapper Implementation](../../../../src/sdl_event_wrapper.cpp)
# Testing Implications

![The Unit Tests](../../../../tests/Unit/sdl_window_wrapper.test.cpp)
![The Integration Test](../../../../tests/SDL_Window_Wrapper)


# Maintenance Implications
- All unit tests must pass
- What needs to be tested is likely to change

# Next steps
- Work on the ImGui Abstraction