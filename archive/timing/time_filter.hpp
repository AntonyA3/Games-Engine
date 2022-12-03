#ifndef GAMES_ENGINE_TIME_FILTER
#define GAMES_ENGINE_TIME_FILTER
#include <SDL2/SDL.h>
template<typename ValueType>
struct TimeFilter
{
    ValueType value;
    Uint64 time, m_filter_duration;
    void create(Uint64 filter_duration);
    void update(ValueType new_value, Uint64 new_time);
    ValueType getValue();
};

template<typename ValueType>
void TimeFilter<ValueType>::create(Uint64 filter_duration){
    m_filter_duration = filter_duration;
}

template<typename ValueType>
void TimeFilter<ValueType>::update(ValueType new_value, Uint64 new_time){
    bool pred = abs((int)(new_time - time)) >= m_filter_duration;
    value = (pred) ? new_value : value;
    time = (pred) ? new_time : time;
}

template<typename ValueType>
ValueType TimeFilter<ValueType>::getValue(){
    return value;
}

#endif