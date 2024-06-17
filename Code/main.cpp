#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <thread>

#include <Characters/Agent.h>
#include <Characters/EntityNames.h>
#include <Messaging/EntityManager.h>
#include <Messaging/MessageDispatcher.h>


int main()
{
    //seed random number generator
    srand((unsigned) time(nullptr));

    //Creates the main character and his friends
    auto* Charlie = new Agent(ent_Agent_Charlie);
    auto* Friend_Elena = new Agent(ent_Friend_Elena);
    auto* Friend_Jonny = new Agent(ent_Friend_Jonny);
    auto* Friend_Mike = new Agent(ent_Friend_Mike);

    //register them with the entity manager
    EntityMgr->RegisterEntity(Charlie);
    EntityMgr->RegisterEntity(Friend_Elena);
    EntityMgr->RegisterEntity(Friend_Jonny);
    EntityMgr->RegisterEntity(Friend_Mike);

    for (int i=0; i<20; ++i)
    {
        Charlie->Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Friend_Elena->Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Friend_Jonny->Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Friend_Mike->Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        //dispatch any delayed messages
        Dispatch->DispatchDelayedMessages();
    }

    //wait for a keypress before exiting
    std::cin.get();

    return 0;
}