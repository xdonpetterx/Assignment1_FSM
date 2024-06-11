#include "Locations/Locations.h"
#include "Characters/Agent.h"
#include "Characters/EntityNames.h"

#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    //Creates the main character and his friends
    Agent Charlie(ent_Agent_Charlie);
    Agent Friend_Elena(ent_Friend_Elena);
    Agent Friend_Jonny(ent_Friend_Jonny);
    Agent Friend_Mike(ent_Friend_Mike);

    for (int i=0; i<20; ++i)
    {
        Charlie.Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Friend_Elena.Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Friend_Jonny.Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Friend_Mike.Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }

    //wait for a keypress before exiting
    std::cin.get();

    return 0;
}