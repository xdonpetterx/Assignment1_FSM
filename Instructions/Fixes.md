Unchecked files needs fixing to get messaging working:
============================================

### Characters:
- [x] Agent.cpp <-> Agent.cpp
- [x] Agent.h <-> Agent.h
- [x] AgentOwnedStates.cpp <-> AgentOwnedStates.cpp
- [x] AgentOwnedStates.h <-> AgentOwnedStates.h
- [ ] EntityNames.h <-> EntityNames.h
- [ ] Personalities.h <-> Doesn't exist 

### Locations:
- [x] Locations.h <-> Locations.h

### StateMachine:
- [x] BaseGameEntity.cpp <-> BaseGameEntity.cpp
- [x] BaseGameEntity.h <-> BaseGameEntity.h
- [x] State.h <-> State.h
- [x] StateMachine.h <-> StateMachine.h

- [x] HandleMessage
    - [x] Agent.h
    - [x] Agent.cpp
    - [x] BaseGameEntity.h
    - [x] MessageDispatcher.cpp
    - [x] StateMachine.h

### GoHomeAndSleep:
- [ ] Needs to enter GoHomeAndSleep::Enter - Now it jumps straight to GoHomeAndSleep::Execute
    - [ ] Walkin' home
    - [ ] Taking a Uber home
    - [ ] Riding my bike home
    - [ ] Driving home

- [ ] Needs to enter GoHomeAndSleep::Execute
    - [] What a God darn fantastic nap! Time to go to work to earn more cash

### States in order:
1. GoHomeAndSleep - notFatigued
2. GoHomeAndSleep - exitHome
3. Working - enterWork
4. Working - working
5. Working - working
6. Working - working
7. Working - exitWork
8. VisitBankAndDepositCash - enterBank
9. VisitBankAndDepositCash - ifRichEnough
10. eatAtBar - enterBar
11. eatAtBar - eating
12. eatAtBar - exitBar
13. Working - enterWork
14. Working - working
15. Working - exitWork
16. VisitBankAndDepositCash - enterBank
17. VisitBankAndDepositCash - ifRichEnough
18. drinkAtBar - enterBar
19. drinkAtBar - drinking
20. drinkAtBar - exitBar
21. Working - enterWork 
22. Working - working 
23. Working - exitWork 
24. VisitBankAndDepositCash - enterBank 
25. VisitBankAndDepositCash - ifRichEnough
26. meetFriendsAtBar - enterBar
27. meetFriendsAtBar - exitBar
28. shopAtWalmart - enterWalmart
29. shopAtWalmart - atWalmart
30. shopAtWalmart - exitWalmart
31. Working - enterWork 
32. Working - working 
33. Working - exitWork 

Setting the breakpoint in line 86 in Personalities.h stops the process
Setting the breakpoint in line 242 in AgentOwnedStates.cpp stops the process
which means that VisitBankAndDepositCash::Exit is always called!
But VisitBankAndDepositCash::Execute is not!!