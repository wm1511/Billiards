#include "stdafx.h"
#include "core/App.hpp"

int main()
{
	try
	{
		App app;
		app.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}