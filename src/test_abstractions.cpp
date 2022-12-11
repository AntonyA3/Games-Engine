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

