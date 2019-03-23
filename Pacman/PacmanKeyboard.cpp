#include "PacmanKeyboard.h"
#include"Command.h"
#include"Pacman.h"
/**
  *************************************************************************************************************************
  * @file    PacmanKeyboard.cpp
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Pacman keyboard
  **************************************************************************************************************************
*/
/*includes*/
#include"Animation.h"
#include"MoveAlgorithmBase.h"
#include"Game_State.h"
#include"PacmanLife.h"

/**
* @brief constructor
* @param1 event listener pointer
* @param2 pacman pointer
* @param3 game state object pointer
*/
PacmanKeyboard::PacmanKeyboard(std::shared_ptr<Event_listener> ev, Pacman* pacman, GameState* game) :
	ev_listener(ev)
{
	//
	commands[0].reset(new Command<Pacman, Direction>
		(pacman, &Pacman::set_direction, Direction::UP));
	
	commands[1].reset(new Command<Pacman, Direction>
		(pacman, &Pacman::set_direction, Direction::DOWN));
	
	commands[2].reset(new Command<Pacman, Direction>
		(pacman, &Pacman::set_direction, Direction::LEFT));
	
	commands[3].reset(new Command<Pacman, Direction>
		(pacman, &Pacman::set_direction, Direction::RIGHT));
	
	commands[4].reset(new Command<GameState>
		(game, &GameState::GamePause));
}

/*Destructor*/
PacmanKeyboard::~PacmanKeyboard()
{
	;
}

/**
* @brief update pacman direction
* @note updates direction according to pressed key
* @retval
*/
void PacmanKeyboard::update()
{
	ev_type = ev_listener->get_event_type();
	switch (ev_type)
	{
	case SDL_KEYUP:
	{
		SDL_KeyboardEvent key_ev = std::move(ev_listener->get_key_event());
		switch (key_ev.keysym.sym)
		{
		case SDLK_UP:
			commands[0]->execute();
			break;
		case SDLK_w:
			commands[0]->execute();
			break;
		case SDLK_DOWN:
			commands[1]->execute();
			break;
		case SDLK_s:
			commands[1]->execute();
			break;
		case SDLK_LEFT:
			commands[2]->execute();
			break;
		case SDLK_a:
			commands[2]->execute();
			break;
		case SDLK_RIGHT:
			commands[3]->execute();
			break;
		case SDLK_d:
			commands[3]->execute();
			break;
		case SDLK_SPACE:
			commands[4]->execute();
			break;
		}
	}
	default:
		;
	}
}

