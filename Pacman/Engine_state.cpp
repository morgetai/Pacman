/**
  *************************************************************************************************************************
  * @file    Engine_state.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    14-March-2019
  * @brief   EngineState class. Part of state pattern
  **************************************************************************************************************************
*/
/*includes*/
#include"Engine_state.h"
#include "Engine.h"

/**
* @brief changes the engine state
* @note
* @param1 pointer to the engine
* @param1 new state
* @retval
*/
void EngineState::chagestate(Engine* engine, EngineStateType state)
{ 
	engine->change_state(state); 
}