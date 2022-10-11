#include <sdl_window_wrapper.hpp>

SDLWindowWrapper::SDLWindowWrapper(/* args */)
{
    m_window = NULL;
    m_active = false;
    m_init_flags = SDL_INIT_VIDEO;
    m_title = std::string("Sample Title");
    m_width = 640;
    m_height = 480;
    m_x_position_flag = SDL_WINDOWPOS_CENTERED;
    m_y_position_flag = SDL_WINDOWPOS_CENTERED;
    m_resizable = SDL_TRUE;
    m_other_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    m_color.r = 0.5f;
    m_color.g = 0.5f;
    m_color.b = 0.5f;
    m_color.a = 1.0f;
    setColor(m_color.r, m_color.g, m_color.b, m_color.a);
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
    setColor(m_color.r, m_color.g, m_color.b, m_color.a);   
}


void SDLWindowWrapper::setDimensions(int width, int height){
    m_width = width;
    m_height = height;
}

void SDLWindowWrapper::setColor(float r ,float g, float b, float a){
    m_color.r = r;
    m_color.g = g;
    m_color.b = b;
    m_color.a = a;
    glClearColor(r, g, b, a);

}

int SDLWindowWrapper::getWidth(){
    return m_width;
}

int SDLWindowWrapper::getHeight(){
    return m_height;
}

void SDLWindowWrapper::clear(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    SDL_Event& event = m_sdl_event_wrapper.nextEvent();
    return event;
}

SDL_Window *& SDLWindowWrapper::getWindow(){
    return m_window;
}


