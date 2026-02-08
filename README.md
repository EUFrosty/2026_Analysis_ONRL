# 2026_Analysis_ONRL

Bojan Velickovic 1070/2024

The project analyzed in this assignment is https://github.com/nullspeaker/ONRL, main branch.
The specific commit is ```12efcde267c00f120b9b16ad7800fe117dd44d9c```. <br>
<br>
This repository has been inactive for some time, so the project in question is not complete. It can still run and has core its functioanlity:
- game window
- terrain
- player character
- enemies
- movement
- object collision
<br>
I actually forked that repository to add:


- ```#include``` <cstdint> to ONRL/src/main.cpp
- ```#include <cstdint>``` and ```#include <string>``` to ONRL/src/console.h

and change the movement controls to wasd from hjkl in main.cpp lines 41-44.<br> <br>
The inclusions were needed becouse of cpp version missmatch. It might not be needed for everyone, but it can't hurt eather.


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
1. Cppcheck
   ```cd ONRL``` and run ```cppcheck --enable=all --inconclusive --quiet src/ 2>../tools/cppcheck/cppcheck.log``` which runs the tool on ONRL src/ code. <br>
   ```--enable=all``` runs checks for everything (style, performance, portability...)<br>
   ```--inconclusive``` reports issues that are not 100% certain<br>
   ```--quiet``` only shows warnings/errors<br>
   ```2>../tools/cppcheck/cppcheck.log``` redirects the output into a log file at the provided path<br>
<br><br>
   In the log file we can see that there are a lot of warnings that the tool could not find the libraries included in the code (things like iostream, SFML/Graphics.hpp, optional, cstdint...). We can safely ignore these warnings.<br>
   Additional warnings are things like:
     - different names for arugments in the funtion definition and declaration
     - redundant or unnecessary if clauses
     - unused variables and functions
     - not passing vectors and strings by reference but rather by name which copies the whole thing
     - use existing std library functions instead of implementing new ones that do the same thing
  
2. 


## Conclusions
(To be completed after analysis)
