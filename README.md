# Computer-Graphics
#### Setup OpenGL on Windows (tested on MinGW):
  1. [Download freeglut](https://www.transmissionzero.co.uk/software/freeglut-devel/)
  * Move "freeglut.dll" to your Windows/System32 (it's on "/bin")
  * Move "/lib" content to the "/lib" of your compiler
  * Move "/GL" (from "/include") to the "/include" of your compiler
  * Compile using these commands (I made a .bat for it):
    * g++ name.cpp -o test.o -c
    * g++ test.o -o test.exe -lglu32 -lopengl32 -lfreeglut


#### Useful links:
  * [Documentation](https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/)
  * [Examples](http://www.swiftless.com/opengltuts.html)
  * [Setup](https://www3.ntu.edu.sg/home/ehchua/programming/opengl/HowTo_OpenGL_C.html)
