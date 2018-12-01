rm test
g++ $1 -o test -lGL -lGLU -lglut -std=c++11
./test
