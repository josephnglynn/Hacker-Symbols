//
// Created by joseph on 11/04/2021.
//



#include "shaderUtils.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    std::string vertexShader, fragmentShader;
    std::ifstream vertexShaderFile, fragmentShaderFile;

    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);

        std::stringstream vertexShaderStream, fragmentShaderStream;

        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexShader = vertexShaderStream.str();
        fragmentShader = fragmentShaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cerr << "ERROR CAN'T READ SHADER" << std::endl;
    }

    const char *vertexShaderCode = vertexShader.c_str();
    const char *fragmentShaderCode = fragmentShader.c_str();

    unsigned int vertex, fragment;
    int success;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
        std::cerr << "ERROR VERTEX SHADER COMPILING FAILED\n" << infoLog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(fragment, 1024, NULL, infoLog);
        std::cerr << "ERROR FRAGMENT SHADER COMPILING FAILED\n" << infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(ID, 1024, NULL, infoLog);
        std::cerr << "ERROR PROGRAM FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}


void Shader::useShader() const {
    glUseProgram(ID);
}