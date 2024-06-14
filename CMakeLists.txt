cmake_minimum_required(VERSION 3.21)
project(Assignment1_FSM)

set(CMAKE_CXX_STANDARD 17)

add_executable(Assignment1_FSM  Code/main.cpp
                                Code/Characters/AgentOwnedStates.cpp
                                Code/Characters/AgentOwnedStates.h
                                Code/Characters/Agent.cpp
                                Code/Characters/Agent.h
                                Code/Characters/EntityNames.h
                                Code/Characters/Personalities.h
                                Code/StateMachine/BaseGameEntity.cpp
                                Code/StateMachine/BaseGameEntity.h
                                Code/StateMachine/State.h
                                Code/StateMachine/StateMachine.h
                                Code/Locations/Locations.h
                                Code/Utilities/TextColor.h
                                Code/Utilities/Utilities.h
                                #Code/Messaging/CrudeTimer.h
                                #Code/Messaging/EntityManager.cpp
                                #Code/Messaging/EntityManager.h
                                #Code/Messaging/MessageDispatcher.cpp
                                #Code/Messaging/MessageDispatcher.h
                                #Code/Messaging/MessageTypes.h
                                #Code/Messaging/Telegram.h
)
