# Handling Errors in Shader Code

## Workflow Complications
1. The GLSL shader code is compiled at c++ runtime, unlike c++ code which is compiled at compile time.
2. Unlike c++ code, the GLSL code runs on the GPU, which makes it impossible for the OS to catch OGL runtime errors.

Due to the above complications, we create some modules for catching and displaying GLSL errors.

## How do we do it?
OpenGL provides us functions which allow us to get information about the compiled GLSL shaders and programs. 2 of them are ```glGetShaderiv()``` and ```glGetProgramiv()```.

### We create 3 functions/modules to log the GLSL errors:
```
1. printShaderLog()
2. printProgramLog()
3. checkOpenGLError()
```