#pragma once

#include <string>
//---------MESSAGING------
#include <Messaging/SMS.h>
//---------MESSAGING------

class BaseGameEntity
{

private:

    //every entity must have a unique identifying number
    int          m_ID{};

    //this is the next valid ID. Each time a BaseGameEntity is instantiated
    //this value is updated
    static int  m_iNextValidID;

    //this must be called within the constructor to make sure the ID is set
    //correctly. It verifies that the value passed to the method is greater
    //or equal to the next valid ID, before setting the ID and incrementing
    //the next valid ID
    void SetID(int val);

public:

    explicit BaseGameEntity(int id)
    {
        SetID(id);
    }

    virtual ~BaseGameEntity()= default;

    //all entities must implement an update function
    virtual void  Update()=0;

    //----------MESSAGING---------
    //all entities can communicate using messages. They are sent
    //using the MessageDispatcher singleton class
    virtual bool  HandleMessage(const SMS& msg)=0;
    //----------MESSAGING---------

    [[nodiscard]] int           ID()const{return m_ID;}
};