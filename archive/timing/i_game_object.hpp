#ifndef GAMES_ENGINE_I_GAME_OBJECT
#define GAMES_ENGINE_I_GAME_OBJECT

class IGameObject
{
    protected:
    IGameObject(){}
    public:
    void update(float dt){}
    template <typename TRenderer>
    void renderControl(TRenderer& renderer){}
    template <typename TInput>
    void inputControl(TInput& input){}
    template <typename IAudio>
    void audioControl(IAudio& audio){}
};
#endif