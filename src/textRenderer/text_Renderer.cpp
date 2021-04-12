//
// Created by joseph on 12/04/2021.
//

#include "text_Renderer.h"

unsigned int TextRenderer::VAO, TextRenderer::VBO;
std::map<char, Character> TextRenderer::Characters;
Shader* TextRenderer::textShader;


void TextRenderer::RenderRow(Shader shader, std::string row, float x, float y, float scale, glm::vec3 color) {

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


void TextRenderer::setUpTextRenderer(float WINDOW_WIDTH, float WINDOW_HEIGHT) {
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    FT_Library ft_library;

    if (FT_Init_FreeType(&ft_library)) {
        std::cerr << "ERROR FREETYPE DIDN'T INIT" << std::endl;
        std::exit(-1);
        
    }


    FT_Face font;
    if (FT_New_Face(ft_library, FONT_PATH, 0, &font)) {
        std::cerr << "ERROR FAILED TO LOAD FONT" << std::endl;
        std::exit(-1);
    }

    FT_Set_Pixel_Sizes(font, 0, 48);

    if (FT_Load_Char(font, 'X', FT_LOAD_RENDER)) {
        std::cerr << "ERROR CAN'T LOAD CHAR" << std::endl;
        std::exit(-1);
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(font, c, FT_LOAD_RENDER)) {
            std::cerr << "ERROR CAN'T LOAD CHAR: " << c << std::endl;
            std::exit(-1);
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


    textShader = new Shader("shader.vert", "shader.frag");
    glm::mat4 projection = glm::ortho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT);
    (*textShader).useShader();
    glUniformMatrix4fv(glGetUniformLocation((*textShader).ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

}