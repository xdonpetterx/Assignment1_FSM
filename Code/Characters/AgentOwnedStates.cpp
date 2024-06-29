#include <Characters/Agent.h>
#include <Characters/AgentOwnedStates.h>
#include <Characters/EntityNames.h>
#include <Characters/Personalities.h>
#include <Locations/Locations.h>
#include <Messaging/CrudeTimer.h>
#include <Messaging/MessageDispatcher.h>
#include <Messaging/MessageTypes.h>
#include <Messaging/SMS.h>

#include <iostream>
#include <map>
#include <thread>

WORD setColor(Agent* pAgent)
{
    WORD COLOR;
    if (GetNameOfEntity(pAgent->ID()) == "Agent Charlie"){COLOR = BLUE;}
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Elena"){COLOR = RED;}
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Jonny"){COLOR = GREEN;}
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Mike"){COLOR = YELLOW;}
    else{COLOR = RESET;}
    return COLOR;
}

//--------------------------------------methods for Working
Working* Working::Instance()
{
    static Working instance;
    return &instance;
}

void Working::Enter(Agent* pAgent)
{
    std::multimap<std::string, std::string> RANDOMWORK, WORK1, WORK2;
    switch (RandomInteger(0, 1)) {
        case 0:
            RANDOMWORK = WORK1;
            break;
        case 1:
            RANDOMWORK = WORK2;
            break;
    }

    /*The best fix is probably to change the workplace here and in Personalities.h get the agent location*/
    if ((GetNameOfEntity(pAgent->ID()) == "Agent Charlie") and (pAgent->Location()) != (charlieMcDonalds or charlieCoalMine))
    {
        if (RANDOMWORK == WORK1 )
            pAgent->ChangeLocation(charlieMcDonalds); //TODO: Needs to change to one of the two workplaces
        if (RANDOMWORK == WORK2 )
            pAgent->ChangeLocation(charlieCoalMine); //TODO: Needs to change to one of the two workplaces
    }
    if ((GetNameOfEntity(pAgent->ID()) == "Friend Elena") and (pAgent->Location()) != (elenaPowerPlant or elenaChemicalFactory))
    {
        if (RANDOMWORK == WORK1 )
            pAgent->ChangeLocation(elenaPowerPlant); //TODO: Needs to change to one of the two workplaces
        if (RANDOMWORK == WORK2 )
            pAgent->ChangeLocation(elenaChemicalFactory); //TODO: Needs to change to one of the two workplaces
    }
    if ((GetNameOfEntity(pAgent->ID()) == "Friend Jonny") and (pAgent->Location()) != (jonnyCarFactory or jonnyHospital))
    {
        if (RANDOMWORK == WORK1 )
            pAgent->ChangeLocation(jonnyHospital); //TODO: Needs to change to one of the two workplaces
        if (RANDOMWORK == WORK2 )
            pAgent->ChangeLocation(jonnyCarFactory); //TODO: Needs to change to one of the two workplaces
    }
    if ((GetNameOfEntity(pAgent->ID()) == "Friend Mike") and (pAgent->Location()) != (mikePizzeria or mikePrison))
    {
        if (RANDOMWORK == WORK1 )
            pAgent->ChangeLocation(mikePizzeria); //TODO: Needs to change to one of the two workplaces
        if (RANDOMWORK == WORK2 )
            pAgent->ChangeLocation(jonnyCarFactory); //TODO: Needs to change to one of the two workplaces
    }
    WORD COLOR = setColor(pAgent);
    std::multimap<std::string, std::string> WORK = setWork(pAgent);
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, COLOR);
    std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << WORK.find("enterWork")->second;
    SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
    << WORK.find("enterWork")->second << pAgent->Location() << RESET;
#endif
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}


