#pragma once
#include "../core/Shader.hpp"
#include "../core/Texture.hpp"

struct Character
{
	std::unique_ptr<Texture> texture = nullptr;
	glm::ivec2 size{};
	glm::ivec2 bearing{};
	unsigned advance{};
};

struct Text
{
	float position_x{};
	float position_y{};
	std::string text{};
};

class TextRenderer
{
public:
	TextRenderer();
	void Init();
	void UpdateProjectionMatrix(int width, int height);
	void Update() const;
	void Render();

	template <typename... Args> void AddText(float x, float y, const std::string& format_string, Args&&... format_args)
	{
		const std::string text = std::vformat(format_string, std::make_format_args(std::forward<Args>(format_args)...));
		texts_.emplace_back(x, y, text);
	}

private:
	void RenderCharacter(float& x, float& y, char character);
	void Load();

	std::unordered_map<int, Character> characters_{};
	std::vector<Text> texts_{};
	std::unique_ptr<Shader> text_shader_ = nullptr;

	unsigned vao_, vbo_;
	glm::vec2 scale_{ 1.0f };
	glm::mat4 projection_matrix_{};
};