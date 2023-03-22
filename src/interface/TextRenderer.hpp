#pragma once
#include "../core/Shader.hpp"

struct Character
{
	unsigned texture_id{};
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

	template <typename... Args> void Render(float x, float y, const std::string& format_string, Args&&... args)
	{
		shader_->Bind();

		shader_->SetVec3(glm::vec3(1.0f), "textColor");

		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(vao_);

		const std::string text = std::vformat(format_string, std::make_format_args(std::forward<Args>(args)...));

		for (const auto& c : text)
			RenderCharacter(x, y, c);

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		shader_->Unbind();
	}

private:
	void RenderCharacter(float& x, float& y, char character);
	void Load();

	std::map<int, Character> characters_{};
	std::unique_ptr<Shader> shader_ = nullptr;

	unsigned vao_, vbo_;
	glm::vec2 scale_{ 1.0f };
	glm::mat4 projection_matrix_{};
};