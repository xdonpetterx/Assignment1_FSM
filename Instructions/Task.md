Task:
============================================
Create a character for a game that through internal representation of its states and characteristics can be described through an FSM. The environment in which the character "lives" must be able to be displayed visually either graphically or in the form of text. Time aspects of the game must be "realistic", which is why you will need to implement a game loop with timers.
Good guidance for the implementation is obtained from the examples that belong to the book's second chapter.

The task should be implemented in C++. FSM libraries can not be used.

The agent shall have the following life:

Collect money (work), at least 2 different places and types.
Buy stuff (eg food, shovel).
Sleep.
Eat.
Drink.
Hang out with friends.

Balancing these needs is part of the task, the goal is that the character should survive for a long time.

It must be possible to send a message between several characters with similar lives. You should be able to meet in the store, when eating / drinking etc. The communication that the agents have between each other must take place in the form of a message, they all have access to a telephone with an SMS function. The dialogue between agents must be printed out and that a meeting is scheduled at a certain time and in a special place. Keep in mind that an agent can starve to death if he goes and meets friends instead of eating, if he needs to eat instead, let his friends know that he is not coming as agreed.
In total, values must consist of at least 4 characters.

Remember to solve these problems in a general way, then you can reuse this FSM in future assignments.

### For grade 3, the following must be implemented:
An FSM that implements the above behavior.

### For grade 4, the following must be implemented:
The above behaviors should be visualized graphically where the sites should be represented on a 2D surface and where the agents move between them through a straight line. You should be able to vary the update time in a simple way, ie speed up or slow down the clock.

### For grade 5, the following must be implemented:
You should be able to "see" the agents' condition by actively selecting them. It must also be possible to change these agent's state variables. You should also be able to pause the simulation.
A non-mandatory function is to be able to reverse the time and change any parameter and run again from that time.