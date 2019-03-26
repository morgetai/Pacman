/**
  *************************************************************************************************************************
  * @file    OptionMenuState.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Option state
  **************************************************************************************************************************
*/
/*includes*/
#include "OptionMenuState.h"
#include"Actuator_constrol.h"
#include"MixEngine.h"
#include"Menu_Option.h"
#include"Engine.h"
#include"Menu_Base.h"
#include"DefaultValues.h"

/**
* @brief constructor
* @param1 actuator control pointer
* @param2 engine pointer
* @param3 mixengine pointer
* @param4 renderer pointer
*/
OptionMenuState::OptionMenuState(std::shared_ptr<Actuator_control> _act_control,Engine* eng, MixEngine* mixengine,
	std::shared_ptr<SDL_Renderer> renderer):
	menu(std::make_unique<Menu_Option>(DefaultValues::MainMenuImg, _act_control,
		eng,mixengine, renderer))
{
}

/*Destructor*/
OptionMenuState::~OptionMenuState()
{
}

/**
* @brief run state
* @note
* @param1 engine pointer
* @retval
*/
void OptionMenuState::run(Engine*)
{
	if (false == active)
	{
		menu->attach_actuators();
		menu->render();
		active = true;
	}
	else
	{
		menu->render();
	}
}

/**
* @brief close state
* @note
* @param1 engine pointer
* @retval
*/
void OptionMenuState::close(Engine*)
{
	menu->detach_actuators();
	active = false;
}