/**
  *************************************************************************************************************************
  * @file    Engine.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    14-March-2019
  * @brief   Main program engine
  **************************************************************************************************************************
*/

#ifndef ENGINE_H
#define ENGINE_H
/*includes*/
#include "Window.h"
#include<memory>
#include<vector>
#include<array>
/*Predeclared  classes*/
class EngineState;
class Event_listener;
class GlobalKeys;
class Actuator_control;
class EngineState;
class Main_Menu;
class GameState;
class MixEngine;
class Music;
class Menu_Option;

/*Engine states*/
enum class EngineStateType {
	STATE_MAIN = 0,
	STATE_OPTIONS = 1,
	STATE_GAME = 2,
	STATE_CLOSE = 3,
	STATE_NOT_INITIALIZED = 4,
	STATE_INITIALIZED = 5
};



class Engine
{
	friend class EngineState;
	friend class GlobalKeys;
	friend class Main_Menu;
	friend class GameState;
	friend class Menu_Option;
public:
	/*Constructor*/
	Engine();
	/*Destructor*/
	~Engine();
	/**
	* @brief runs the program
	* @note run in main()
	* @retval
	*/
	void run();
private: 
	/**
	* @brief setting state
	* @param1 new state
	* @note
	* @retval
	*/
	void change_state(EngineStateType);
private:
	const std::unique_ptr<Window> window;//pointer to the window
	const std::shared_ptr<Event_listener> EventListener;//
	const std::shared_ptr<Actuator_control> ActuatorControl;//pointer 
	const std::shared_ptr<GlobalKeys> globalkeys;
	const std::unique_ptr<MixEngine> mixengine;//pointer to music control object
	const std::shared_ptr<Music> menumusic;
	const std::shared_ptr<Music> gamemusic;

	std::array<std::unique_ptr<EngineState>,3> states;//Pointers to a states objects
	EngineStateType current_state;
	EngineStateType prev_state;
	bool Close;//true some state was closed
};


#endif
