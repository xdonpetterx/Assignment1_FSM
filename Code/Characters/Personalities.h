#pragma once

#include <Characters/AgentOwnedStates.h>
#include <Characters/Agent.h>
#include <Characters/EntityNames.h>
#include <Locations/Locations.h>
#include <StateMachine/State.h>
#include <Utilities/TextColor.h>
#include <Utilities/Utilities.h>

#include <map>

std::multimap<std::string, std::string> setWork(Agent* pAgent)
{
    std::multimap<std::string, std::string> WORK, WORK1, WORK2;
    if (GetNameOfEntity(pAgent->ID()) == "Agent Charlie"){
        WORK1.insert(std::make_pair("enterWork","Walkin' to the McDonalds"));
        WORK2.insert(std::make_pair("enterWork","Walkin' to the Coal Mine"));
        WORK1.insert(std::make_pair("working","Flippin' a burger, getting cash"));
        WORK2.insert(std::make_pair("working","Minin' coal, getting cash"));
        WORK1.insert(std::make_pair("exitWork","I'm leavin' McDonald's with my pockets full of cash"));
        WORK2.insert(std::make_pair("exitWork","I'm leavin' the Coal Mine with my pockets full of cash"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Elena"){
        WORK1.insert(std::make_pair("enterWork","Taking a Uber to the Power Plant"));
        WORK2.insert(std::make_pair("enterWork","Taking a Uber to the Chemical Factory"));
        WORK1.insert(std::make_pair("working","Working at the Power Plant"));
        WORK2.insert(std::make_pair("working","Mixing chemicals"));
        WORK1.insert(std::make_pair("exitWork","Enough money earned for now. Leaving the Power Plant"));
        WORK2.insert(std::make_pair("exitWork","Enough money earned for now. Leaving the Chemical Factory"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Jonny"){
        WORK1.insert(std::make_pair("enterWork","Riding a bike to the Hospital"));
        WORK2.insert(std::make_pair("enterWork","Riding a bike to the Car Factory"));
        WORK1.insert(std::make_pair("working","Saving the World, one person at a time"));
        WORK2.insert(std::make_pair("working","Fixing cars"));
        WORK1.insert(std::make_pair("exitWork","Finished work. I'm leaving the Hospital"));
        WORK2.insert(std::make_pair("exitWork","Finished work. I'm leaving the Car Factory"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Mike"){
        WORK1.insert(std::make_pair("enterWork","Driving to the Pizzeria"));
        WORK2.insert(std::make_pair("enterWork","Driving to the Prison"));
        WORK1.insert(std::make_pair("working","Baking pizzas"));
        WORK2.insert(std::make_pair("working","Back to the Prison, this time as a guard"));
        WORK1.insert(std::make_pair("exitWork","Let's call it a day. I'm leaving the Pizzeria"));
        WORK2.insert(std::make_pair("exitWork","Let's call it a day. I'm leaving the Prison"));
    }
    else{
        WORK1.insert(std::make_pair("enterWork","Going to work"));
        WORK2.insert(std::make_pair("enterWork","Going to work"));
        WORK1.insert(std::make_pair("working","Working"));
        WORK2.insert(std::make_pair("working","Working"));
        WORK1.insert(std::make_pair("exitWork","I'm leaving work"));
        WORK2.insert(std::make_pair("exitWork","I'm leaving work"));
    }
    switch (RandomInteger(0, 1)) {
        case 0:
            WORK = WORK1;
            break;
        case 1:
            WORK = WORK2;
            break;
    }
    return WORK;
}

std::multimap<std::string, std::string> depositCash(Agent* pAgent)
{
    std::multimap<std::string, std::string> DEPOSIT;
    if (GetNameOfEntity(pAgent->ID()) == "Agent Charlie"){
        DEPOSIT.insert(std::make_pair("enterBank","Going to the Bank. Yes sir!"));
        DEPOSIT.insert(std::make_pair("depositing","Here's mi money. Total savings now: $"));
        DEPOSIT.insert(std::make_pair("ifRichEnough",
                                         "WooHoo! Rich enough for now. Back home for some well earned rest"));
        DEPOSIT.insert(std::make_pair("exitBank","Leavin' the bank"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Elena"){
        DEPOSIT.insert(std::make_pair("enterBank","Taking a Uber to the Bank to deposit my savings"));
        DEPOSIT.insert(std::make_pair("depositing","Depositing savings. Total savings now: $"));
        DEPOSIT.insert(std::make_pair("ifRichEnough","Rich enough. Back home to watch some Netflix"));
        DEPOSIT.insert(std::make_pair("exitBank","Leaving the bank"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Jonny"){
        DEPOSIT.insert(std::make_pair("enterBank","Riding a bike to the Bank. Going to deposit my savings"));
        DEPOSIT.insert(std::make_pair("depositing","Depositing savings. Total savings now: $"));
        DEPOSIT.insert(std::make_pair("ifRichEnough","Rich enough for now. Back home for some video games"));
        DEPOSIT.insert(std::make_pair("exitBank","Leaving the bank"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Mike"){
        DEPOSIT.insert(std::make_pair("enterBank","Driving to the Bank. Goin' to deposit my savings"));
        DEPOSIT.insert(std::make_pair("depositing","Depositing savings. Total savings now: $"));
        DEPOSIT.insert(std::make_pair("ifRichEnough",
                                         "Rich enough for now. Back home for some guitar practice"));
        DEPOSIT.insert(std::make_pair("exitBank","Leaving the bank"));
    }
    else{
        DEPOSIT.insert(std::make_pair("enterBank","Going to the bank. Goin' to deposit my savings"));
        DEPOSIT.insert(std::make_pair("depositing","Depositing savings. Total savings now: $"));
        DEPOSIT.insert(std::make_pair("ifRichEnough","Rich enough for now. Back home to rest"));
        DEPOSIT.insert(std::make_pair("exitBank","Leaving the bank"));
    }
    return DEPOSIT;
}

std::multimap<std::string, std::string> goHomeAndSleep(Agent* pAgent)
{
    std::multimap<std::string, std::string> SLEEP;
    if (GetNameOfEntity(pAgent->ID()) == "Agent Charlie") {
        SLEEP.insert(std::make_pair("enterHome", "Walkin' home"));
        SLEEP.insert(std::make_pair("notFatigued",
                                       "What a God darn fantastic nap! Time to go to work to earn more cash"));
        SLEEP.insert(std::make_pair("sleeping", "ZZZZ..."));
        SLEEP.insert(std::make_pair("exitHome", "Leaving the trailer"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Elena") {
        SLEEP.insert(std::make_pair("enterHome", "Taking a Uber home"));
        SLEEP.insert(std::make_pair("notFatigued", "What a nice sleep. Time to make some money"));
        SLEEP.insert(std::make_pair("sleeping", "ZZZZ..."));
        SLEEP.insert(std::make_pair("exitHome", "Leaving the house"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Jonny") {
        SLEEP.insert(std::make_pair("enterHome", "Riding my bike home"));
        SLEEP.insert(std::make_pair("notFatigued", "Did I even sleep? Well, it's time to go to work anyways"));
        SLEEP.insert(std::make_pair("sleeping", "ZZZZ..."));
        SLEEP.insert(std::make_pair("exitHome", "Leaving the penthouse"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Mike") {
        SLEEP.insert(std::make_pair("enterHome", "Driving home"));
        SLEEP.insert(std::make_pair("notFatigued", "The nightmares have ended. Time to make some money"));
        SLEEP.insert(std::make_pair("sleeping", "ZZZZ..."));
        SLEEP.insert(std::make_pair("exitHome", "Heading to work"));
    }
    else {
        SLEEP.insert(std::make_pair("enterHome", "I'm home. I'm tired and need to sleep"));
        SLEEP.insert(std::make_pair("notFatigued", "I slept OK. Time to make some money"));
        SLEEP.insert(std::make_pair("sleeping", "ZZZZ..."));
        SLEEP.insert(std::make_pair("exitHome", "I'm leaving home"));
    }
    return SLEEP;
}

std::multimap<std::string, std::string> drinkAtBar(Agent* pAgent)
{
    std::multimap<std::string, std::string> DRINK;
    if (GetNameOfEntity(pAgent->ID()) == "Agent Charlie"){
        DRINK.insert(std::make_pair("enterBar","Boy, ah sure is thirsty! Walking to the bar"));
        DRINK.insert(std::make_pair("drinking","That's mighty fine beer"));
        DRINK.insert(std::make_pair("exitBar","I'm leaving the Bar by foot. No longer thirsty"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Elena"){
        DRINK.insert(std::make_pair("enterBar","Taking a Uber to the Bar to get something to drink"));
        DRINK.insert(std::make_pair("drinking","Drinking a cocktail"));
        DRINK.insert(std::make_pair("exitBar","I'm leaving the Bar in a Uber. No longer thirsty"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Jonny"){
        DRINK.insert(std::make_pair("enterBar","Riding a bike to the Bar to get something to drink"));
        DRINK.insert(std::make_pair("drinking","Drinking a martini"));
        DRINK.insert(std::make_pair("exitBar","I'm leaving the Bar by bike. No longer thirsty"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Mike"){
        DRINK.insert(std::make_pair("enterBar","Taking a bus to the Bar to get something to drink"));
        DRINK.insert(std::make_pair("drinking","Drinking a whiskey"));
        DRINK.insert(std::make_pair("exitBar","I'm leaving the Bar by bus. No longer thirsty"));
    }
    else{
        DRINK.insert(std::make_pair("enterBar","Going to the Bar to get something to drink"));
        DRINK.insert(std::make_pair("drinking","Drinking"));
        DRINK.insert(std::make_pair("exitBar","I'm leaving the Bar. No longer thirsty"));
    }
    return DRINK;
}

std::multimap<std::string, std::string> eatAtBar(Agent* pAgent){
    std::multimap<std::string, std::string> EAT;
    if (GetNameOfEntity(pAgent->ID()) == "Agent Charlie"){
        EAT.insert(std::make_pair("enterBar","Boy, ah sure is hungry! Walking to the bar"));
        EAT.insert(std::make_pair("eating","That's mighty fine porridge"));
        EAT.insert(std::make_pair("exitBar","Leaving the bar by foot, not hungry anymore"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Elena"){
        EAT.insert(std::make_pair("enterBar","Taking a Uber to the Bar to get something to eat"));
        EAT.insert(std::make_pair("eating","Eating a salad"));
        EAT.insert(std::make_pair("exitBar","Leaving the bar in a Uber, not hungry anymore"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Jonny"){
        EAT.insert(std::make_pair("enterBar","Riding a bike to the Bar to get something to eat"));
        EAT.insert(std::make_pair("eating","Eating a sandwich"));
        EAT.insert(std::make_pair("exitBar","Leaving the bar by bike, not hungry anymore"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Mike"){
        EAT.insert(std::make_pair("enterBar","Driving to the Bar to get something to eat"));
        EAT.insert(std::make_pair("eating","Eating a pizza"));
        EAT.insert(std::make_pair("exitBar","Leaving the bar by car, not hungry anymore"));
    }
    else{
        EAT.insert(std::make_pair("enterBar","Going to the Bar to get something to eat"));
        EAT.insert(std::make_pair("eating","Eating"));
        EAT.insert(std::make_pair("exitBar","Leaving the bar, not hungry anymore"));
    }
    return EAT;
}

std::multimap<std::string, std::string> meetFriendsAtBar(Agent* pAgent){
    std::multimap<std::string, std::string> MEET;
    if (GetNameOfEntity(pAgent->ID()) == "Agent Charlie"){
        MEET.insert(std::make_pair("enterBar","Boy, ah sure is bored! Walking to meet som' friends at the bar"));
        MEET.insert(std::make_pair("atBar","Hanging out with mi friends"));
        MEET.insert(std::make_pair("exitBar","Leavin' the bar by foot"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Elena"){
        MEET.insert(std::make_pair("enterBar","Taking a Uber to the Bar"));
        MEET.insert(std::make_pair("atBar","Good times with friends"));
        MEET.insert(std::make_pair("exitBar","Leaving the bar in a Uber"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Jonny"){
        MEET.insert(std::make_pair("enterBar","Riding a bike to the Bar"));
        MEET.insert(std::make_pair("atBar","Playing pool with friends"));
        MEET.insert(std::make_pair("exitBar","Leaving the bar by bike"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Mike"){
        MEET.insert(std::make_pair("enterBar","Taking a bus to the Bar"));
        MEET.insert(std::make_pair("atBar","Getting drunk at the blackjack table"));
        MEET.insert(std::make_pair("exitBar","Leaving the bar by bus"));
    }
    else{
        MEET.insert(std::make_pair("enterBar","Going to the Bar"));
        MEET.insert(std::make_pair("atBar","Waiting for my friends"));
        MEET.insert(std::make_pair("exitBar","Leaving the bar"));
    }
    return MEET;
}

std::multimap<std::string, std::string> shopAtWalmart(Agent* pAgent){
    std::multimap<std::string, std::string> SHOP;
    if (GetNameOfEntity(pAgent->ID()) == "Agent Charlie"){
        SHOP.insert(std::make_pair("enterWalmart","Walking to Walmart"));
        SHOP.insert(std::make_pair("atWalmart","Buying a hammer and an axe"));
        SHOP.insert(std::make_pair("exitWalmart","Leavin' Walmart by foot"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Elena"){
        SHOP.insert(std::make_pair("enterWalmart","Taking a Uber to Walmart"));
        SHOP.insert(std::make_pair("atWalmart","Buying bread and milk"));
        SHOP.insert(std::make_pair("exitWalmart","Leaving Walmart in a Uber"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Jonny"){
        SHOP.insert(std::make_pair("enterWalmart","Riding a bike to Walmart"));
        SHOP.insert(std::make_pair("atWalmart","Buying some groceries"));
        SHOP.insert(std::make_pair("exitWalmart","Leaving Walmart by bike"));
    }
    else if (GetNameOfEntity(pAgent->ID()) == "Friend Mike"){
        SHOP.insert(std::make_pair("enterWalmart","Taking the car to Walmart"));
        SHOP.insert(std::make_pair("atWalmart","Buying some rope and a shovel"));
        SHOP.insert(std::make_pair("exitWalmart","Leaving Walmart by car"));
    }
    else{
        SHOP.insert(std::make_pair("enterWalmart","Going to Walmart"));
        SHOP.insert(std::make_pair("atWalmart","Buying some groceries"));
        SHOP.insert(std::make_pair("exitWalmart","Leaving Walmart"));
    }
    return SHOP;
}

