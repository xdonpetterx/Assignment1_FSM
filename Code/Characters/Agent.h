#pragma once

#include <string>
#include <cassert>

#include <Characters/AgentOwnedStates.h>
#include <Locations/Locations.h>
#include <StateMachine/BaseGameEntity.h>
#include <StateMachine/StateMachine.h>

template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

struct Telegram;

//the amount of cash an Agent must have before he feels comfortable
const int ComfortLevel       = 5;
//the amount of cash an Agent can carry
const int MaxCash         = 3;
//above this value an Agent is thirsty
const int ThirstLevel        = 5;
//above this value an Agent is hungry
const int HungerLevel        = 4;
//above this value an Agent is sleepy
const int TirednessThreshold = 5;
//above this value an Agent is bored and want to meet friends
const int BoredomLevel        = 8;
//above this value an Agent is keen on buying stuff
const int KeenOnBuyingLevel        = 7;


class Agent : public BaseGameEntity
{
private:

    //an instance of the state machine class
    StateMachine<Agent>*  m_pStateMachine;

    location_type         m_Location;

    int                   m_iCashCarried;
    int                   m_iMoneyInBank;
    int                   m_iThirst;
    int                   m_iHunger;
    int                   m_iFatigue;
    int                   m_iBoredom;
    int                   m_iKeenOnBuying;

public:

    explicit Agent(int id):BaseGameEntity(id),
                  m_Location(AgentHouse),
                  m_iCashCarried(0),
                  m_iMoneyInBank(0),
                  m_iThirst(0),
                  m_iHunger(0),
                  m_iFatigue(0),
                  m_iBoredom(0),
                  m_iKeenOnBuying(0)
    {
        m_pStateMachine = new StateMachine<Agent>(this);

        m_pStateMachine->SetCurrentState(GoHomeAndSleep::Instance());
    }

    ~Agent() override{delete m_pStateMachine;}

    //this must be implemented
    void Update() override;

    bool  HandleMessage(const Telegram& msg) override;
    [[nodiscard]] StateMachine<Agent>*  GetFSM()const{return m_pStateMachine;}


    [[nodiscard]] location_type Location()const{return m_Location;}
    void          ChangeLocation(const location_type loc){m_Location=loc;}

    [[nodiscard]] int           CashCarried()const{return m_iCashCarried;}
    void          SetCashCarried(const int val){ m_iCashCarried = val;}
    void          AddToCashCarried(int val);
    [[nodiscard]] bool          PocketsFull()const{return m_iCashCarried >= MaxCash;}

    [[nodiscard]] bool          Fatigued()const;
    void          DecreaseFatigue(){m_iFatigue -= 1;}
    void IncreaseFatigue() { m_iFatigue += 5;}

    [[nodiscard]] int           Wealth()const{return m_iMoneyInBank;}

    [[maybe_unused]] void          SetWealth(const int val){m_iMoneyInBank = val;}
    void          AddToWealth(int val);

    [[nodiscard]] bool          Thirsty()const;
    void          DrinkSomethingAtTheBar(){ m_iThirst = 0; m_iMoneyInBank-=2;}

    [[nodiscard]] bool          Hungry()const;
    void          EatSomethingAtTheBar(){ m_iHunger = 0; m_iMoneyInBank-=2;}

    [[nodiscard]] bool          Bored()const;
    void          MeetFriends(){m_iBoredom = 0;}

    [[nodiscard]] bool          KeenOnBuying()const;
    void          BuySomething(){m_iKeenOnBuying = 0; m_iMoneyInBank-=1;}
};