#pragma once

#include <string>

enum
{
    ent_Agent_Charlie,

    ent_Friend_Elena,

    ent_Friend_Jonny,

    ent_Friend_Mike
};

inline std::string GetNameOfEntity(int n)
{
    switch(n)
    {
        case ent_Agent_Charlie:

            return "Agent Charlie";

        case ent_Friend_Elena:

            return "Friend Elena";

        case ent_Friend_Jonny:

            return "Friend Jonny";

        case ent_Friend_Mike:

            return "Friend Mike";

        default:

            return "UNKNOWN!";
    }
}