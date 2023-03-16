#include "stdafx.h"
#include "Window.hpp"

Window::Window() : width_(Config::width), height_(Config::height), window_name_(Config::window_name)
{
	Init();
}

Window::~Window()
{
	glfwDestroyWindow(window_);
	glfwTerminate();
}

void Window::FramebufferResizeCallback(GLFWwindow* window, const int width, const int height)
{
	const auto app_window = static_cast<Window*>(glfwGetWindowUserPointer(window));
	app_window->framebuffer_resized_ = true;
	app_window->width_ = width;
	app_window->height_ = height;
}

void Window::KeyPressedCallback(GLFWwindow* window, const int key, int, const int action, int)
{
	if (action == GLFW_PRESS)
	{
		if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED && key == GLFW_KEY_ESCAPE)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL && key == GLFW_KEY_ENTER)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void Window::ErrorCallback(const int error, const char* description)
{
	throw std::exception(description, error);
}

void Window::Init()
{
	if (!glfwInit())
		[[unlikely]] throw std::exception("Failed to init GLFW");

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

	glfwSetErrorCallback(ErrorCallback);

	window_ = glfwCreateWindow(width_, height_, window_name_.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window_);

	if (!window_)
		[[unlikely]] throw std::exception("Failed to create GLFW window");

	if (!gladLoadGL(glfwGetProcAddress)) 
        [[unlikely]] throw std::exception("Failed to load GL");

	glfwSwapInterval(1);

	glfwSetWindowUserPointer(window_, this);
	glfwSetWindowSizeCallback(window_, FramebufferResizeCallback);
	glfwSetKeyCallback(window_, KeyPressedCallback);
}
