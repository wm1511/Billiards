#include "stdafx.h"
#include "TextRenderer.hpp"

TextRenderer::TextRenderer() : text_shader_(std::make_unique<Shader>(Config::text_vertex_path, Config::text_fragment_path)), vao_{}, vbo_{}
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
	text_shader_->Bind();
	text_shader_->SetMat4(projection_matrix_, "projectionMatrix");
}

void TextRenderer::Render()
{
	text_shader_->Bind();

	text_shader_->SetVec3(glm::vec3(1.0f), "textColor");

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao_);

	for (auto& [position_x, position_y, text] : texts_)
		for (const auto c : text)
			RenderCharacter(position_x, position_y, c);

	texts_.clear();

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextRenderer::RenderCharacter(float& x, float& y, const char character)
{
	const Character& ch = characters_[character];

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

	if (ch.texture)
		ch.texture->Bind();

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof vertices, vertices);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	x += (ch.advance >> 6) * scale_.x;
}

void TextRenderer::Load()
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		[[unlikely]] throw std::exception("Could not init FreeType Library");

	const auto font_path = std::filesystem::current_path() / "assets/fonts" / Config::font_path;

	FT_Face face;
	if (FT_New_Face(ft, font_path.string().c_str(), 0, &face))
		[[unlikely]] throw std::exception("Failed to load font");

	FT_Set_Pixel_Sizes(face, 0, Config::default_font_size);
	FT_Select_Charmap(face, FT_ENCODING_UNICODE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (int i = 32; i < 128; i++)
	{
		if (FT_Load_Char(face, i, FT_LOAD_RENDER))
			[[unlikely]] throw std::exception(std::string("Failed to load glyph \'" + i + '\'').c_str());

		auto character = Character(
			std::make_unique<Texture>(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows, 1),
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			static_cast<unsigned>(face->glyph->advance.x));

		characters_.insert(std::pair(i, std::move(character)));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}