void Working::Execute(Agent* pAgent)
{
    //if the Agent is at the workplace he works for money until he
    //is carrying in excess of MaxCash. If he gets thirsty during
    //his work he packs up work for a while and changes state to
    //go to the Bar for a something to drink.
    pAgent->AddToCashCarried(1);

    pAgent->IncreaseFatigue();

    WORD COLOR = setColor(pAgent);
    std::multimap<std::string, std::string> WORK = setWork(pAgent);
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << WORK.find("working")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
    << WORK.find("working")->second << RESET;
#endif

    //if enough cash earned, go and put it in the Bank
    if (pAgent->PocketsFull())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(VisitBankAndDepositCash::Instance());
    }

    else if (pAgent->Thirsty())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(QuenchThirst::Instance());
    }

    else if (pAgent->Hungry())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(ReduceHunger::Instance());
    }

    else if (pAgent->Bored())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(ReduceBoredom::Instance());
    }

    else if (pAgent->KeenOnBuying())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(BuyStuff::Instance());
    }
    else if (pAgent->Fatigued())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(GoHomeAndSleep::Instance());
    }
}


void Working::Exit(Agent* pAgent)
{
    WORD COLOR = setColor(pAgent);
    std::multimap<std::string, std::string> WORK = setWork(pAgent);
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": "
             << WORK.find("exitWork")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
    << WORK.find("exitWork")->second << RESET;
#endif
}

bool Working::OnMessage(Agent* pAgent, const SMS& msg)
{
    //send msg to global message handler
    return false;
}

//----------------------------------------methods for VisitBankAndDepositCash

VisitBankAndDepositCash* VisitBankAndDepositCash::Instance()
{
    static VisitBankAndDepositCash instance;

    return &instance;
}

void VisitBankAndDepositCash::Enter(Agent* pAgent)
{
    //on entry the Agent makes sure he is located at the Bank
    if (pAgent->Location() != Bank)
    {
        WORD COLOR = setColor(pAgent);
        std::multimap<std::string, std::string> DEPOSIT = depositCash(pAgent);
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << DEPOSIT.find("enterBank")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
        << DEPOSIT.find("enterBank")->second << RESET;
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->ChangeLocation(Bank);
    }
}


void VisitBankAndDepositCash::Execute(Agent* pAgent)
{
    //deposit the gold
    pAgent->AddToWealth(pAgent->CashCarried());

    pAgent->SetCashCarried(0);

    WORD COLOR = setColor(pAgent);
    std::multimap<std::string, std::string> DEPOSIT = depositCash(pAgent);
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": "
        << DEPOSIT.find("depositing")->second << pAgent->Wealth();
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
    << DEPOSIT.find("depositing")->second << pAgent->Wealth() << RESET;
#endif

    //wealthy enough to have a well earned rest?
    if (pAgent->Wealth() >= ComfortLevel)
    {
        WORD COLOR = setColor(pAgent);
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": "
             << DEPOSIT.find("ifRichEnough")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
             << DEPOSIT.find("ifRichEnough")->second << RESET;
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(GoHomeAndSleep::Instance());
    }

        //otherwise get more cash
    else
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(Working::Instance());
    }

}


void VisitBankAndDepositCash::Exit(Agent* pAgent)
{
    WORD COLOR = setColor(pAgent);
    std::multimap<std::string, std::string> DEPOSIT = depositCash(pAgent);
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << DEPOSIT.find("ifRichEnough")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
    << DEPOSIT.find("exitBank")->second << RESET;
#endif
}

bool VisitBankAndDepositCash::OnMessage(Agent* pAgent, const SMS& msg)
{
    //send msg to global message handler
    return false;
}

//----------------------------------------methods for GoHomeAndSleep

GoHomeAndSleep* GoHomeAndSleep::Instance()
{
    static GoHomeAndSleep instance;

    return &instance;
}

void GoHomeAndSleep::Enter(Agent* pAgent)
{
    if (pAgent->Location() != AgentHouse)
    {
        WORD COLOR = setColor(pAgent);
        std::multimap<std::string, std::string> SLEEP = goHomeAndSleep(pAgent);
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << SLEEP.find("enterHome")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
        << SLEEP.find("enterHome")->second << RESET;
#endif

        //All the characters send a message to Elena when they are home - TODO: needs to be fixed later!!
        Dispatch->DispatchMessages(SEND_MSG_IMMEDIATELY, //time delay
                                  pAgent->ID(),        //ID of sender
                                  ent_Friend_Elena,            //ID of recipient
                                  Msg_WhatsUp,   //the message
                                  (void *) NO_ADDITIONAL_INFO);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->ChangeLocation(AgentHouse);
    }
}

