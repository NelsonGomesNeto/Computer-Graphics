del test.exe
del test.o
g++ %1 -o test.o -c -std=c++17
g++ test.o -o test.exe -lglu32 -lopengl32 -lfreeglut -std=c++17
test.exe