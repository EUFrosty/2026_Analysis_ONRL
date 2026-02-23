# 2026_Analysis_ONRL

Bojan Velickovic 1070/2024

The project analyzed in this assignment is https://github.com/nullspeaker/ONRL, main branch.
The specific commit is ```12efcde267c00f120b9b16ad7800fe117dd44d9c```. <br>
<br>
This repository has been inactive for some time, so the project in question is not complete. It can still run and has its core functioanlity:
- game window
- terrain
- player character
- enemies
- movement
- object collision
<br>
I actually forked that repository to add:


- ```#include <cstdint>``` to ONRL/src/main.cpp
- ```#include <cstdint>``` and ```#include <string>``` to ONRL/src/console.h

and change the movement controls to wasd from hjkl in main.cpp lines 41-44.<br> <br>
The inclusions were needed becouse of cpp version missmatch. It might not be needed for everyone, but it can't hurt either.


## Build instructions:

1. The build requires some dependencies that I did not have previously installed. Run: <br>
```
sudo apt update
sudo apt install libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev \
                 libxi-dev libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev \
                 libudev-dev libopenal-dev libflac-dev libvorbis-dev libogg-dev \ 
                 libfreetype6-dev
```
<br>
This did the trick for me.

2. Build:
```
cd ONRL
mkdir build
cmake -B build -S .
cmake --build build
./build/ONRL || build/Debug/ONRL.exe
```

CI configuration is provided in .github/workflows/ci.yml

## Tools and Analysis
1. Cppcheck <br>
   ```cd ONRL``` and run ```cppcheck --enable=all --inconclusive --quiet src/ 2>../tools/cppcheck/cppcheck.log``` which runs the tool on ONRL src/ code. <br>
   ```--enable=all``` runs checks for everything (style, performance, portability...)<br>
   ```--inconclusive``` reports issues that are not 100% certain<br>
   ```--quiet``` only shows warnings/errors<br>
   ```2>../tools/cppcheck/cppcheck.log``` redirects the output into a log file at the provided path<br>
<br><br>
   In the log file we can see that there are a lot of warnings that the tool could not find the libraries included in the code (things like iostream, SFML/Graphics.hpp, optional, cstdint...). We can safely ignore these warnings.<br>
   Additional warnings are things like:
     - different names for arguments in the function definition and declaration
     - redundant or unnecessary if clauses
     - unused variables and functions
     - not passing vectors and strings by reference but rather by name which copies the whole thing
     - use existing std library functions instead of implementing new ones that do the same thing
  
2. Clang-tidy<br>
   ```cd ONRL``` and run 
   ```
   clang-tidy src/*.cpp -checks='bugprone-*,performance-*,modernize-*,readability-*,cppcoreguidelines-*,-cppcoreguidelines-avoid-magic-numbers' -- -I./src 2>&1 | tee ../tools/clang-tidy/clang-tidy.log
   ``` 
   which runs the tool on ONRL src/ code. <br>

  In the log we can find 104 warnings and 2 errors. <br>
  Regarding the errors, they are both in connection with the SFML (Simple and Fast Multimedia Library). Clang-tidy can't find the library, which is to be expected since the dependencies are built using cmake and are located in a separate directory. This means that these errors are not really errors, just indicators that the necessary dependencies were not included in the directory in which we ran clang-tidy.<br>
  Regarding the warnings, let's split them up by type:
  1. bugprone
     - a couple of warnings for easily swappable parameters of functions that share the same type
     - implicit conversion from uint32_t to unsigned long due to multiplication of two uint32_t values
    
  2. performance
     - not passing parameters by reference when that would be more optimal
     - using larger types than necessary
    
  3. modernize
     - when to use a trailing return type
    
  4. readability
     - mostly paramaeter naming issues
     - replacing "magic numbers" with named constants
     - leaving out braces {} for if blocks when they have only one line
     - ...
    
  5. cppcoreguidelines
     - avoid pointer arithmetic
     - replacing macros with enums
     - avoid creating C-style arrays, should use ```std::array<>``` instead
     - ...
3. Valgrind<br>
```cd ONRL``` and run ```valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./build/ONRL &>../tools/valgrind/valgrind_log.txt``` which runs the executable ONRL file and tracks memory leaks.<br>
- ```--leak-check=full``` - show all leaks
- ```--show-leak-kinds=all``` - categorizes all kinds of leaks
- ```--track-origins=yes``` - shows where uninitialized values come from

The short leak summary is:
```
LEAK SUMMARY:
    definitely lost: 184 bytes in 1 blocks
    indirectly lost: 1,825 bytes in 2 blocks
    possibly lost: 0 bytes in 0 blocks
    still reachable: 74,869 bytes in 558 blocks
    suppressed: 0 bytes in 0 blocks
```
While the full leak report can be found in the log.<br>
- As we can see, there is a lot of still reachable memory. That is memory that was left allocated at program exit but it was still reachable. This in it self is not a big problem.For example, in record 74/130 we have still reachable memory that happened due to ```gfx::Console::Console(unsigned int, unsigned int, std::string, unsigned int)``` which creates a console i.e. a game window. The practice of leaveing this memory allocated at program end without losing the pointer to it seems standard for GUI applications that rely on the OS to clean up such memory on program exit.<br>
- In record 120/130 we have our only definitely lost memory, which is a genuine memory leak. However, the leak didn't occur in the repository code, but instead it happened in the code of the libdbus-1 library.<br>
- In records 83/130 and 119/130 we have our only two instances of indirectly lost memory. Again, both of these memory leaks happen in the libdbus-1 library, not in the original ONRL source code.<br>

4. Unit testing
TODO
5. Lizart
TODO
6. Hyperfine
TODO


## Conclusions
(To be completed after analysis)
