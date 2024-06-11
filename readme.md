# Assignment 1: Finite State Machine

## Introduction
This is a simple implementation of a Finite State Machine (FSM) in C++. The FSM is a mathematical model of computation that consists of a set of states, a set of input symbols, a set of transitions, and a set of output symbols. The FSM starts in a start state and transitions to different states based on the input symbols it receives. The FSM can also produce output symbols based on the input symbols it receives.

## Implementation
The FSM is implemented using a class called `FiniteStateMachine`. The class has the following attributes:   
- `states`: A set of states in the FSM.
- `input_symbols`: A set of input symbols in the FSM.
- `output_symbols`: A set of output symbols in the FSM.
- `transitions`: A set of transitions in the FSM.
- `start_state`: The start state of the FSM.
- `current_state`: The current state of the FSM.
- `current_output`: The current output of the FSM.
- `is_accepting`: A boolean flag that indicates whether the FSM is in an accepting state.
- `is_rejecting`: A boolean flag that indicates whether the FSM is in a rejecting state.
- `is_halted`: A boolean flag that indicates whether the FSM has halted.
- `is_error`: A boolean flag that indicates whether an error has occurred in the FSM.
- `error_message`: A string that contains the error message if an error has occurred.
- `transition_function`: A function that defines the transition function of the FSM.
- `reset`: A function that resets the FSM to its initial state.