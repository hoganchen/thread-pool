if exist build (
    rmdir /s /q build
)

mkdir build
cd build

@REM 使用GCC编译
@REM cmake ..
@REM cmake --build . --config release

@REM 使用MinGW32 Cmake编译
@REM cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_CC_COMPILER=gcc -DCMAKE_MAKE_PROGRAM=mingw32-make -G "MinGW Makefiles" ..
cmake -G "MinGW Makefiles" ..
mingw32-make
