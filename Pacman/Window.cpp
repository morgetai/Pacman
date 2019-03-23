/**
  *************************************************************************************************************************
  * @file    Window.cpp
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    17-March-2019
  * @brief   Window class
  **************************************************************************************************************************
*/
/*includes*/
#include "Window.h"

/**
* @brief constructor
* @param1 Window name
*/
Window::Window(std::string name)
{
	_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		DefaultValues::WindowWidth, DefaultValues::WindowHeight, SDL_WINDOW_SHOWN);
	if (_window == NULL) std::cerr << "Window could not be created! SDL Error" << name << "\n" << SDL_GetError();
	else
	{
		std::shared_ptr<SDL_Renderer> ptr(SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
			, [](SDL_Renderer* r) {SDL_DestroyRenderer(r); });
		if (!ptr)
		{
			std::cerr << "Renderer could not be created! SDL Error" << SDL_GetError();
			std::terminate();
		}
		else
		{
			renderer = std::move(ptr);
			SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 0);
		}
	}
}

/*destructor*/
Window::~Window()
{
	SDL_DestroyWindow(_window);
}

/**
* @brief clears the window screen
* @note
* @retval
*/
void Window::clear_window()
{
	SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 0);
	SDL_RenderClear(renderer.get());
}

/**
* @brief clears the window screen
* @note
* @retval
*/
void Window::update_window()
{
	SDL_RenderPresent(renderer.get());
}