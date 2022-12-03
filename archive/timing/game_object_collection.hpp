#ifndef GAMES_ENGINE_GAME_OBJECT_COLLECTION
#define GAMES_ENGINE_GAME_OBJECT_COLLECTION

template <typename GameObject>
struct GameObjectCollection : public std::vector<GameObject>, public IGameObject{
    GameObject * target;
    bool contains(glm::vec2 point){
        for(GameObject& object: *this){
            if(object.contains(point)){
                target = &object;
                break;
            }
        }
    }

    void move(glm::vec2 movement){
        target->move(movement);
    }

    template <typename TRenderer>
    void renderControl(TRenderer& renderer){
      
    }

    template <typename TInput>
    void inputControl(TInput& input){

    }
};
#endif