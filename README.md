# llp
llp lab1

test are running in main func

to build windows:

SET CMAKE_PATH="C:\Program Files\JetBrains\CLion 2022.1\bin\cmake\win\bin\cmake.exe"

SET CMAKE_NINJA_PATH="C:/Program Files/JetBrains/CLion 2022.1/bin/ninja/win/ninja.exe"

%CMAKE_PATH% -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=$CMAKE_NINJA_PATH$ -G Ninja -S . -B build-dir

%CMAKE_PATH% --build build-dir --target all

linux:

cmake . -B build-dir

cmake --build build-dir --target all
