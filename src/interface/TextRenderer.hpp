#pragma once
#include "Menu.hpp"
#include "../core/Shader.hpp"
#include "../core/Texture.hpp"

struct Character
{
	std::unique_ptr<Texture> texture = nullptr;
	glm::ivec2 size{};
	glm::ivec2 bearing{};
	unsigned advance{};
};

class TextRenderer
{
public:
	TextRenderer();
	void Init();
	void UpdateProjectionMatrix(int width, int height);
	void Update() const;
	void Render(std::vector<Text>& texts);

private:
	void RenderCharacter(float& x, float& y, char character);
	float CalculateTextWidth(const std::string& text);
	void Load();

	std::unordered_map<int, Character> characters_{};
	std::unique_ptr<Shader> text_shader_ = nullptr;

	unsigned vao_, vbo_;
	glm::vec2 font_scale_{ 1.0f };
	glm::mat4 projection_matrix_{};
};