
# SDL Window Wrapper 

## Summary 
An abstraction to encapsulate the initial properties related to an SDL window and the continuous properties related to an SDL_Window

| Property | Description |
| --- | --- |
| m_window | An **allocated reference** to the SDLWindow object that created, **on creation** |
| m_active | To store whether the window is **currently** active |
| m_x_position_flag | To store the flag of the SDL_Window's x position **on initialisation** |
| m_x_position_flag | To store the flag of the SDL_Window's y position **on initialisation** |
| m_initial_width |  To store the width of the window **on initialisation** |
| m_initial_height | To store the height of the window **on initialisation** |
| m_resizable | To determine whether the window will be resizable **on initialisation** |
| m_width | To store the **current** width of the window |
| m_height | To store the **current**  height of the Window |

|Function | Description |
| --- | --- |
| Create | Given the properties of **this**<br> And **this** window property is null <br> **initilise** window <br> **set** window to resizable <br> Then **this** window should not be null <br> And **this** window should be visible on the *screen*|
| Terminate | Set **this** to inactive |
| Destroy | Destroy **this** window |
| IsActive | Return whether **this** is active |




