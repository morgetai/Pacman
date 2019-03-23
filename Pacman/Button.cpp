/**
  *************************************************************************************************************************
  * @file    Button.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    13-March-2019
  * @brief   Implementation of the button
  **************************************************************************************************************************
*/

/*includes*/
#include "Button.h"
#include"Primitives.h"


/*setting sprite ptr to null*/
std::unique_ptr<Sprite> Button::button_sprite = nullptr;


/**
* @brief constructor
* @param1,2 width and height
* @param3,4 position x and y
* @param5 path to a font file
* @param6 text
* @param7 renderer
* @param8 command which will be executed at act member function
*/
Button::Button(int w, int h, int x, int y, std::string ttf_path, std::string _text,
	std::shared_ptr<SDL_Renderer> r,std::unique_ptr<Command_Base>&& _command):
	text(std::make_unique<Font>
	(x + w/4, //x of text rect
	y + h/4, //y of text rect
	18, // text height
	r, //renderer
	ttf_path)), // path to a font file
	command(std::move(_command)) //command which is executed when button is pressed
{
	/*setting dest rectangle*/
	dest.w = w; dest.h = h; dest.x = x; dest.y = y;
	/*loading text*/
	text->loadText(_text);

	/*text alignment*/
	int EndOfText = text->get_pos().x + (_text.size() * 18);
	//if text ends beyond destination rectangle
	if (EndOfText > (x+w))
	{
		//getting current text position
		SDL_Point p(text->get_pos()); 
		//moving text to the left side of a button destination rectangle
		p.x = (EndOfText - w + x)/2 + 4;
		//setting new text position
		text->set_pos(p);
	}
}

/*Destructor*/
Button::~Button()
{
	;
}


/**
* @brief executes command
* @note
* @retval none
*/
void Button::act()
{
	/*execute*/
	command->execute();
	/*reset state*/
	state = ACTUATORSTATE::NONACTIVE;
}

/**
* @brief checks to see if cursor is in the Button rectangle
* @note  this function is called when actuator is in ACTING state.
* @param1 x of mause position
* @param2 y of mause position
* @retval true when mouse coursor is in actuator rectangle
*/
bool Button::check_collision(int x, int y)
{
	SDL_Point p; p.x = x; p.y = y;
	if (SDL_PointInRect(&p, &dest))
		return true;
	else return false;
}

/**
* @brief renders the button
* @note
* @retval none
*/
void Button::render()
{
	/*setting button sprite destination rectangle*/
	button_sprite->set_rect(dest);
	/*switching images according to state*/
	switch (state)
	{
	case ACTUATORSTATE::NONACTIVE:
			button_sprite->render(0);
			break;
	case ACTUATORSTATE::ACTIVE:
			button_sprite->render(1);
			break;
	case ACTUATORSTATE::ACTING:
			button_sprite->render(2);
			break;
	}
	/*rendering text*/
	text->render();
}

/**
* @brief sets a button sprite for all buttons
* @param1 number of images
* @param2 renderer
* @param3 path to sprite image file
* @note
* @retval none
*/
void Button::set_button_sprite(std::shared_ptr<SDL_Renderer> r, std::string path)
{
	std::unique_ptr<Sprite> ptr(std::make_unique<Sprite>(3, r, path));
	Button::button_sprite = std::move(ptr);
}