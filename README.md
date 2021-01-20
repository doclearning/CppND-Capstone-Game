# CPPND: Capstone Game - Landerlike

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

//Rewrite project description

## Build Dependencies

### Requirements

* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

  //JAQ Review

### Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

  //JAQ Check

## Code Structure Overview

**Execution and Game**

- Main

- Game

**Secondary/Wrapped Libraries**


- Renderer

- Controller

- Collision Handler

**Game Objects**

- GObject

- Ship

- Ground

- Pad

**Components**

- BoxCollider

- MeshRender

- PhysicsEntity

- ShipInput

**Utils**

- Observer

- Singleton

## Rubric Satisfaction

**Readme**

- ✅ A README with instructions is included with the project
- ✅ The README indicates which project is chosen.
- ✅ The README includes information about each rubric point addressed.

**Compiling and Testing**

- ✅ The submission must compile and run.

**Loops, Functions, I/O**

- ✅ The project demonstrates an understanding of C++ functions and control structures.
- The project reads data from a file and process the data, or the program writes data to a file.
- ✅ The project accepts user input and processes the input.

**Object Oriented Programming**

- ✅ The project uses Object Oriented Programming techniques.
- ✅ Classes use appropriate access specifiers for class members.
- ✅ Class constructors utilize member initialization lists.
- ✅ Classes abstract implementation details from their interfaces.
- ✅ Classes encapsulate behavior.
- ✅ Classes follow an appropriate inheritance hierarchy.
- ✅ Overloaded functions allow the same function to operate on different parameters.
- ✅ Derived class functions override virtual base class functions.
- ✅ Templates generalize functions in the project.

**Memory Management**

- ✅ The project makes use of references in function declarations.
- ✅ The project uses destructors appropriately.
- ✅ The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
- The project follows the Rule of 5.
- ✅ The project uses move semantics to move data, instead of copying it, where possible.
- ✅ The project uses smart pointers instead of raw pointers.

**Concurrency**
- The project uses multithreading.
- A promise and future is used in the project.
- A mutex or lock is used in the project.
- A condition variable is used in the project.
