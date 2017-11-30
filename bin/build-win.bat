@echo off

if not exist lib\gl3w\src\gl3w.c (
  pushd lib\gl3w
  .\gl3w_gen.py
  popd
)

if not exist build\win (
  mkdir build\win
)

pushd build\win

set PATH=.;C:\Users\lzubiaur\cmake-3.3.2\bin;%PATH% 

set BUILD_TYPE=Release

if /I "%1" == "debug" (
  set BUILD_TYPE=Debug
  echo "Build DEBUG"
)

cmake.exe ^
    -G "Visual Studio 14 2015" ^
    -DBUILD_WIN=TRUE ^
    -DCMAKE_SYSTEM_VERSION=10.0 ^
    -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
    ..\..

cmake.exe --build . --target install --config %BUILD_TYPE%

popd
