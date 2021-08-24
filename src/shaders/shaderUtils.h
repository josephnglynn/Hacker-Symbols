//
// Created by joseph on 11/04/2021.
//

#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    void useShader() const;


};

