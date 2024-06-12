#include "Personalities.h"

#include <iostream>
#include <map>
#include <thread>

using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

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



//--------------------------------------methods for EnterMcDonaldsAndWorkForCash

EnterMcDonaldsAndWorkForCash* EnterMcDonaldsAndWorkForCash::Instance()
{
    static EnterMcDonaldsAndWorkForCash instance;
    return &instance;
}

void EnterMcDonaldsAndWorkForCash::Enter(Agent* pAgent)
{
    //if the Agent is not already located at McDonalds, he must
    //change location to the gold mine
    if (pAgent->Location() != McDonalds)
    {
        WORD COLOR = setColor(pAgent);
        std::multimap<std::string, std::string> WORK = setWork(pAgent);
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << WORK.find("enterWork")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
        << WORK.find("enterWork")->second << RESET;
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->ChangeLocation(McDonalds);
    }
}


void EnterMcDonaldsAndWorkForCash::Execute(Agent* pAgent)
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
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << WORK.find("working")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
    << WORK.find("working")->second << RESET;
#endif

    //if enough cash earned, go and put it in the Bank
    if (pAgent->PocketsFull())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(VisitBankAndDepositCash::Instance());
    }

    if (pAgent->Thirsty())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(QuenchThirst::Instance());
    }

    if (pAgent->Hungry())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(ReduceHunger::Instance());
    }

    if (pAgent->Bored())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(ReduceBoredom::Instance());
    }

    if (pAgent->KeenOnBuying())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(BuyStuff::Instance());
    }
}


void EnterMcDonaldsAndWorkForCash::Exit(Agent* pAgent)
{
    WORD COLOR = setColor(pAgent);
    std::multimap<std::string, std::string> WORK = setWork(pAgent);
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": "
             << WORK.find("exitWork")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
    << WORK.find("exitWork")->second << RESET;
#endif
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
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << DEPOSIT.find("enterBank")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
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
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": "
        << DEPOSIT.find("depositing")->second << pAgent->Wealth();
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
    << DEPOSIT.find("depositing")->second << pAgent->Wealth() << RESET;
#endif

    //wealthy enough to have a well earned rest?
    if (pAgent->Wealth() >= ComfortLevel)
    {
        WORD COLOR = setColor(pAgent);
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": "
             << DEPOSIT.find("ifRichEnough")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
             << DEPOSIT.find("ifRichEnough")->second << RESET;
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(GoHomeAndSleep::Instance());
    }

        //otherwise get more cash
    else
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(EnterMcDonaldsAndWorkForCash::Instance());
    }

}


void VisitBankAndDepositCash::Exit(Agent* pAgent)
{
    WORD COLOR = setColor(pAgent);
    std::multimap<std::string, std::string> DEPOSIT = depositCash(pAgent);
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << DEPOSIT.find("ifRichEnough")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
    << DEPOSIT.find("ifRichEnough")->second << RESET;
#endif
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
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << SLEEP.find("enterHome")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
        << SLEEP.find("enterHome")->second << RESET;
#endif
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
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": "
             << SLEEP.find("notFatigued")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
             << SLEEP.find("notFatigued")->second << RESET;
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(EnterMcDonaldsAndWorkForCash::Instance());
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
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << SLEEP.find("sleeping")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
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
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << SLEEP.find("exitHome")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": " << SLEEP.find("exitHome")->second << RESET;
#endif
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
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": "
             << DRINK.find("enterBar")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
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
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << DRINK.find("drinking")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": " << DRINK.find("drinking")->second << RESET;
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(EnterMcDonaldsAndWorkForCash::Instance());
    }

    else
    {
        cout << "\nERROR!\nERROR!\nERROR!";
    }
}

void QuenchThirst::Exit(Agent* pAgent)
{
    WORD COLOR = setColor(pAgent);
    std::multimap<std::string, std::string> DRINK = drinkAtBar(pAgent);
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << DRINK.find("exitBar")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": " << DRINK.find("exitBar")->second << RESET;
#endif
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
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": "
             << EAT.find(enterBar)->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
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
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": "
             << EAT.find("eating")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
             << EAT.find("eating")->second << RESET;
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(EnterMcDonaldsAndWorkForCash::Instance());
    }

    else
    {
        cout << "\nERROR!\nERROR!\nERROR!";
    }
}

void ReduceHunger::Exit(Agent* pAgent)
{
    WORD COLOR = setColor(pAgent);
    std::multimap<std::string, std::string> EAT = eatAtBar(pAgent);
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << EAT.find("exitBar")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
         << EAT.find("exitBar")->second << RESET;
#endif
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
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": "
             << MEET.find("enterBar")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
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
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << MEET.find("atBar")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
             << MEET.find("atBar")->second << RESET;
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(EnterMcDonaldsAndWorkForCash::Instance());
    }

    else
    {
        cout << "\nERROR!\nERROR!\nERROR!";
    }
}

void ReduceBoredom::Exit(Agent* pAgent)
{
    WORD COLOR = setColor(pAgent);
    std::multimap<std::string, std::string> MEET = meetFriendsAtBar(pAgent);
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << MEET.find("exitBar")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
         << MEET.find("exitBar")->second << RESET;
#endif
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
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": "
             << SHOP.find("enterWalmart")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
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
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << SHOP.find("atWalmart")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
        cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
        << SHOP.find("atWalmart")->second << RESET;
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pAgent->GetFSM()->ChangeState(EnterMcDonaldsAndWorkForCash::Instance());
    }

    else
    {
        cout << "\nERROR!\nERROR!\nERROR!";
    }
}

void BuyStuff::Exit(Agent* pAgent)
{
    WORD COLOR = setColor(pAgent);
    std::multimap<std::string, std::string> SHOP = shopAtWalmart(pAgent);
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, COLOR);
        cout << "\n" << GetNameOfEntity(pAgent->ID()) << ": " << SHOP.find("exitWalmart")->second;
        SetConsoleTextAttribute(hConsole, RESET);
#endif
#ifndef _WIN32
    cout << "\n" << COLOR << GetNameOfEntity(pAgent->ID()) << ": "
    << SHOP.find("exitWalmart")->second << RESET;
#endif
}
//------------------------------------End of methods for buying stuff