#include "stdafx.h"
#include "TextRenderer.hpp"

TextRenderer::TextRenderer() : shader_(std::make_unique<Shader>(Config::text_vertex_path, Config::text_fragment_path)), vao_{}, vbo_{}
{
	Load();

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::Init()
{
    projection_matrix_ = glm::ortho(0.0f, static_cast<float>(Config::width), 0.0f, static_cast<float>(Config::height));
    Update();
}

void TextRenderer::UpdateProjectionMatrix(const int width, const int height)
{
	projection_matrix_ = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
    scale_ = glm::vec2(width / static_cast<float>(Config::width), height / static_cast<float>(Config::height));
}

void TextRenderer::Update() const
{
	shader_->Bind();

	shader_->SetMat4(projection_matrix_, "projectionMatrix");

	shader_->Unbind();
}

void TextRenderer::Render(const std::u16string& text, float x, float y, const glm::vec3 color)
{
    shader_->Bind();

    shader_->SetVec3(color, "textColor");

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao_);

    for (const auto& c : text) 
    {
	    const Character ch = characters_[c];

	    const float position_x = x + ch.bearing.x * scale_.x;
	    const float position_y = y - (ch.size.y - ch.bearing.y) * scale_.y;

	    const float w = ch.size.x * scale_.x;
	    const float h = ch.size.y * scale_.y;

	    const float vertices[6][4] = 
        {
            { position_x,     position_y + h,   0.0f, 0.0f },            
            { position_x,     position_y,       0.0f, 1.0f },
            { position_x + w, position_y,       1.0f, 1.0f },

            { position_x,     position_y + h,   0.0f, 0.0f },
            { position_x + w, position_y,       1.0f, 1.0f },
            { position_x + w, position_y + h,   1.0f, 0.0f }           
        };

        glBindTexture(GL_TEXTURE_2D, ch.texture_id);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof vertices, vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.advance >> 6) * scale_.x;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    shader_->Unbind();
}

void TextRenderer::Load()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        [[unlikely]] throw std::exception("Could not init FreeType Library");

    const auto font_path = std::filesystem::current_path() / "assets/fonts" / Config::font_path;

    FT_Face face;
    if (FT_New_Face(ft, font_path.string().c_str(), 0, &face))
        [[unlikely]] throw std::exception(std::string("Failed to load font " + Config::font_path).c_str());

    FT_Set_Pixel_Sizes(face, 0, Config::width / 40);
    FT_Select_Charmap(face, FT_ENCODING_UNICODE);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    const std::u16string char_set = u" !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ĄąĆćĘęŁłŃńÓóŚśŹźŻż";

    for (const auto& c : char_set)
    {
	    const auto glyph_index = FT_Get_Char_Index(face, c);
        if (FT_Load_Glyph(face, glyph_index, FT_LOAD_RENDER))
			[[unlikely]] throw std::exception(std::string("Failed to load glyph \'" + c + '\'').c_str());

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = 
        {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned>(face->glyph->advance.x)
        };
        characters_.insert(std::pair(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}
