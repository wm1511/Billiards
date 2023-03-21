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
	void Render(const std::u16string& text, float x = 0.0f, float = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
	void Load();

	std::map<char16_t, Character> characters_{};
	glm::mat4 projection_matrix_{};
	std::unique_ptr<Shader> shader_ = nullptr;

	unsigned vao_, vbo_;
	glm::vec2 scale_{1.0f};
};