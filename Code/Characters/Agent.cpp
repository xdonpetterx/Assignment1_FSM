#include <Characters/Agent.h>

//-----------------------------------------------------------------------------
void Agent::Update()
{
    m_iThirst += 1;
    m_iHunger += 1;
    m_iBoredom +=1;
    m_iKeenOnBuying +=1;

    m_pStateMachine->Update();
}

//-----------------------------------------------------------------------------
void Agent::AddToCashCarried(const int val)
{
    m_iCashCarried += val;

    if (m_iCashCarried < 0) m_iCashCarried = 0;
}

//-----------------------------------------------------------------------------
void Agent::AddToWealth(const int val)
{
    m_iMoneyInBank += val;

    if (m_iMoneyInBank < 0) m_iMoneyInBank = 0;
}

//-----------------------------------------------------------------------------
bool Agent::Thirsty()const
{
    if (m_iThirst >= ThirstLevel){return true;}

    return false;
}
//-----------------------------------------------------------------------------
bool Agent::Hungry()const
{
    if (m_iHunger >= HungerLevel){return true;}

    return false;
}
//-----------------------------------------------------------------------------
bool Agent::Fatigued()const
{
    if (m_iFatigue > TirednessThreshold)
    {
        return true;
    }

    return false;
}
//-----------------------------------------------------------------------------
bool Agent::Bored()const
{
    if (m_iBoredom >= BoredomLevel){return true;}

    return false;
}
bool Agent::KeenOnBuying() const {
    if (m_iKeenOnBuying >= KeenOnBuyingLevel){return true;}

    return false;
}