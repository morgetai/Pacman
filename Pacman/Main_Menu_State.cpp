/**
  *************************************************************************************************************************
  * @file    Main_Menu_State.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Main menu state. Implementation of state pattern
  **************************************************************************************************************************
*/
/*includes*/
#include "Main_Menu_State.h"
#include"DefaultValues.h"
/**
* @brief constructor
* @param1 actuator control pointer
* @param2 engine pointer
* @param3 renderer pointer
*/
MainMenuState::MainMenuState(std::shared_ptr<Actuator_control> _act_control, Engine* en,
	 std::shared_ptr<SDL_Renderer> renderer):
	menu(std::make_unique<Main_Menu>(DefaultValues::MainMenuImg, _act_control,
		en, renderer))
{
	active = false;
}

MainMenuState::~MainMenuState()
{
	;
}


/**
* @brief run state
* @note
* @retval
*/
void MainMenuState::run(Engine*)
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
* @retval
*/
void MainMenuState::close(Engine*)
{
	menu->detach_actuators();
	active = false;
}