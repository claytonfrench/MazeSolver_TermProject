@echo off
if not exist bin (
   mkdir bin
)
pushd src
g++ *.cpp -o ../bin/maze.exe
popd


