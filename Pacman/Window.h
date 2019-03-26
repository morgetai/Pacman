/**
  *************************************************************************************************************************
  * @file    Window.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    17-March-2019
  * @brief   Window class
  **************************************************************************************************************************
*/
#ifndef WINDOW_H
#define WINDOW_H
/*includes*/
#include<string>
#include<iostream>
#include<SDL.h>
#include"DefaultValues.h"


class Window
{
public:
	/**
	* @brief constructor
	* @param1 Window name
	*/
	Window(std::string );
	/*destructor*/
	~Window();

	/**
	* @brief clears the window screen
	* @note
	* @retval
	*/
	void clear_window();

	/**
	* @brief clears the window screen
	* @note
	* @retval
	*/
	void update_window();

	/**
	* @brief get renderer
	* @note
	* @retval renderer pointer
	*/
	std::shared_ptr<SDL_Renderer> get_renderer() { return renderer; }

private:
	SDL_Window* _window;
	std::shared_ptr<SDL_Renderer> renderer;
};



#endif
