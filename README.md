# Tetris
 This is an attemt to replicate the "famous" Tetris game from scratch. 
 In order to approach this task I have created a Matrix data type class in order to provide basic functionality for the game. 
 
 Funcitonality of the game is ensured by using matrices to represent the individual Tetracubes needed to play this game. 

<img src="Tetris.png" />

 Rendering is done with the SDL library.
 ## Dependencies for Running Tetris Locally
 * cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Tetris`.

## Rubric points addressed
### Loops, Functions, I/O
| Rubric point  | Location |
| ------------- | ------------- |
| The project demonstrates an understanding of C++ functions and control structures.  |   Yes, check all the files
|The project accepts user input and processes the input.  |   [controller](src/controller.cpp)

### Object Oriented Programming
| Rubric point  | Location |
| ------------- | ------------- |
| The project uses Object Oriented Programming techniques.  |   Yes, check all the files
Classes use appropriate access specifiers for class members. | Yes, check all the files
Class constructors utilize member initialization lists. | Yes, check all the files
Classes abstract implementation details from their interfaces. | Yes, check all the files
Classes encapsulate behavior. | Yes, check all the files | 
Templates generalize functions in the project. | [matrix](src/matrix.h)

### Memory Management
| Rubric point  | Location |
| ------------- | ------------- |
| The project makes use of references in function declarations.  |  Yes, check all the files 
The project uses destructors appropriately. | [matrix](src/matrix.h) / [tetris](src/tetris.cpp)
The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. | [matrix](src/matrix.h)
The project follows the Rule of 5. | [matrix](src/matrix.h)

