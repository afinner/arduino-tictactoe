# Tic-Tac-Toe Game with Arduino Uno

## Overview
This project implements a game of Tic-Tac-Toe using the Arduino Uno microcontroller. The game allows a person to play against a computer algorithm. Players make moves by pressing buttons, and the computer's moves are signaled by LEDs lighting up.

## Components
- Arduino Uno
- 9 LEDs (3 rows x 3 columns for the Tic-Tac-Toe board)
- 3 push buttons (for selecting rows)
- 3 push buttons (for selecting columns)
- Resistors (appropriate values for LEDs and buttons)
- Breadboard and jumper wires
- USB cable for programming the Arduino

## Features
- **User-Friendly Interface**: Simple button interface for player moves.
- **Computer Algorithm**: Intelligent algorithm that makes moves in response to the player's moves.
- **LED Display**: LEDs light up to show the current state of the Tic-Tac-Toe board.
- **Game Logic**: Complete game logic for Tic-Tac-Toe, including win/draw detection and player/computer turns.

## Explanation of files
- The ```tictactoe.ino``` file contains the basic logic to run the game
- The ```t_ard_1``` file contains the game logic to run multiple computer algorithms (Please see my AI vs BF repo)
- The ```twoxtwo``` file contains the logic for a two by two grid

## Circuit Diagram
A circuit diagram will be added here to illustrate the connections between the Arduino Uno, LEDs, and buttons.


