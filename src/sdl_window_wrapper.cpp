#include <sdl_window_wrapper.hpp>

SDLWindowWrapper::SDLWindowWrapper(/* args */)
{
    m_window = NULL;
    m_active = true;
    m_init_flags = SDL_INIT_VIDEO;
    m_title = std::string("Sample Title");
    m_width = 640;
    m_height = 480;
    m_x_position_flag = SDL_WINDOWPOS_CENTERED;
    m_y_position_flag = SDL_WINDOWPOS_CENTERED;
    m_resizable = SDL_TRUE;
}

SDLWindowWrapper::~SDLWindowWrapper()
{


}

void SDLWindowWrapper::create(){
    
    if( SDL_Init( m_init_flags ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    //Create window
    m_window = SDL_CreateWindow(m_title.c_str(), m_x_position_flag, m_y_position_flag, m_width, m_height, SDL_WINDOW_SHOWN );
    SDL_SetWindowResizable(m_window, m_resizable);
    if( m_window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }    
    m_active = true;
}

void SDLWindowWrapper::terminate(){
    m_active = false;
}

void SDLWindowWrapper::destroyAndQuit(){
    SDL_DestroyWindow( m_window );
    SDL_Quit();
}

bool SDLWindowWrapper::isActive(){
    return m_active;
}

bool SDLWindowWrapper::polledEvent(){
    return m_sdl_event_wrapper.polledEvent();
}

SDL_Event& SDLWindowWrapper::nextEvent(){
    return m_sdl_event_wrapper.nextEvent();
}

