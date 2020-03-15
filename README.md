# opengl-dynamic-shader-editing
This Shader Program Wrapper enables the user to dynamically edit shaders
at runtime. It can be either used for debugging shaders or while presenting 
the effects of changes to the shader code.

## How to use

Initialize the Shader Program Wrapper with a Vertex Shader and a Fragment Shader:
```c++
ShaderProgramWrapper spw("shaders/vertex_shader.shader", 
  "shaders/fragment_shader.shader", 
  true);
```

If the last parameter is set to _false_, the shader files will not be watched.

Use the underlying Shader Program to render:
```c++
spw.UseShaderProgram();
```

You can edit the shader files at runtime and 
changes will apply after saving.

