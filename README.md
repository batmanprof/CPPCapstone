# C++ Capstone
Capstone Project for Udacity's CPP ND

# Five-in-a-raw
This project implements a console based environment in which the game Five-in-a-row can be played. Also two (somewhat primitive) AI players is provided.

![Screenshot](./FiveInARaw.png)

## Game Description
The game is played by two players on a 15x15 checked grid. Alternatly they put a mark (1st player: X, 2nd player: O) into one cell. The first player who collects five marks next to each others (vertically, horizontally or diagonally) wins.

## How to use program
* Go to the folder containing the executable (see building instruction later)
* Start the executable
* Select the 1st player (human or AI)
* Select the 2nd player (human or AI)
* Use arrow keys and space to put a mark into the grid (provided it is human's turn)
* You can quit anytime with key 'q' during the game

# Building Instructions

## Dependencies
You need development verison of library `ncurses` installed. In Linux environment you install the library this way: 

```
sudo apt install libncurses5-dev libncursesw5-dev
```

## Building
Go to the project library and follow these steps:

```
mkdir build
cd build
cmake ..
make
```

# File and Class structure

The project contains the following files and classes
* main.cpp - containing just the `main()` function
  * No classes in it
* screen.h and screen.cpp
  * Class `Screen` - Responsible for handling the screen and screen logic
* game.h and game.cpp
  * Class `Game` - Responsible for a game (match). If contains all the information from the beginning of the match, and it responsible for determining if the match is over.
* ai.h and ai.cpp
  * Class `AI` - Abstract ancestor class for all AI player
  * Class `AIRandomAll` - AI player class (rather dumb, playing randomly)
  * Class `AIRandomClose` - AI player class (a tiny bit less dumb, but still dumb, playing randomly, but not too far from existing marks)
    
# Addressed Rubric Points

## 1. 

### Loops, Functions, I/O - The project accepts user input and processes the input

The project accepts input from a user as part of the necessary operation of the program:

All I/O related function is implemented in class `Screen`. I used `getch()` from `ncurses` to get keyboard input from the user. 
One example is in line 84 of `screen.cpp`. This line is part of the method `getNextStep` which is responsible for getting the next move of the human player (it is handling the arrow-keys and space). 

## 2.

### Object Oriented Programming - The project uses Object Oriented Programming techniques.

The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks:

Except for `main.cpp`, I used only classes with attributes and methods. See the section "File and Class Structure" above to see which source code file contains which class.

## 3.

### Object Oriented Programming - Classes use appropriate access specifiers for class members.

All class data members are explicitly specified as public, protected, or private:

You can check this in the header files (screen.h, game.h, ai.h).

## 4.

### Object Oriented Programming - Class constructors utilize member initialization lists.

All class members that are set to argument values are initialized through member initialization lists:

See these locations:
* screen.cpp: line 9
* game.cpp: line 5
* ai.h: line 14

## 5.

### Object Oriented Programming - Derived class functions override virtual base class functions.

One member function in an inherited class overrides a virtual base class member function:

See ai.h, line 9 -> 23 and 39.

