/**
  *************************************************************************************************************************
  * @file    GlobalKeys.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    15-March-2019
  * @brief   Control keys ESC,backspace and close window event. Observer implemention
  **************************************************************************************************************************
*/
#ifndef GLOABAL_KEYS_H
#define GLOABAL_KEYS_H
/*includes*/
#include<array>
#include<memory>
#include"Observer.h"
#include"Event_listener.h"
#include<SDL.h>
/*Predeclared  classes*/
class Engine;
class Command_Base;

class GlobalKeys:public Observer
{
public:
	/**
	* @brief constructor
	* @param1 event listener pointer
	* @param2 main engine pointer
	*/
	GlobalKeys(std::shared_ptr<Event_listener>,Engine*);
	/*Destructor*/
	virtual ~GlobalKeys();
	/**
	* @brief if event happens this function is called
	* @note
	* @retval 
	*/
	virtual void update();

private:
	std::shared_ptr<Event_listener> ev_listener;
	std::array<std::unique_ptr<Command_Base>,2> commands;//commands for backspace and esc
	Uint32 ev_type;// current event type
};

#endif
