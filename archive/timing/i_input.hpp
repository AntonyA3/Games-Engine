#ifndef GAMES_ENGINE_I_INPUT
#define GAMES_ENGINE_I_INPUT
struct IInput{
    virtual bool leftPressedOrDown() = 0;
    virtual bool rightPressedOrDown() = 0;
    virtual bool pausePressed() = 0;
};
#endif