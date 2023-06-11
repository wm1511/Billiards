#include "stdafx.h"
#include "Menu.hpp"

Menu::Menu(const int width, const int height) :
	width_(width), height_(height)
{
}

void Menu::Draw()
{
	ControlState();

	AddText(0.5f, 0.9f, "BILLIARDS", 2.0f, Alignment::CENTER);
	AddText(0.5f, 0.7f, "Play game", 0.75f, Alignment::CENTER, selected_ == 0);
	AddText(0.5f, 0.6f, "Show help", 0.75f, Alignment::CENTER, selected_ == 1);
	AddText(0.5f, 0.5f, "Reset balls", 0.75f, Alignment::CENTER, selected_ == 2);
	AddText(0.5f, 0.4f, "Strike force", 0.75f, Alignment::CENTER, selected_ == 3);
	AddText(0.5f, 0.3f, "Ball friction", 0.75f, Alignment::CENTER, selected_ == 4);
	AddText(0.5f, 0.2f, "Exit game", 0.75f, Alignment::CENTER, selected_ == 6);
}

void Menu::ControlState()
{
	GLFWwindow* window = glfwGetCurrentContext();

	const int down_state = glfwGetKey(window, GLFW_KEY_DOWN);
	if (down_state == GLFW_PRESS && last_down_state_ != GLFW_PRESS)
		selected_++;

	last_down_state_ = down_state;

	const int up_state = glfwGetKey(window, GLFW_KEY_UP);
	if (up_state == GLFW_PRESS && last_up_state_ != GLFW_PRESS)
		selected_--;

	last_up_state_ = up_state;

	if (selected_ < 0)
		selected_ = 6;
	else if (selected_ > 6)
		selected_ = 0;
}

void Menu::AddText(const float u, const float v, const std::string& text, const float scale, Alignment alignment, bool selected)
{
	texts_.emplace_back(u * width_, v * height_, text, scale, alignment, selected);
}

void Menu::DrawHelp()
{
	AddText(0.99f, 0.7f, R"(Edit options using 'RIGHT" and 'LEFT' arrows)", 0.4f, Alignment::RIGHT);
	AddText(0.99f, 0.65f, R"(Move camera using 'W', 'S', 'A', 'D', 'E', 'Q')", 0.4f, Alignment::RIGHT);
	AddText(0.99f, 0.6f, R"(Rotate camera using mouse)", 0.4f, Alignment::RIGHT);
	AddText(0.99f, 0.55f, R"(Adjust strike force using 'UP' and 'DOWN' arrows)", 0.4f, Alignment::RIGHT);
	AddText(0.99f, 0.5f, R"(Rotate cue using 'RIGHT' and 'LEFT' arrows)", 0.4f, Alignment::RIGHT);
	AddText(0.99f, 0.45f, R"(Cue cannot be rotated after changing strike force)", 0.4f, Alignment::RIGHT);
	AddText(0.99f, 0.4f, R"(Strike a white ball using 'SPACE')", 0.4f, Alignment::RIGHT);
	AddText(0.99f, 0.35f, R"(Turn on additional light using 'LSHIFT')", 0.4f, Alignment::RIGHT);
}

void Menu::Update(const int width, const int height)
{
	width_ = width;
	height_ = height;
}
