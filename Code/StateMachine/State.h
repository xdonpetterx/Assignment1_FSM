#pragma once

struct Telegram;

template <class entity_type>
class State
{
public:

    virtual ~State()= default;

    virtual void Enter(entity_type*)=0;

    virtual void Execute(entity_type*)=0;

    virtual void Exit(entity_type*)=0;

    //this executes if the agent receives a message from the
    //message dispatcher
    virtual bool OnMessage(entity_type*, const Telegram&)=0;
};