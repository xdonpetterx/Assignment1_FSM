#pragma once

#include <string>

enum message_type
{
    Msg_WhatsUp,
    Msg_VideoGames,
};


inline std::string MsgToStr(int msg)
{
    switch (msg)
    {
        case Msg_WhatsUp:

            return "WhatsUp?";

        case Msg_VideoGames:

            return "Play videogames?";

        default:

            return "Not recognized!";
    }
}