/**
  *************************************************************************************************************************
  * @file    GlobalKeys.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    15-March-2019
  * @brief   Control keys ESC,backspace and close window event. Observer implemention
  **************************************************************************************************************************
*/
/*includes*/
#include"GlobalKeys.h"
#include"Command.h"
#include"Engine.h"
#include"Event_listener.h"

/**
* @brief constructor
* @param1 event listener pointer
* @param2 main engine pointer
*/
GlobalKeys::GlobalKeys(std::shared_ptr<Event_listener> ev, Engine* engine) :
	ev_listener(ev)
{
	/*close program*/
	commands[0] = std::make_unique<Command<Engine, EngineStateType>>
		(engine, &Engine::change_state, EngineStateType::STATE_CLOSE);
	/*return to main menu*/
	commands[1] = std::make_unique<Command<Engine, EngineStateType>>
		(engine,&Engine::change_state, EngineStateType::STATE_MAIN);
}

/*Destructor*/
GlobalKeys::~GlobalKeys()
{
}

/**
* @brief if event happens this function is called
* @note
* @retval
*/
void GlobalKeys::update()
{
	ev_type = ev_listener->get_event_type();
	switch (ev_type)
	{
	case SDL_QUIT:
		commands[0]->execute();
		break;
	case SDL_KEYUP:
	{
		SDL_KeyboardEvent key_ev = std::move(ev_listener->get_key_event());
		switch (key_ev.keysym.sym)
		{
		case SDLK_BACKSPACE:
			commands[1]->execute();
			break;
		case SDLK_ESCAPE:
			commands[1]->execute();
			break;
		}
	}
	break;
	}
}