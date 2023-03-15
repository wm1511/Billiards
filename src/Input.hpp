#pragma once

class Input
{
public:
	static void SetPressedKey(const int key_code)
	{
		pressed_key_code_ = key_code;
	}

	static void SetCursorPosition(const double cursor_x, const double cursor_y)
	{
		cursor_delta_ = glm::vec2(static_cast<float>(cursor_x_ - cursor_x), static_cast<float>(cursor_y_ - cursor_y));
		cursor_x_ = cursor_x;
		cursor_y_ = cursor_y;
	}

	static glm::vec2 GetCursorDelta()
	{
		const glm::vec2 temp = cursor_delta_;
		cursor_delta_ = {0.0f, 0.0f};
		return temp;
	}

	static int GetPressedKey()
	{
		GLFWwindow* window = glfwGetCurrentContext();
		return pressed_key_code_;
	}

private:
	inline static glm::vec2 cursor_delta_{};
	inline static double cursor_x_{}, cursor_y_{};
	inline static int pressed_key_code_{};
};
