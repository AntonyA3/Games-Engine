#include <sdl_window_wrapper.hpp>

SDLWindowWrapper::SDLWindowWrapper(/* args */)
{
    m_window = NULL;
    m_active = false;
    m_init_flags = SDL_INIT_VIDEO;
    m_title = std::string("Sample Title");
    m_initial_width = 640;
    m_initial_height = 480;
    m_width = 640;
    m_height = 480;
    m_x_position_flag = SDL_WINDOWPOS_CENTERED;
    m_y_position_flag = SDL_WINDOWPOS_CENTERED;
    m_resizable = SDL_TRUE;
    m_other_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    setDimensions(m_width, m_height);
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
    m_window = SDL_CreateWindow(m_title.c_str(), m_x_position_flag, m_y_position_flag, m_width, m_height, m_other_flags);
    SDL_SetWindowResizable(m_window, m_resizable);
    if( m_window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }    
    m_active = true;
}


void SDLWindowWrapper::setDimensions(int width, int height){
    m_width = width;
    m_height = height;
}


int SDLWindowWrapper::getWidth(){
    return m_width;
}

int SDLWindowWrapper::getHeight(){
    return m_height;
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

