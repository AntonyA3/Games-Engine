#include <test_abstractions.hpp>


void BasicSDLTest::initialise(){
     bool active = true;

    // The Window Dependancy
    SDL_Window * window; // An **allocated reference** to the SDLWindow object that created, **on creation**
    // A window must have a name
    std::string window_name = std::string("Test");
    // must have a width and height
    int width = 640;
    int height  = 480;
    if(SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    window = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
}

void BasicSDLTest::update(bool& active){
    // The Poll Event Dependancy
    SDL_Event event; // The current SDL event to process
    while (SDL_PollEvent(&event))
    {   
        switch (event.type)
        {
        case SDL_QUIT:
            active = false;
            break;
        } 
    }
}

void BasicSDLOpenGLTest::initialise(){
    if(SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    window = SDL_CreateWindow(this->window_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_SetWindowResizable(this->window, SDL_TRUE);
    SDL_SetWindowMinimumSize(this->window, this->width, this->height); // Set the window with tho current widht and height, which should be the same as the minimum
    if(window == NULL){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY); // This is required of the opengl versions are greater than or equal to 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, this->opengl_major_version); // GL version is a property
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, this->opengl_minor_version); // GL minor version us a property
    this->gl_context = SDL_GL_CreateContext(this->window);
    SDL_GL_SetSwapInterval(1);
    GLenum err = glewInit(); // Initialise glew

    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(1);
    }
    SDL_GL_MakeCurrent(this->window, this->gl_context);
}

void BasicSDLOpenGLTest::cleanup(){
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

TimeTicker::TimeTicker(Uint64 tick_time, Uint64 current_time){
    this->tick_time = tick_time;
    this->current_time = current_time;
    this->accumulated_time = 0;
}

bool TimeTicker::tick(){
    bool will_tick = this->accumulated_time >= this->tick_time;
    this->accumulated_time = (will_tick) ? this->accumulated_time - this->tick_time : this->accumulated_time;
    return will_tick; 
}

void TimeTicker::addTime(Uint64 new_time){
    Uint64 delta_time = new_time - this->current_time;
    this->accumulated_time += delta_time;
    this->current_time = new_time;
}

