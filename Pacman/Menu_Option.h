/**
  *************************************************************************************************************************
  * @file    Menu_Option.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Option menu class
  **************************************************************************************************************************
*/
#ifndef MENU_OPTION_H
#define MENU_OPTION_H
/*includes*/
#include"Menu_Base.h"
#include<SDL.h>
#include<string>
#include<memory>
/*Predeclared  classes*/
class Actuator_control;
class Engine;
class Image;
class Font;
class MixEngine;

class Menu_Option:public Menu_Base
{
public:
	/**
	* @brief constructor
	* @param1 path to image file
	* @param2 actuator control pointer
	* @param3 engine pointer
	* @param3 MixEngine pointer
	* @param4 Renderer pointer
	*/
	Menu_Option(std::string, std::shared_ptr<Actuator_control>,Engine*, MixEngine*,
		std::shared_ptr<SDL_Renderer>);
	/*Destructor*/
	virtual ~Menu_Option();

	/**
	* @brief render a menu
	* @note
	* @retval
	*/
	void render() override;
private:
	const std::unique_ptr<Image> img;
	const std::unique_ptr<Font> SoundText;
	const std::unique_ptr<Font> MusicText;
};

#endif