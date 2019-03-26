/**
  *************************************************************************************************************************
  * @file    Event_listener.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    14-March-2019
  * @brief   Class for events listening. Implementetion of observer pattern
  **************************************************************************************************************************
*/
/*includes*/
#include"Event_listener.h"

/*Constructor*/
Event_listener::Event_listener() :
	sdlEvent(std::make_unique<SDL_Event>())
{
}
/*Destructor*/
Event_listener::~Event_listener()
{
}

/**
* @brief listens the events
* @note notifies all attached objects
* @retval
*/
void Event_listener::listen_events()
{
	if (SDL_PollEvent(sdlEvent.get()))
		notify();
}

/**
* @brief get keyboard event
* @note
* @retval keyboard event
*/
SDL_KeyboardEvent Event_listener::get_key_event(void)
{
	return sdlEvent->key;
}

/**
* @brief get mouse event
* @note
* @retval mouse event
*/
SDL_MouseMotionEvent Event_listener::get_mousem_event()
{
	return sdlEvent->motion;
}

/**
* @brief get mouse button event
* @note
* @retval mouse button event
*/
SDL_MouseButtonEvent Event_listener::get_mouseb_event()
{
	return sdlEvent->button;
}

/**
* @brief get current event type
* @note
* @retval returns event type. See typedef union SDL_Event
*/
Uint32 Event_listener::get_event_type()
{
	return sdlEvent->type;
}