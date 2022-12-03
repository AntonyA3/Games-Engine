#include <SDL2/SDL.h>
#include <limits>

class TimeController
{
private:
    float delta_time;
    Uint64 time;
public:
    TimeController();
    TimeController(Uint64 time);

    Uint64 getTime();
    float getDeltaTime();
    void update();
    void create();


    //Only useful for Unit Testing
    void create(Uint64 time);
    void update(Uint64 new_time);

};