void GoHomeAndSleep::Execute(Agent* pAgent)
{
    //if Agent is not fatigued start to dig for nuggets again.
    if (!pAgent->Fatigued())
    {
        WORD COLOR = setColor(pAgent);
        std::multimap<std::string, std::string> SLEEP = goHomeAndSleep(pAgent);
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": "
             << SLEEP.find("notFatigued")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
             << SLEEP.find("notFatigued")->second << RESET;
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(Working::Instance());
    }

    else
    {
        //sleep
        pAgent->DecreaseFatigue();

        WORD COLOR = setColor(pAgent);
        std::multimap<std::string, std::string> SLEEP = goHomeAndSleep(pAgent);
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << SLEEP.find("sleeping")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
             << SLEEP.find("sleeping")->second << RESET;
#endif
    }
}

void GoHomeAndSleep::Exit(Agent* pAgent)
{
    WORD COLOR = setColor(pAgent);
    std::multimap<std::string, std::string> SLEEP = goHomeAndSleep(pAgent);
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << SLEEP.find("exitHome")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": " << SLEEP.find("exitHome")->second << RESET;
#endif
}

bool GoHomeAndSleep::OnMessage(Agent* pAgent, const SMS& msg)
{
    switch(msg.Msg)
    {
        case Msg_VideoGames:

            std::cout << "\nMessage handled by " << GetNameOfEntity(pAgent->ID())
                 << " at time: " << Clock->GetCurrentTime();

            std::cout << "\n" << GetNameOfEntity(pAgent->ID())
                 << ": Okay Hun, ahm a comin'!";

            //pAgent->GetFSM()->ChangeState(EatStew::Instance());
            pAgent->GetFSM()->ChangeState(ReduceHunger::Instance());

            return true;

    }//end switch

    return false; //send message to global message handler
}

//------------------------------------------------methods for QuenchThirst

QuenchThirst* QuenchThirst::Instance()
{
    static QuenchThirst instance;

    return &instance;
}

void QuenchThirst::Enter(Agent* pAgent)
{
    if (pAgent->Location() != Bar)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->ChangeLocation(Bar);

        WORD COLOR = setColor(pAgent);
        std::multimap<std::string, std::string> DRINK = drinkAtBar(pAgent);
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": "
             << DRINK.find("enterBar")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
             << DRINK.find("enterBar")->second << RESET;
#endif
    }
}

void QuenchThirst::Execute(Agent* pAgent)
{
    if (pAgent->Thirsty())
    {
        pAgent->DrinkSomethingAtTheBar();

        WORD COLOR = setColor(pAgent);
        std::multimap<std::string, std::string> DRINK = drinkAtBar(pAgent);
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << DRINK.find("drinking")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": " << DRINK.find("drinking")->second << RESET;
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(Working::Instance());
    }

    else
    {
        std::cout << "\nERROR!\nERROR!\nERROR!";
    }
}

void QuenchThirst::Exit(Agent* pAgent)
{
    WORD COLOR = setColor(pAgent);
    std::multimap<std::string, std::string> DRINK = drinkAtBar(pAgent);
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << DRINK.find("exitBar")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": " << DRINK.find("exitBar")->second << RESET;
#endif
}

bool QuenchThirst::OnMessage(Agent* pAgent, const SMS& msg)
{
    //send msg to global message handler
    return false;
}

// -------------------------------------------- End of methods for QuenchThirst

// -------------------------------------------- Methods for reducing hunger
ReduceHunger* ReduceHunger::Instance()
{
    static ReduceHunger instance;

    return &instance;
}

void ReduceHunger::Enter(Agent* pAgent)
{
    if (pAgent->Location() != Bar)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->ChangeLocation(Bar);

        WORD COLOR = setColor(pAgent);
        std::multimap<std::string, std::string> EAT = eatAtBar(pAgent);
        std::string enterBar = "enterBar";
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": "
             << EAT.find(enterBar)->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
             << EAT.find(enterBar)->second << RESET;
#endif
    }
}

