/**
  *************************************************************************************************************************
  * @file    Button.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    13-March-2019
  * @brief   Implementation of the button
  **************************************************************************************************************************
*/


#ifndef BUTTON_H
#define BUTTON_H

/*includes*/
#include<memory>
#include<string>
#include<SDL.h>
#include"Actuator.h"
#include"Command_base.h"

/*Predeclared  classes*/
class Font;
class Sprite;


class Button:public Actuator
{
public:
	/**
	* @brief constructor
	* @param1,2 width and height
	* @param3,4 position x and y
	* @param5 path to a font file
	* @param6 text
	* @param7 renderer
	* @param8 command which will be executed at act member function
	*/
	Button(int, int, int, int, std::string , std::string , 
		std::shared_ptr<SDL_Renderer> ,std::unique_ptr<Command_Base>&& );
	/*Destructor*/
	virtual ~Button();

	/**
	* @brief sets a button sprite for all buttons
	* @param1 number of images
	* @param2 renderer
	* @param3 path to sprite image file
	* @note
	* @retval none
	*/
	static void set_button_sprite(std::shared_ptr<SDL_Renderer> r, std::string path);

	/**
	* @brief renders the button
	* @note
	* @retval none
	*/
	virtual void render();

	/**
	* @brief executes command
	* @note
	* @retval none
	*/
	virtual void act();

	/**
	* @brief checks to see if cursor is in the Button rectangle
	* @note  this function is called when actuator is in ACTING state.
	* @param1 x of mause position
	* @param2 y of mause position
	* @retval true when mouse coursor is in actuator rectangle
	*/
	virtual bool check_collision(int x, int y);
private:
	SDL_Rect dest;//destination rectangle
	std::unique_ptr<Font> text;//button text
	std::unique_ptr<Command_Base> command;//command which is executed when button is pressed
	static std::unique_ptr<Sprite> button_sprite;//pointer to a sprite object
};



#endif
