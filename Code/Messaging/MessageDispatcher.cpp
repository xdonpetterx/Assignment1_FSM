#include <Characters/EntityNames.h>
#include <Locations/Locations.h>
#include <Messaging/MessageDispatcher.h>
#include <Messaging/CrudeTimer.h>
#include <Messaging/EntityManager.h>
#include <Messaging/MessageTypes.h>
#include <Messaging/SMS.h>
#include <StateMachine/BaseGameEntity.h>

#include <iostream>
using std::set;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//------------------------------ Instance -------------------------------------

MessageDispatcher* MessageDispatcher::Instance()
{
    static MessageDispatcher instance;

    return &instance;
}


//----------------------------- Dispatch ---------------------------------
//
//  see description in header
//------------------------------------------------------------------------
void MessageDispatcher::Discharge(BaseGameEntity *pReceiver, const SMS &msg) {
    if (!pReceiver->HandleMessage(SMS()))
    {
        //SMS could not be handled
        std::cout << "Message not handled";
    }
}

//---------------------------- DispatchMessages ---------------------------
//
//  given a message, a receiver, a sender and any time delay , this function
//  routes the message to the correct agent (if no delay) or stores
//  in the message queue to be dispatched at the correct time
//------------------------------------------------------------------------
void MessageDispatcher::DispatchMessages(double  delay,
                                        int    sender,
                                        int    receiver,
                                        int    msg,
                                        void*  ExtraInfo)
{
#ifdef _WIN32
    //SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
#endif

    //get pointers to the sender and receiver
    BaseGameEntity* pSender   = EntityMgr->GetEntityFromID(sender);
    BaseGameEntity* pReceiver = EntityMgr->GetEntityFromID(receiver);

    //make sure the receiver is valid
    if (pSender == nullptr)
    {
        std::cout << "\nWarning! No Sender with ID of " << sender << " found";

        return;
    }

    //make sure the receiver is valid
    if (pReceiver == nullptr)
    {
        std::cout << "\nWarning! No Receiver with ID of " << receiver << " found";

        return;
    }

    //create the SMS
    SMS SMS(0, sender, receiver, msg, ExtraInfo);

    //if there is no delay, route SMS immediately
    if (delay <= 0.0f)
    {
        std::cout << "\nInstant SMS dispatched at time: " << Clock->GetCurrentTime()
             << " by " << GetNameOfEntity(pSender->ID()) << " for " << GetNameOfEntity(pReceiver->ID())
             << ". Msg is "<< MsgToStr(msg);

        //send the SMS to the recipient
        Discharge(pReceiver, SMS);
    }

        //else calculate the time when the SMS should be dispatched
    else
    {
        double CurrentTime = Clock->GetCurrentTime();

        SMS.DispatchTime = CurrentTime + delay;

        //and put it in the queue
        PriorityQ.insert(SMS);

        std::cout << "\nDelayed SMS from " << GetNameOfEntity(pSender->ID()) << " recorded at time "
             << Clock->GetCurrentTime() << " for " << GetNameOfEntity(pReceiver->ID())
             << ". Msg is "<< MsgToStr(msg);

    }
}


//---------------------- DispatchDelayedMessages -------------------------
//
//  This function dispatches any SMSs with a timestamp that has
//  expired. Any dispatched SMSs are removed from the queue
//------------------------------------------------------------------------
void MessageDispatcher::DispatchDelayedMessages()
{
#ifdef _WIN32
    //SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
#endif

    //get current time
    double CurrentTime = Clock->GetCurrentTime();

    //now peek at the queue to see if any SMSs need dispatching.
    //remove all SMSs from the front of the queue that have gone
    //past their sell by date
    while( !PriorityQ.empty() &&
           (PriorityQ.begin()->DispatchTime < CurrentTime) &&
           (PriorityQ.begin()->DispatchTime > 0) )
    {
        //read the SMS from the front of the queue
        const SMS& SMS = *PriorityQ.begin();

        //find the recipient
        BaseGameEntity* pReceiver = EntityMgr->GetEntityFromID(SMS.Receiver);

        std::cout << "\nQueued SMS ready for dispatch: Sent to "
             << GetNameOfEntity(pReceiver->ID()) << ". Msg is " << MsgToStr(SMS.Msg);

        //send the SMS to the recipient
        Discharge(pReceiver, SMS);

        //remove it from the queue
        PriorityQ.erase(PriorityQ.begin());
    }
}