void ReduceHunger::Execute(Agent* pAgent)
{
    if (pAgent->Hungry())
    {
        pAgent->EatSomethingAtTheBar();

        WORD COLOR = setColor(pAgent);
        std::multimap<std::string, std::string> EAT = eatAtBar(pAgent);
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": "
             << EAT.find("eating")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
             << EAT.find("eating")->second << RESET;
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(Working::Instance());
    }

    else
    {
        std::cout << "\nERROR!\nERROR!\nERROR!";
    }
}

void ReduceHunger::Exit(Agent* pAgent)
{
    WORD COLOR = setColor(pAgent);
    std::multimap<std::string, std::string> EAT = eatAtBar(pAgent);
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << EAT.find("exitBar")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
         << EAT.find("exitBar")->second << RESET;
#endif
}

bool ReduceHunger::OnMessage(Agent* pAgent, const SMS& msg)
{
    //send msg to global message handler
    return false;
}

// -------------------------------------------- End of methods for reducing hunger

// -------------------------------------------- Methods for reducing boredom
ReduceBoredom* ReduceBoredom::Instance()
{
    static ReduceBoredom instance;

    return &instance;
}

void ReduceBoredom::Enter(Agent* pAgent)
{
    if (pAgent->Location() != Bar)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->ChangeLocation(Bar);

        WORD COLOR = setColor(pAgent);
        std::multimap<std::string, std::string> MEET = meetFriendsAtBar(pAgent);
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": "
             << MEET.find("enterBar")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
             << MEET.find("enterBar")->second << RESET;
#endif
    }
}

void ReduceBoredom::Execute(Agent* pAgent)
{
    if (pAgent->Bored())
    {
        pAgent->MeetFriends();

        WORD COLOR = setColor(pAgent);
        std::multimap<std::string, std::string> MEET = meetFriendsAtBar(pAgent);
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << MEET.find("atBar")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
             << MEET.find("atBar")->second << RESET;
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(Working::Instance());
    }

    else
    {
        std::cout << "\nERROR!\nERROR!\nERROR!";
    }
}

void ReduceBoredom::Exit(Agent* pAgent)
{
    WORD COLOR = setColor(pAgent);
    std::multimap<std::string, std::string> MEET = meetFriendsAtBar(pAgent);
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << MEET.find("exitBar")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
         << MEET.find("exitBar")->second << RESET;
#endif
}

bool ReduceBoredom::OnMessage(Agent* pAgent, const SMS& msg)
{
    //send msg to global message handler
    return false;
}

// -------------------------------------------- End of methods for reducing boredom

// -------------------------------------------- Methods for buying stuff
BuyStuff* BuyStuff::Instance()
{
    static BuyStuff instance;

    return &instance;
}

void BuyStuff::Enter(Agent* pAgent)
{
    if (pAgent->Location() != Walmart)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->ChangeLocation(Walmart);

        WORD COLOR = setColor(pAgent);
        std::multimap<std::string, std::string> SHOP = shopAtWalmart(pAgent);
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": "
             << SHOP.find("enterWalmart")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
             << SHOP.find("enterWalmart")->second << RESET;
#endif
    }
}

void BuyStuff::Execute(Agent* pAgent)
{
    if (pAgent->KeenOnBuying())
    {
        pAgent->BuySomething();

        WORD COLOR = setColor(pAgent);
        std::multimap<std::string, std::string> SHOP = shopAtWalmart(pAgent);
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << SHOP.find("atWalmart")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
        << SHOP.find("atWalmart")->second << RESET;
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(Working::Instance());
    }

    else
    {
        std::cout << "\nERROR!\nERROR!\nERROR!";
    }
}

void BuyStuff::Exit(Agent* pAgent)
{
    WORD COLOR = setColor(pAgent);
    std::multimap<std::string, std::string> SHOP = shopAtWalmart(pAgent);
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        std::cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << SHOP.find("exitWalmart")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    std::cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
    << SHOP.find("exitWalmart")->second << RESET;
#endif
}

bool BuyStuff::OnMessage(Agent* pAgent, const SMS& msg)
{
    //send msg to global message handler
    return false;
}

//------------------------------------End of methods for buying stuff