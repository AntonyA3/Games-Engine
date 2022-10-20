#include <sdl_window_wrapper.hpp>

SDLWindowWrapper::SDLWindowWrapper(/* args */)
{
    m_window = NULL;
    m_active = false;
}

SDLWindowWrapper::~SDLWindowWrapper()
{

}


void SDLWindowWrapper::create(SDLWindowData& sdl_window_data){
    
    if( SDL_Init( sdl_window_data.init_flags ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    //Create window
    int shown_flag = (sdl_window_data.window_shown) ? SDL_WINDOW_SHOWN : 0;
    int open_gl_flag = (sdl_window_data.open_gl_active) ? SDL_WINDOW_OPENGL : 0;
    m_window = SDL_CreateWindow(
        sdl_window_data.title.c_str(), 
        sdl_window_data.x_position_flag, 
        sdl_window_data.y_position_flag, 
        sdl_window_data.width, 
        sdl_window_data.height, 
        shown_flag | open_gl_flag
    );
    SDL_SetWindowResizable(m_window, sdl_window_data.resizable);
    if( m_window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }    

    m_active = true;
    m_width = sdl_window_data.width;
    m_height = sdl_window_data.height;
}


void SDLWindowWrapper::terminate(){
    m_active = false;
}

void SDLWindowWrapper::destroy(){
    SDL_DestroyWindow(m_window);
}

bool SDLWindowWrapper::isActive(){
    return m_active;
}

SDL_Window *& SDLWindowWrapper::getWindow(){
    return m_window;
}


