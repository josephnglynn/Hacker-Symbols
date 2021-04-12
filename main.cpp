//
// Created by joseph on 11/04/2021.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <map>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <shaderUtils.h>


#define FONT_PATH "Roboto-Regular.ttf"

float WINDOW_WIDTH = 1920;
float WINDOW_HEIGHT = 1080;

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

std::map<char, Character> Characters;

unsigned int VAO, VBO;

void RenderRow(Shader &shader, std::string row, float x, float y, float scale, glm::vec3 color) {

    shader.useShader();
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator c;
    for (c = row.begin(); c != row.end(); c++) {
        Character character = Characters[*c];

        float xPos = x + (float) character.Bearing.x * scale;
        float yPos = y - (float) (character.Size.y - character.Bearing.y) * scale;

        float w = (float) character.Size.x * scale;
        float h = (float) character.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
                {xPos,     yPos + h, 0.0f, 0.0f},
                {xPos,     yPos,     0.0f, 1.0f},
                {xPos + w, yPos,     1.0f, 1.0f},

                {xPos,     yPos + h, 0.0f, 0.0f},
                {xPos + w, yPos,     1.0f, 1.0f},
                {xPos + w, yPos + h, 1.0f, 0.0f}
        };

        glBindTexture(GL_TEXTURE_2D, character.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (float) (character.Advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}







int main() {

    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow((int) WINDOW_WIDTH, (int) WINDOW_HEIGHT, "Hacker Symbols", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, [](GLFWwindow* callbackWindow, int width, int height){
        WINDOW_HEIGHT = (float)height;
        WINDOW_WIDTH = (float)width;
    });

    if (glewInit() != GLEW_OK) {
        std::cerr << "ERROR GLEW DIDN'T INIT" << std::endl;
        return -1;
    }

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << glGetString(GL_VERSION) << std::endl;

    //WINDOW IS INIT NOW TO INIT FREE TYPE
    FT_Library ft_library;

    if (FT_Init_FreeType(&ft_library)) {
        std::cerr << "ERROR FREETYPE DIDN'T INIT" << std::endl;
        return -1;
    }


    FT_Face font;
    if (FT_New_Face(ft_library, FONT_PATH, 0, &font)) {
        std::cerr << "ERROR FAILED TO LOAD FONT" << std::endl;
        return -1;
    }

    FT_Set_Pixel_Sizes(font, 0, 48);

    if (FT_Load_Char(font, 'X', FT_LOAD_RENDER)) {
        std::cerr << "ERROR CAN'T LOAD CHAR" << std::endl;
        return -1;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(font, c, FT_LOAD_RENDER)) {
            std::cerr << "ERROR CAN'T LOAD CHAR: " << c << std::endl;
            return -1;
        }

        unsigned int characterTexture;
        glGenTextures(1, &characterTexture);
        glBindTexture(GL_TEXTURE_2D, characterTexture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                (GLsizei)font->glyph->bitmap.width,
                (GLsizei)font->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                font->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
                characterTexture,
                glm::ivec2(font->glyph->bitmap.width, font->glyph->bitmap.rows),
                glm::ivec2(font->glyph->bitmap_left, font->glyph->bitmap_top),
                static_cast<unsigned int>(font->glyph->advance.x)
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }

    FT_Done_Face(font);
    FT_Done_FreeType(ft_library);


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    Shader shader("shader.vert", "shader.frag");
    glm::mat4 projection = glm::ortho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT);
    shader.useShader();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);

        RenderRow(shader, "This is a test", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 1.0f, glm::vec3(1, 1, 1));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}