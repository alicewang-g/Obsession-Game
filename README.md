Obsession
Obsession is a C++ command-line turn-based strategy board game played against a computer AI. Players roll dice to manipulate numbered rings on their board and their opponent's board, striving to secure all their rings while hindering their opponent's progress.
Overview
In Obsession, two players (Human vs. Computer) take turns rolling a pair of six-sided dice. The numbers rolled allow players to advance their own rings (pushing them UP) or strike at their opponent's board to knock their rings back down (DOWN). Rings that remain UP when a player ends their round become locked as SAFE.

How to Play

Objective: The primary goal is to get all 10 of your rings (numbered 1 through 10) into either the UP or SAFE state. The first player to achieve this across all rings wins the game.

Components & SetupRings (1–10): Each player starts with 10 rings, all initially in the DOWN state.

Ring States: DOWN: The default starting state. UP: The ring has been moved up during the current turn. SAFE: The ring has been permanently locked at the end of a round (cannot easily be targeted or knocked back).

Game Mechanics & Turn Rules
On your turn, you roll two dice and use their values to make move commands.
1. Moving Your Own Rings (u / UP) 
Moving a ring UP changes its state from DOWN to UP, or from SAFE back to UP. You can move a ring matching individual die values: E.g., if you roll a 2 and a 4, you can move ring 2 UP and ring 4 UP (u2u4) or the sum of both dice: E.g., if you roll a 2 and a 4 (sum = 6), you can move ring 6 UP (u6).
2. Knocking Down Opponent Rings (d / DOWN)
Moving an opponent's ring DOWN changes their ring state from UP back to DOWN.You can apply DOWN moves using individual die values or their sum to disrupt the computer's board.
3. Matching Dice Rules
Full Consumption: If you use both rolled dice completely in a single move (e.g., matching both individual dice or using the combined sum), you get to roll again and take another action within the same turn!
Partial Consumption: If you only use one die value, your turn automatically ends, and control passes to the opponent.

Command Notation
When prompted with turn:, enter your action as a single string combining move types and ring numbers
Example: uXu6 = Push ring 6 UP on your board (using sum or single die), dXd4 = Push ring 4 DOWN on the opponent's board,uXdYu3d5 = Push your ring 3 UP and push opponent's ring 5 DOWN. Duplicate moves like d3d3 are invalid.

Main Menu Options
When presented with (p)lay (e)ndround (q)uit: :p (Play): Prompt for a turn: command using the current dice values.e (End Round): End your active turn. All your current UP rings lock into SAFE state, and the computer takes its automatic turns.q (Quit): Terminate the game early.

Project Architecture
The codebase is built with modular C++ OOP principles:
Die.cpp / DieManager.cpp: Handles uniform random generation for rolling single and dual 6-sided dice.
Ring.cpp: Tracks ring values (1–10) and state transitions (DOWN, UP, SAFE).
Move.cpp / Turn.cpp: Parses player input strings (e.g., "u2d5"), validates move mechanics against active dice values, and determines full/partial turn consumption.
Player.cpp: Manages a board of 10 rings and executes valid moves against self or target players.
Obsession.cpp: Orchestrates game flow, coordinates turns between human and AI players, displays the board layout, and handles win conditions.
main.cpp: Contains the primary interactive game loop and assertion unit tests.
