#pragma once

#include <iostream>
#include <cmath>


struct SMS
{
    //the entity that sent this SMS
    int          Sender;

    //the entity that is to receive this SMS
    int          Receiver;

    //the message itself. These are all enumerated in the file
    //"MessageTypes.h"
    int          Msg;

    //messages can be dispatched immediately or delayed for a specified amount
    //of time. If a delay is necessary this field is stamped with the time
    //the message should be dispatched.
    double       DispatchTime;

    //any additional information that may accompany the message
    void*        ExtraInfo;


    SMS():DispatchTime(-1),
               Sender(-1),
               Receiver(-1),
               Msg(-1)
    {}


    SMS(double time,
             int    sender,
             int    receiver,
             int    msg,
             void*  info = nullptr): DispatchTime(time),
                                  Sender(sender),
                                  Receiver(receiver),
                                  Msg(msg),
                                  ExtraInfo(info)
    {}

};


//these SMSs will be stored in a priority queue. Therefore the >
//operator needs to be overloaded so that the PQ can sort the SMSs
//by time priority. Note how the times must be smaller than
//SmallestDelay apart before two SMSs are considered unique.
const double SmallestDelay = 0.25;


inline bool operator==(const SMS& t1, const SMS& t2)
{
    return ( fabs(t1.DispatchTime-t2.DispatchTime) < SmallestDelay) &&
           (t1.Sender == t2.Sender)        &&
           (t1.Receiver == t2.Receiver)    &&
           (t1.Msg == t2.Msg);
}

inline bool operator<(const SMS& t1, const SMS& t2)
{
    if (t1 == t2)
    {
        return false;
    }

    else
    {
        return  (t1.DispatchTime < t2.DispatchTime);
    }
}

inline std::ostream& operator<<(std::ostream& os, const SMS& t)
{
    os << "time: " << t.DispatchTime << "  Sender: " << t.Sender
       << "   Receiver: " << t.Receiver << "   Msg: " << t.Msg;

    return os;
}

//handy helper function for dereferencing the ExtraInfo field of the SMS
//to the required type.
template <class T>
inline T DereferenceToType(void* p)
{
    return *(T*)(p);
}