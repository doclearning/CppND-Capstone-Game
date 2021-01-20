# CPPND: Capstone Game - Landerlike

Landerlike game. Vaguely built around the Capstone Snake project (Capstone Option 2). This game is fully playable, contains random ship spawning, random pad spawning and size, some basic level progression, in-game text, basic physics and collisions, easily-extendable input, and flexible line-rendering.

The project contribution, however, is more in its architecture. It is an (albeit trivial) component-based game engine. This makes the game quite flexible and extensible. Random box-line terrain, asteroids, ship trails, explosions, etc could be added fairly easily.

**Future Work**

* Parallelise collision, game and render work
* Asteroids, or boxes, randomly in level
* Render ship thrust
* Render ship explosion
* Variadic templates to make Component creation/parameterisation cleaner
* Use playtime to affect score
* File IO for meshes, and probably settings
* Mesh colliders
* Fuel
* Procedural terrain, using mesh collider (maybe overhangs)
	* Place pad on any surface with accessiblity (would likely require raycasting/intersection support, and a heuristic)
* More genericisation of components and gameobjects
* Data structure for collisions
* Tidy-up level and game states, and theirtransitions
* Move ownership of a lot of stuff out of ship into game
  * And then clean-up structure of game

-----------------

**Appreciate usage of this font ['Arcade'](https://www.dafont.com/arcade-pizzadude.font).**

## Build Dependencies

### Requirements

* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
  * CmakeLists.txt uses [pkg-config](https://www.freedesktop.org/wiki/Software/pkg-config/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL2_image and SDL2_ttf
  * Installation instructions can be found [here](https://www.libsdl.org/projects/SDL_image/) and [here](https://www.libsdl.org/projects/SDL_ttf/)
  * use: [sudo apt-get install libsdl2-image-dev libsdl2-ttf-dev] on workspace
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* Google Mathfu and Vectorial for vector math
  * Embedded for laziness

### Instructions

1. Clone this repo
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./LanderClone`

## Code Structure Overview

**Execution and Game**

- Main - Instantiates a few core objects, and launches game.
- Game - Handles state and runtime for game. Encapsulates and owns all game happenings. Observer of 'game' input events.

**Secondary/Wrapped Libraries**

- Renderer - Wraps SDL render contexts, and has some core methods for preping the canvas and rendering text.
- Controller - Singleton that handles all events. Observer subject. Singleton to reduce it being passed around, and enable global subscription.
- Collision Handler - Singleton that handles and processess all game collisions. Purely aabb for this game. Extendible. Observer subject. Singleton as above.

**Game Objects**

- GObject - Core gameobject. Not purely virtual to minimise code repeition, as lots of shared functions. Component, transform, owner.
- Ship - Abstraction of Gobject. Has some game logic (probably should have less). Observer of collision events. Uses all components.
- Ground - Abstraction of Gobject. Represents ground.
- Pad - Abstraction of Gobject. Represents landing pad.

**Components**

- IComponent - Pure virtual class that allows templated genericisation of components.
- BoxColliderComponent - Implements IComponent. AABB collision component. Light.
- MeshRenderComponent - Implements IComponent. Mesh rendering component. Utilises renderer context. Owns mesh.
- PhysicsEntityComponent - Implements IComponent. Physics component. Represents trivial newtonian physics states.
- ShipInputComponent - Implements IComponent. Observer of input events.

**Utils**

- Observer - Observer pattern implementation.
- Singleton - Singleton pattern. Probably not thread-safe.

**Other**

- Transform - Transform struct. Owned by GObject.

## Rubric Satisfaction

**Readme**

- ✅ A README with instructions is included with the project
- ✅ The README indicates which project is chosen.
- ✅ The README includes information about each rubric point addressed.

**Compiling and Testing**

- ✅ The submission must compile and run.

**Loops, Functions, I/O**

- ✅ The project demonstrates an understanding of C++ functions and control structures. (any class)
- The project reads data from a file and process the data, or the program writes data to a file.
- ✅ The project accepts user input and processes the input. (e.g. controller.cpp, game.cpp[ln93])

**Object Oriented Programming**

- ✅ The project uses Object Oriented Programming techniques. (all components, gobjects)
- ✅ Classes use appropriate access specifiers for class members. (any class)
- ✅ Class constructors utilize member initialization lists. (any class, e.g. PhysicsEntityComponent.cpp)
- ✅ Classes abstract implementation details from their interfaces. (any class. e.g. PhysicsEntityComponent.h[ln36])
- ✅ Classes encapsulate behavior. (many classes. e.g. ship.cpp)
- ✅ Classes follow an appropriate inheritance hierarchy. (all components (pure virtual), all gobjects)
- ✅ Overloaded functions allow the same function to operate on different parameters. (renderer.h[ln21])
- ✅ Derived class functions override virtual base class functions. (all components and gobjects, e.g. pad.h[ln15])
- ✅ Templates generalize functions in the project. (e.g. gobject.h[ln39])

**Memory Management**

- ✅ The project makes use of references in function declarations. (many classes, e.g. shipInputComponent.h[ln16])
- ✅ The project uses destructors appropriately. (when required, e.g. renderer.cpp[ln46], meshRenderComponent.h[ln5])
- ✅ The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. (many places, e.g. collisionHandler.cpp, renderer.cpp)
- The project follows the Rule of 5.
- ✅ The project uses move semantics to move data, instead of copying it, where possible (as often as possible, e.g. meshRenderComponent.cpp[ln57])
- ✅ The project uses smart pointers instead of raw pointers. (where possible, e.g. component storage in gobject.h[ln65])

**Concurrency**
- The project uses multithreading.
- A promise and future is used in the project.
- A mutex or lock is used in the project.
- A condition variable is used in the project.
