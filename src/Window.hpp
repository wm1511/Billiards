#pragma once

class Window
{
public:
	Window(int width, int height, std::string name);
	~Window();

	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator= (const Window&) = delete;
	Window& operator= (Window&&) = delete;

	[[nodiscard]] bool ShouldClose() const
	{
		return glfwWindowShouldClose(window_);
	}
	[[nodiscard]] GLFWwindow* GetGLFWWindow() const
	{
		return window_;
	}
	[[nodiscard]] bool Resized() const
	{
		return framebuffer_resized_;
	}
	[[nodiscard]] int GetWidth() const
	{
		return width_;
	}
	[[nodiscard]] int GetHeight() const
	{
		return height_;
	}
	void ResetResizedFlag()
	{
		framebuffer_resized_ = false;
	}

private:
	static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);
	static void KeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	[[noreturn]] static void ErrorCallback(int error, const char* description);

	void Init();

	int width_{};
	int height_{};
	bool framebuffer_resized_ = false;

	std::string window_name_;
	GLFWwindow* window_ = nullptr;
};
