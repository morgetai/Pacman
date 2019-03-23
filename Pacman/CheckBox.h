/**
  *************************************************************************************************************************
  * @file    Checkbox.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    13-March-2019
  * @brief   Implementation of the checkbox
  **************************************************************************************************************************
*/
#ifndef CHECKBOX_H
#define CHECKBOX_H

/*includes*/
#include"Actuator.h"
#include<SDL.h>
#include<memory>
#include<string>

/*Predeclared  classes*/
class Font;
class Sprite;
class Command_Base;


class CheckBox : public Actuator
{
public:
	/**
	* @brief constructor
	* @param1 rectangle
	* @param2 command object
	*/
	CheckBox(SDL_Rect, std::unique_ptr<Command_Base>&&);
	/*Destructor*/
	virtual ~CheckBox();

	/**
	* @brief rendring the actuator
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
	* @brief checks to see if cursor is in the checkbox rectangle
	* @note  this function is called when actuator is in ACTING state.
	* @param1 x of mause position
	* @param2 y of mause position
	* @retval true when mouse coursor is in actuator rectangle
	*/
	virtual bool check_collision(int x, int y);

	/**
	* @brief sets a checkbox sprite
	* @param1 number of images
	* @param2 renderer
	* @param3 path to sprite image file
	* @note
	* @retval none
	*/
	static void set_checkbox_sprite(std::shared_ptr<SDL_Renderer>,
		std::string);
private:
	SDL_Rect dest;//destination recrangle
	std::unique_ptr<Command_Base> command;//command which is executed when button is pressed
	bool acted;//true if checkbox is set
	static std::unique_ptr<Sprite> checkbox_sprite;//pointer to a sprite object
};

#endif
