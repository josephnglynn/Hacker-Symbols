//
// Created by joseph on 12/04/2021.
//

#ifndef HACKER_SYMBOLS_TEXT_RENDERER_H
#define HACKER_SYMBOLS_TEXT_RENDERER_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <map>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "shaders/shaderUtils.h"
#include <GL/glew.h>


#define FONT_PATH "Roboto-Regular.ttf"


struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class TextRenderer {
public:
    static unsigned int VAO, VBO;
    static unsigned int characterHeight;
    static std::map<char, Character> Characters;
    static Shader *textShader;

    //void setUpTextRenderer(float WINDOW_WIDTH, float WINDOW_HEIGHT, unsigned int fontHeight);
    static void setUpTextRenderer(float, float, unsigned int);

    //void RenderRow(Shader theShader, std::string theStringOfCharacters, float theXPosition, float theYPosition, float scale, glm::vec3 theColor);
    static void RenderRow(Shader, std::string, float, float, float, glm::vec3);
};


#endif //HACKER_SYMBOLS_TEXT_RENDERER_H
