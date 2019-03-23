/**
  *************************************************************************************************************************
  * @file    Main_Menu.cpp
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Main menu
  **************************************************************************************************************************
*/
/*includes*/
#include "Main_Menu.h"
#include "Engine.h"
#include "Command.h"
#include "Command.h"
#include "Button.h"
#include "Primitives.h"
#include"DefaultValues.h"
#include <algorithm>

/**
* @brief constructor
* @param1 image path
* @param2 actuator control pointer
* @param3 engine pointer
* @param4 renderer pointer
*/
Main_Menu::Main_Menu(std::string img_path, std::shared_ptr<Actuator_control> _act_control,Engine* en ,
	std::shared_ptr<SDL_Renderer> renderer):
	img(std::make_unique<Image>	(
		300, //w
		200, //h
		250, //x
		10,  //y
		renderer, img_path)),
	Menu_Base(_act_control)
{
	/*load game state*/
	actuators.emplace_back(new Button(
		150, //w
		50, //h
		320, //x
		320, //y
		DefaultValues::Font, "PLAY", renderer,
		std::move(std::unique_ptr<Command_Base>
		(new Command<Engine,EngineStateType>(en, &Engine::change_state, EngineStateType::STATE_GAME)))));

	/*load options menu*/
	actuators.emplace_back(new Button(
		150, //w
		50, //h
		320, //x
		400, //y
		DefaultValues::Font, "OPTIONS", renderer,
		std::move(std::unique_ptr<Command_Base>
		(new Command<Engine, EngineStateType>(en, &Engine::change_state, EngineStateType::STATE_OPTIONS)))));



	texts.emplace_back
	(
		30,//x
		500,//y
		16,//text height
		renderer,
		DefaultValues::Font
	);
	texts.emplace_back
	(
		30,//x
		520,//y
		16,//text height
		renderer,
		DefaultValues::Font
	);
	texts.emplace_back
	(
		46,//x
		540,//y
		16,//text height
		renderer,
		DefaultValues::Font
	);
	texts.emplace_back
	(
		46,//x
		560,//y
		16,//text height
		renderer,
		DefaultValues::Font
	);

	std::for_each(texts.begin(), texts.end(), [](Font& f) 
	{
		f.setColor(255, 215, 0);
	});

	/*set texts*/
	texts[0].loadText("Start: Enter");
	texts[1].loadText("Pause: Space");
	texts[2].loadText("Move: \"up\" \"down\" \"left\" \"right\" or \"wasd\"");
	texts[3].loadText("back: backspace or esc");
}

/*Destructor*/
Main_Menu::~Main_Menu()
{
	;
}

/**
* @brief render all interactive objects
* @note
* @retval
*/
void Main_Menu::render()
{
	img->render();
	/*render buttons*/
	std::for_each(actuators.begin(), actuators.end(), [](std::shared_ptr<Actuator>& act) {act->render(); });
	/*render texts*/
	std::for_each(texts.begin(), texts.end(), [](Font& f) {f.render(); });
}