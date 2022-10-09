

#include <sdl_window_wrapper.hpp>

#include <SDL2/SDL.h>
#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
struct SampleOpenGLWrapper{
    int m_gl_major_version = 3;
    int m_gl_minor_version = 3;
    SDL_GLContext m_gl_context;
    SDL_Renderer * m_renderer;

    SampleOpenGLWrapper(){
        this->m_gl_major_version = 3;
        this->m_gl_minor_version = 3;
    }

    void create(SDL_Window * window){
        std::cout << "Initialising open gl" << std::endl;
        // [Notes] - This is required for higher version or opengl
        if (m_gl_major_version > 3 || (m_gl_major_version == 3 && m_gl_minor_version >= 3))
        {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, m_gl_major_version); // GL version is a property
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, m_gl_minor_version); // GL minor version us a property
        
        m_gl_context = SDL_GL_CreateContext(window);
        SDL_GL_SetSwapInterval(1);

        m_renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_GL_MakeCurrent(window, m_gl_context);

        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
            exit(1);
        }
    }
};


struct NewSDLWindowWrapper {

    SDL_Window * m_window;
    SDLEventWrapper m_sdl_event_wrapper;
    SampleOpenGLWrapper m_sample_wrapper;
    bool m_active;
    Uint32 m_init_flags;
    std::string m_title;
    int m_width;
    int m_height;
    int m_x_position_flag;
    int m_y_position_flag;
    SDL_bool m_resizable;
public:
    NewSDLWindowWrapper();
    ~NewSDLWindowWrapper();
    void create();
    void terminate();
    void destroyAndQuit();
    bool isActive();
    bool polledEvent();
    SDL_Event& nextEvent();
};


NewSDLWindowWrapper::NewSDLWindowWrapper(/* args */)
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
    
}

NewSDLWindowWrapper::~NewSDLWindowWrapper()
{


}

void NewSDLWindowWrapper::create(){
    if( SDL_Init( m_init_flags ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    //Create window
    m_window = SDL_CreateWindow(m_title.c_str(), m_x_position_flag, m_y_position_flag, m_width, m_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    SDL_SetWindowResizable(m_window, m_resizable);
    if( m_window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }    
    this->m_sample_wrapper.create(this->m_window);
    m_active = true;
}

void NewSDLWindowWrapper::terminate(){
    m_active = false;
}

void NewSDLWindowWrapper::destroyAndQuit(){
    SDL_DestroyWindow( m_window );
    SDL_Quit();
}

bool NewSDLWindowWrapper::isActive(){
    return m_active;
}

bool NewSDLWindowWrapper::polledEvent(){
    return m_sdl_event_wrapper.polledEvent();
}

SDL_Event& NewSDLWindowWrapper::nextEvent(){
    return m_sdl_event_wrapper.nextEvent();
}



int main(int argc, char const *argv[])
{
    NewSDLWindowWrapper window_wrapper;
    window_wrapper.create();


   
    while (window_wrapper.isActive())
    {
        while (window_wrapper.polledEvent())
        {
            SDL_Event& event  = window_wrapper.nextEvent();
            if(event.type == SDL_QUIT){
                window_wrapper.terminate();
            }
            /* code */
        }

        glViewport(0.0f, 0.0f, 640, 480);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_GL_SwapWindow(window_wrapper.m_window);

        
        /* code */
    }
    
    window_wrapper.destroyAndQuit();

    return 0;
}
