# Source CMake project file for the Assignment1_FSM project.

# CREATE EXECUTABLE
file(GLOB_RECURSE SUBDIRECTORIES "${CMAKE_SOURCE_DIR}/Code/*.cpp" "${CMAKE_SOURCE_DIR}/Code/*.h")
source_group(TREE "${CMAKE_SOURCE_DIR}/Code" FILES ${SUBDIRECTORIES})
add_executable(Assignment1_FSM  main.cpp

        "Characters/AgentOwnedStates.cpp"
        "Characters/AgentOwnedStates.h"
        "Characters/Agent.cpp"
        "Characters/Agent.h"
        "Characters/EntityNames.h"
        "Characters/Personalities.h"

        "Locations/Locations.h"

        "Messaging/CrudeTimer.h"
        "Messaging/EntityManager.cpp"
        "Messaging/EntityManager.h"
        "Messaging/MessageDispatcher.cpp"
        "Messaging/MessageDispatcher.h"
        "Messaging/MessageTypes.h"
        "Messaging/SMS.h"

        "StateMachine/BaseGameEntity.cpp"
        "StateMachine/BaseGameEntity.h"
        "StateMachine/State.h"
        "StateMachine/StateMachine.h"

        "Utilities/TextColor.h"
        "Utilities/Utilities.h"
)

# INCLUDE DIRECTORIES AND LINK LIBRARIES
target_include_directories(Assignment1_FSM PRIVATE "${CMAKE_SOURCE_DIR}/Code")