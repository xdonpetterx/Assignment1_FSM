#pragma once
#include "../StateMachine/State.h"

class Agent;
//------------------------------------------------------------------------
//
//  In this state the Agent will walk to a McDonald's and get cash for working.
//  If the Agent already has a nugget of gold he'll change state
//  to VisitBankAndDepositCash. If he gets thirsty he'll change state
//  to QuenchThirst and if he gets hungry he'll change state to ReduceHunger
//------------------------------------------------------------------------
class EnterMcDonaldsAndWorkForCash : public State<Agent>
{
private:

    EnterMcDonaldsAndWorkForCash()= default;

    //copy ctor and assignment should be private
    EnterMcDonaldsAndWorkForCash(const EnterMcDonaldsAndWorkForCash&);
    EnterMcDonaldsAndWorkForCash& operator=(const EnterMcDonaldsAndWorkForCash&);

public:

    static EnterMcDonaldsAndWorkForCash* Instance();

public:

    void Enter(Agent* Agent) override;

    void Execute(Agent* Agent) override;

    void Exit(Agent* Agent) override;

};

//------------------------------------------------------------------------
//
//  Entity will go to a Bank and deposit any cash he is carrying. If the
//  Agent is subsequently wealthy enough he'll walk home, otherwise he'll
//  keep going to get more cash
//------------------------------------------------------------------------
class VisitBankAndDepositCash : public State<Agent>
{
private:

    VisitBankAndDepositCash()= default;

    VisitBankAndDepositCash(const VisitBankAndDepositCash&);
    VisitBankAndDepositCash& operator=(const VisitBankAndDepositCash&);

public:

    static VisitBankAndDepositCash* Instance();

    void Enter(Agent* Agent) override;

    void Execute(Agent* Agent) override;

    void Exit(Agent* Agent) override;
};

//------------------------------------------------------------------------
//
//  Agent will go home and sleep until his fatigue is decreased
//  sufficiently
//------------------------------------------------------------------------
class GoHomeAndSleep : public State<Agent>
{
private:

    GoHomeAndSleep()= default;

    //copy ctor and assignment should be private
    GoHomeAndSleep(const GoHomeAndSleep&);
    GoHomeAndSleep& operator=(const GoHomeAndSleep&);

public:

    static GoHomeAndSleep* Instance();

    void Enter(Agent* Agent) override;

    void Execute(Agent* Agent) override;

    void Exit(Agent* Agent) override;
};

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
class QuenchThirst : public State<Agent>
{
private:

    QuenchThirst()= default;

    //copy ctor and assignment should be private
    QuenchThirst(const QuenchThirst&);
    QuenchThirst& operator=(const QuenchThirst&);

public:

    static QuenchThirst* Instance();

    void Enter(Agent* Agent) override;

    void Execute(Agent* Agent) override;

    void Exit(Agent* Agent) override;
};

class ReduceHunger : public State<Agent>
{
private:

    ReduceHunger()= default;

    //copy ctor and assignment should be private
    ReduceHunger(const ReduceHunger&);
    ReduceHunger& operator=(const ReduceHunger&);

public:

    static ReduceHunger* Instance();

    void Enter(Agent* Agent) override;

    void Execute(Agent* Agent) override;

    void Exit(Agent* Agent) override;
};

class ReduceBoredom : public State<Agent>
{
private:

    ReduceBoredom()= default;

    //copy ctor and assignment should be private
    ReduceBoredom(const ReduceBoredom&);
    ReduceBoredom& operator=(const ReduceBoredom&);

public:

    static ReduceBoredom* Instance();

    void Enter(Agent* Agent) override;

    void Execute(Agent* Agent) override;

    void Exit(Agent* Agent) override;
};

class BuyStuff : public State<Agent>
{
private:

    BuyStuff()= default;

    //copy ctor and assignment should be private
    BuyStuff(const BuyStuff&);
    BuyStuff& operator=(const BuyStuff&);

public:

    static BuyStuff* Instance();

    void Enter(Agent* Agent) override;

    void Execute(Agent* Agent) override;

    void Exit(Agent* Agent) override;
};