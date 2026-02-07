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

## Build instructions:

1. The build requires some dependencies that I did not have previously installed. Run:
``sudo apt update
sudo apt install libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev \
                 libxi-dev libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev \
                 libudev-dev libopenal-dev libflac-dev libvorbis-dev libogg-dev \ 
                 libfreetype6-dev```

This did the trick for me.

2. I also had to add:
- ```#include <cstdint>``` to ONRL/src/main.cpp
- ```#include <cstdint>``` and ```#include <string>``` to ONRL/src/console.h

Depending on your cpp version, it might not be needed?

3. (Optional) Additionally I changed the move controls from hjkl to wasd in main.cpp lines 41-44.

4. Finaly, build:
```cd ONRL
mkdir build
cmake -B build -S .
cmake --build build
./build/ONRL || build/Debug/ONRL.exe```

TODO: CI configuration is provided in .github/workflows/ci.yml

## Tools and Analysis
(To be filled in with results from cppcheck, Valgrind, tests, etc.)


## Conclusions
(To be completed after analysis)
