# Computer-Graphics
#### Setup OpenGL on Windows (tested on MinGW):
  1. [Download freeglut](https://www.transmissionzero.co.uk/software/freeglut-devel/)
  2. Move "freeglut.dll" to the "/bin" of your compiler
  3. Move "/lib" content to the "/lib" of your compiler
  4. Move "/GL" (from "/include") to the "/include" of your compiler [OPT*]
  5. Compile using these commands (I made .bat and .sh scripts for it):
      * Windows:
        * g++ name.cpp -o test.o -c
        * g++ test.o -o test.exe -lglu32 -lopengl32 -lfreeglut
      * Linux:
        * g++ name.cpp -o test -lGL -lGLU -lglut

  [OPT*] Also put into the 32 bits version folder, if it still doesn't work


#### Useful links:
  * [Documentation](https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/)
  * [Examples](http://www.swiftless.com/opengltuts.html)
  * [Tutorials](http://www.inf.pucrs.br/~manssour/OpenGL/Tutorial.html)
  * [Setup](https://www3.ntu.edu.sg/home/ehchua/programming/opengl/HowTo_OpenGL_C.html)
  * [Transformations](http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/)
  * [Light](https://www.glprogramming.com/red/chapter05.html)
