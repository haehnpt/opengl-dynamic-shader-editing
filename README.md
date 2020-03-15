# opengl-dynamic-shader-editing
Introduce a Shader Program Wrapper to enable dynamic editing of shaders at runtime

# How to use

Initialize the Shader Program Wrapper with a Vertex Shader and a Fragment Shader:
```
// Use ShaderProgramWrapper.h to create a shader program wrapper
ShaderProgramWrapper spw("shaders/vertex_shader.shader", "shaders/fragment_shader.shader", true);
```

If the last parameter is set to _false_, the shader files will not be watched.

Use the underlying Shader Program to render:
```
spw.UseShaderProgram();
```

That's all!
