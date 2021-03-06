/**
  *************************************************************************************************************************
  * @file    Main_Menu_State.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Main menu state. Implementation of state pattern
  **************************************************************************************************************************
*/
#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H
/*includes*/
#include"Engine_state.h"
#include"Main_Menu.h"
/*Predeclared  classes*/
class Music;

class MainMenuState : public EngineState
{
public:
	/**
	* @brief constructor
	* @param1 actuator control pointer
	* @param2 engine pointer
	* @param3 renderer pointer
	*/
	MainMenuState(std::shared_ptr<Actuator_control> _act_control, Engine* en,
		 std::shared_ptr<SDL_Renderer> renderer);
	/*Destructor*/
	virtual ~MainMenuState();

	/**
	* @brief run state
	* @note
	* @retval
	*/
	void run(Engine*) override;

	/**
	* @brief close state
	* @note
	* @retval
	*/
	void close(Engine*) override;
private:
	const std::unique_ptr<Main_Menu> menu;
};


#endif