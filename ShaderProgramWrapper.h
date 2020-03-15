// Shader Program Wrapper
// - Simplify creating shader programs
// - Enable dynamic shader editing
// Author: Patrick Hähn

#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <glad/glad.h>

#define SHADER_WATCH_FREQUENCY 60

class ShaderProgramWrapper {
public:
	ShaderProgramWrapper(const char * vertex_shader_path, const char * fragment_shader_path, bool update_shader_dynamically = false);
	~ShaderProgramWrapper();
	void UseShaderProgram();
private:
    std::hash<std::string> hasher;
	bool watch_shader_files = false;
	unsigned int watch_shader_files_counter = 0;
	unsigned int shaderProgram;
	unsigned int vertex_shader_hash;
	unsigned int fragment_shader_hash;
	const char * vertex_shader_path;
	const char * fragment_shader_path;
	const char * ReadShader(const char * shader_path);
	unsigned int CreateShader(const char * shader_path, int type);
	void DeleteShader(unsigned int shader);
	unsigned int CreateShaderProgram(unsigned int vertex_shader, unsigned int fragment_shader);
	unsigned int CreateShaderProgram(const char * vertex_shader_path, const char * fragment_shader_path);
	void DeleteShaderProgram(unsigned int shader_program);
	void UpdateShaderProgram(unsigned int * shader_program, const char * vertex_shader_path, const char * fragment_shader_path);
};