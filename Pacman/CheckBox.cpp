/**
  *************************************************************************************************************************
  * @file    Checkbox.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    13-March-2019
  * @brief   Implementation of the checkbox
  **************************************************************************************************************************
*/

/*includes*/
#include "CheckBox.h"
#include"Command_base.h"
#include"Primitives.h"

/*setting sprite ptr to null*/
std::unique_ptr<Sprite> CheckBox::checkbox_sprite = nullptr;

/**
* @brief constructor
* @param1 rectangle
* @param3 command object
*/
CheckBox::CheckBox(SDL_Rect r, 
	std::unique_ptr<Command_Base>&& _command):
	dest(r),
	command(std::move(_command))
{
	acted = true;
}

/*Destructor*/
CheckBox::~CheckBox()
{
}

/**
* @brief executes command
* @note
* @retval none
*/
void CheckBox::act()
{
	command->execute();
	/*if checkbox was set before*/
	if (!acted)
	{
		state = ACTUATORSTATE::ACTING;
		acted = true;
	}
	else
		acted = false;
}

/**
* @brief checks to see if cursor is in the checkbox rectangle
* @note  this function is called when actuator is in ACTING state.
* @param1 x of mause position
* @param2 y of mause position
* @retval true when mouse coursor is in actuator rectangle
*/
bool CheckBox::check_collision(int x, int y)
{
	SDL_Point p;
	p.x = x; p.y = y;
	return SDL_PointInRect(&p, &dest);
}

/**
* @brief rendring the actuator
* @retval none
*/
void CheckBox::render()
{
	checkbox_sprite->set_rect(dest);
	switch (state)
	{
	case ACTUATORSTATE::NONACTIVE:
		if (acted)
			checkbox_sprite->render(2);
		else
			checkbox_sprite->render(0);
		break;
	case ACTUATORSTATE::ACTIVE:
		if (acted)
		{
			checkbox_sprite->render(2);
		}
		else
		{
			checkbox_sprite->render(1);
		}
		break;
	case ACTUATORSTATE::ACTING:
		if (acted)
		{
			checkbox_sprite->render(2);
		}
		else
		{
			checkbox_sprite->render(1);
		}
		break;
	}
}

/**
* @brief sets a checkbox sprite
* @param1 number of images
* @param2 renderer
* @param3 path to sprite image file
* @note
* @retval none
*/
void CheckBox::set_checkbox_sprite(std::shared_ptr<SDL_Renderer> r, std::string path)
{
	std::unique_ptr<Sprite> ptr(std::make_unique<Sprite>(3, r, path, SpriteOrientation::HORIZONTAL));
	CheckBox::checkbox_sprite = std::move(ptr);
}