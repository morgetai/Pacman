/**
  *************************************************************************************************************************
  * @file    Main_Menu.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Main menu 
  **************************************************************************************************************************
*/
#ifndef MAIN_MENU_H
#define MAIN_MENU_H
/*includes*/
#include<memory>
#include <vector>
#include<string>
#include "Menu_Base.h"
/*Predeclared  classes*/
class Image;
class Engine;
class Font;

class Main_Menu:public Menu_Base
{
public:
	/**
	* @brief constructor
	* @param1 image path
	* @param2 actuator control pointer
	* @param3 engine pointer
	* @param4 renderer pointer
	*/
	Main_Menu(std::string , std::shared_ptr<Actuator_control> , Engine* ,
		 std::shared_ptr<SDL_Renderer> );
	/*Destructor*/
	virtual ~Main_Menu();

	/**
	* @brief render all interactive objects
	* @note
	* @retval
	*/
	void render() override;
private:
	const std::unique_ptr<Image> img;
	std::vector<Font> texts;
};



#endif
