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
3. EnterMcDonaldsAndWorkForCash - enterWork
4. EnterMcDonaldsAndWorkForCash - working
5. EnterMcDonaldsAndWorkForCash - working
6. EnterMcDonaldsAndWorkForCash - working
7. EnterMcDonaldsAndWorkForCash - exitWork
8. VisitBankAndDepositCash - enterBank
9. VisitBankAndDepositCash - ifRichEnough
10. eatAtBar - enterBar
11. eatAtBar - eating
12. eatAtBar - exitBar
13. EnterMcDonaldsAndWorkForCash - enterWork
14. EnterMcDonaldsAndWorkForCash - working
15. EnterMcDonaldsAndWorkForCash - exitWork
16. VisitBankAndDepositCash - enterBank
17. VisitBankAndDepositCash - ifRichEnough
18. drinkAtBar - enterBar
19. drinkAtBar - drinking
20. drinkAtBar - exitBar
21. EnterMcDonaldsAndWorkForCash - enterWork 
22. EnterMcDonaldsAndWorkForCash - working 
23. EnterMcDonaldsAndWorkForCash - exitWork 
24. VisitBankAndDepositCash - enterBank 
25. VisitBankAndDepositCash - ifRichEnough
26. meetFriendsAtBar - enterBar
27. meetFriendsAtBar - exitBar
28. shopAtWalmart - enterWalmart
29. shopAtWalmart - atWalmart
30. shopAtWalmart - exitWalmart
31. EnterMcDonaldsAndWorkForCash - enterWork 
32. EnterMcDonaldsAndWorkForCash - working 
33. EnterMcDonaldsAndWorkForCash - exitWork 

Setting the breakpoint in line 86 in Personalities.h stops the process
Setting the breakpoint in line 242 in AgentOwnedStates.cpp stops the process
which means that VisitBankAndDepositCash::Exit is always called!
But VisitBankAndDepositCash::Execute is not!!