/**
  *************************************************************************************************************************
  * @file    PacmanKeyboard.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Pacman keyboard
  **************************************************************************************************************************
*/
#ifndef  PACMAN_KEYBOARD_H
#define PACMAN_KEYBOARD_H
/*includes*/
#include<memory>
#include<array>
#include"Event_listener.h"
#include"Observer.h"

/*Predeclared  classes*/
class Command_Base;
class Pacman;
class PacmanMoveAlgorithm;
class GameState;
class PacmanKeyboard:public Observer
{
public:
	/**
	* @brief constructor
	* @param1 event listener pointer
	* @param2 pacman pointer
	* @param3 game state object pointer
	*/
	PacmanKeyboard(std::shared_ptr<Event_listener>,Pacman*, GameState*);
	/*Destructor*/
	virtual ~PacmanKeyboard();

	/**
	* @brief update pacman direction
	* @note updates direction according to pressed key
	* @retval
	*/
	virtual void update();

private:
	std::shared_ptr<Event_listener> ev_listener;
	std::array<std::unique_ptr<Command_Base>, 5> commands;
	Uint32 ev_type;//keyboard eve type
};

#endif // ! PACMAN_KEYBOARD_H

