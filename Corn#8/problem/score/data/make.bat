@echo off
mkdir tmp
rm -r data
echo Compiling ...
g++ code/controller.cpp -std=c++11 -O2 -o tmp/controller
g++ code/score.data.cpp -std=c++11 -O2 -o tmp/score.data
g++ code/score.data2.cpp -std=c++11 -O2 -o tmp/score.data2
g++ code/score.std.cpp -std=c++11 -O2 -o tmp/score.std
copy score.rules .\tmp\score.rules
echo Making ...
cd .\tmp
controller
rm controller.exe
rm score.*
cd ..
ren tmp data
pause
