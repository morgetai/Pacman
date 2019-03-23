/**
  *************************************************************************************************************************
  * @file    Event_listener.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    14-March-2019
  * @brief   Class for events listening. Implementetion of observer pattern
  **************************************************************************************************************************
*/

#ifndef EVENT_LISTERNER_H
#define EVENT_LISTERNER_H
/*includes*/
#include <SDL.h>
#include "Subject.h"

class Event_listener:public Subject
{
public:
	/*Constructor*/
	Event_listener();
	/*Destructor*/
	virtual ~Event_listener(void);
	
	/*attach objects*/
	using Subject::attach;
	/*detach objects*/
	using Subject::detach;

	/**
	* @brief listens the events
	* @note notifies all attached objects
	* @retval
	*/
	void listen_events();

	/**
	* @brief get keyboard event
	* @note
	* @retval keyboard event
	*/
	SDL_KeyboardEvent get_key_event(void);

	/**
	* @brief get mouse event
	* @note
	* @retval mouse event
	*/
	SDL_MouseMotionEvent get_mousem_event();

	/**
	* @brief get mouse button event
	* @note
	* @retval mouse button event
	*/
	SDL_MouseButtonEvent get_mouseb_event();

	/**
	* @brief get current event type
	* @note 
	* @retval returns event type. See typedef union SDL_Event
	*/
	Uint32 get_event_type();
private:
	std::unique_ptr<SDL_Event> sdlEvent;//pointer to the SDL structure
};


#endif
