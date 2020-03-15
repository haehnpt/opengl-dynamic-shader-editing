#include "ShaderProgramWrapper.h"

ShaderProgramWrapper::ShaderProgramWrapper(const char * vertex_shader_path, const char * fragment_shader_path, bool update_shader_dynamically) {
	this->shaderProgram = CreateShaderProgram(vertex_shader_path, fragment_shader_path);
	this->watch_shader_files = update_shader_dynamically;
	this->vertex_shader_path = vertex_shader_path;
	this->fragment_shader_path = fragment_shader_path;
}

ShaderProgramWrapper::~ShaderProgramWrapper() {
	DeleteShaderProgram(this->shaderProgram);
}

void ShaderProgramWrapper::UseShaderProgram() {
	if (this->watch_shader_files) {
		this->watch_shader_files_counter++;
		if (this->watch_shader_files_counter == SHADER_WATCH_FREQUENCY) {
			if (this->vertex_shader_hash != hasher(std::string(ReadShader(this->vertex_shader_path))) ||
				this->fragment_shader_hash != hasher(std::string(ReadShader(this->fragment_shader_path)))) {
				UpdateShaderProgram(&this->shaderProgram,
					this->vertex_shader_path,
					this->fragment_shader_path);
			}
			this->watch_shader_files_counter = 0;
		}
	}
	glUseProgram(this->shaderProgram);
}

const char * ShaderProgramWrapper::ReadShader(const char * shader_path) {
	std::ifstream file;
	std::string * result = new std::string();
	std::string line;
	file.open(shader_path);
	if (file.is_open()) {
		while (std::getline(file, line)) {
			result->append(line);
			result->append("\n");
		}
		file.close();
	}
	return result->c_str();
}

unsigned int ShaderProgramWrapper::CreateShader(const char * shader_path, int type) {
	unsigned int shader;
	shader = glCreateShader(type);
	const char * source = ReadShader(shader_path);
	if (this->watch_shader_files) {
		if (type == GL_VERTEX_SHADER) this->vertex_shader_hash = hasher(std::string(source));
		if (type == GL_FRAGMENT_SHADER) this->fragment_shader_hash = hasher(std::string(source));
	}
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR AT SHADER COMPILATION OF " << source << "\n" << infoLog << std::endl;
	}
	return shader;
}

void ShaderProgramWrapper::DeleteShader(unsigned int shader) {
	glDeleteShader(shader);
}

unsigned int ShaderProgramWrapper::CreateShaderProgram(unsigned int vertex_shader, unsigned int fragment_shader) {
	unsigned int shader_program;
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	int success;
	char infoLog[512];
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
		std::cout << "ERROR AT LINKING OF SHADER PROGRAM\n" << infoLog << std::endl;
	}
	return shader_program;
}

unsigned int ShaderProgramWrapper::CreateShaderProgram(const char * vertex_shader_path, const char * fragment_shader_path) {
	system("cls");
	unsigned int vertex_shader = CreateShader(vertex_shader_path, GL_VERTEX_SHADER);
	unsigned int fragment_shader = CreateShader(fragment_shader_path, GL_FRAGMENT_SHADER);
	unsigned int shader_program = CreateShaderProgram(vertex_shader, fragment_shader);
	DeleteShader(vertex_shader);
	DeleteShader(fragment_shader);
	return shader_program;
}

void ShaderProgramWrapper::DeleteShaderProgram(unsigned int shader_program) {
	glDeleteProgram(shader_program);
}

void ShaderProgramWrapper::UpdateShaderProgram(unsigned int * shader_program, const char * vertex_shader_path, const char * fragment_shader_path) {
	DeleteShaderProgram(*shader_program);
	*shader_program = CreateShaderProgram(vertex_shader_path, fragment_shader_path);
}