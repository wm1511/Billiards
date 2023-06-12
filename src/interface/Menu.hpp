#pragma once

template <typename... Args>
std::string BuildString(const std::string& format_string, Args&&... format_args)
{
	return std::vformat(format_string, std::make_format_args(std::forward<Args>(format_args)...));
}

enum class Alignment
{
	LEFT,
	CENTER,
	RIGHT
};

struct Text
{
	float u{};
	float v{};
	std::string text{};
	float scale{ 1.0f };
	Alignment alignment{};
	bool selected{ false };
};

class Menu
{
public:
	Menu(int width, int height);

	[[nodiscard]] std::vector<Text>& GetTexts() { return texts_; }
	[[nodiscard]] int GetSelected() const { return selected_; }

	void Draw(bool not_loaded);
	void DrawHelp();
	void Update(int width, int height);
	void AddText(float u, float v, const std::string& text, float scale = 1.0f, Alignment alignment = Alignment::LEFT, bool selected = false);

private:
	void ControlState();

	int width_{};
	int height_{};
	int selected_{};
	int last_left_state_{}, last_up_state_{}, last_right_state_{}, last_down_state_{};
	std::vector<Text> texts_{};
};