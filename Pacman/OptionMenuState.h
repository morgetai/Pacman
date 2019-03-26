/**
  *************************************************************************************************************************
  * @file    OptionMenuState.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Option state
  **************************************************************************************************************************
*/
#ifndef IPTIONSTATE_H
#define IPTIONSTATE_H
/*includes*/
#include<memory>
#include<SDL.h>
#include"Engine_state.h"
/*Predeclared  classes*/
class Actuator_control;
class MixEngine;
class Engine;
class Menu_Base;

class OptionMenuState : public EngineState
{
public:
	/**
	* @brief constructor
	* @param1 actuator control pointer
	* @param2 engine pointer
	* @param3 mixengine pointer
	* @param4 renderer pointer
	*/
	OptionMenuState(std::shared_ptr<Actuator_control>, Engine*,MixEngine*,
		std::shared_ptr<SDL_Renderer>);
	/*Destructor*/
	virtual ~OptionMenuState();

	/**
	* @brief run state
	* @note
	* @param1 engine pointer
	* @retval
	*/
	virtual void run(Engine*);

	/**
	* @brief close state
	* @note
	* @param1 engine pointer
	* @retval
	*/
	virtual void close(Engine*);
private:
	std::unique_ptr<Menu_Base> menu;//option menu pointer 
};

#endif