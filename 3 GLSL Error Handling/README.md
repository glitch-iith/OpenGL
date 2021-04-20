# Handling Errors in Shader Code

## 1. Workflow Complications
1. The GLSL shader code is compiled at c++ runtime, unlike c++ code which is compiled at compile time.
2. Unlike c++ code, the GLSL code runs on the GPU, which makes it impossible for the OS to catch OGL runtime errors.

Due to the above complications, we manually create some modules for catching and displaying GLSL errors.

## 2. How do we do it?
OpenGL provides us 2 important functions which allow us to get information about the compiled GLSL shaders and programs. 2 of them are [```glGetShaderiv()```](https://docs.gl/es3/glGetShaderiv) and [```glGetProgramiv()```](https://docs.gl/gl4/glGetProgram).

If you visit the documentation pages href'ed, you'll see that the above functions will let us know the value of the paramater of the shader object that we pass to the functions.
For a shader object, the following parameters are available:
1. GL_DELETE_STATUS
2. GL_COMPILE_STATUS
3. GL_INFO_LOG_LENGTH
4. GL_SHADER_SOURCE_LENGTH
5. 
For example, if we call the function with the 2nd parameter listed above for a vertex shader, it would look like this:
```
glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertex_compiled);
```
Where vShader is the vertex shader object that you've created in the last project, and vertex_compiled is a ```GLuint``` whose value is set by this function call.

## 3. We define three functions/modules in this project to log the GLSL errors:
```
1. printShaderLog()
2. printProgramLog()
3. checkOpenGLError()
```
