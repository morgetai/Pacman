/**
  *************************************************************************************************************************
  * @file    Actuator_conrol.cpp
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    13-March-2019
  * @brief   Class for controlling buttons, checkboxes. When menu is being active actuators are attached to this
  * @brief		constrol object via "add_actuators" function. Uses pointer to a Event_listener object to listen for events.
  **************************************************************************************************************************
*/


/*Includes*/
#include "Actuator_constrol.h"


/*Constructor*/
Actuator_control::Actuator_control(std::shared_ptr<Event_listener> ev) :

	ev_listener(ev),
	current_actuator (0)
{
	actuators.reserve(5);
}


/**
* @brief updates actuators state
* @note  called when keyboard or mouse event occurred
* @retval none
*/
void Actuator_control::update()
{
	/*run if only some actuators are attached*/
	if (!actuators.empty())
	{
		ev_type = ev_listener->get_event_type();

		/*type event processing*/
		switch (ev_type)
		{
		/*Keyboard key up*/
		case SDL_KEYUP:
		{
			/*Keyboard button event*/
			SDL_KeyboardEvent key_ev = ev_listener->get_key_event();
			/*current key*/
			switch (key_ev.keysym.sym) 
			{
			/*Key up*/
			case SDLK_UP:
				if (current_actuator == 0)
				{
					actuators.at(current_actuator)->set_state(ACTUATORSTATE::NONACTIVE);
					actuators.at(current_actuator)->set_state(ACTUATORSTATE::ACTIVE);
				}
				else
				{
					actuators.at(current_actuator--)->set_state(ACTUATORSTATE::NONACTIVE);
					actuators.at(current_actuator)->set_state(ACTUATORSTATE::ACTIVE);
				}

				break;
				/*Key down*/
			case SDLK_DOWN:
				if (current_actuator == actuators.size() - 1)
				{
					actuators.at(current_actuator)->set_state(ACTUATORSTATE::NONACTIVE);
					actuators.at(current_actuator)->set_state(ACTUATORSTATE::ACTIVE);
				}
				else
				{
					actuators.at(current_actuator++)->set_state(ACTUATORSTATE::NONACTIVE);
					actuators.at(current_actuator)->set_state(ACTUATORSTATE::ACTIVE);
				}
				break;
				/*Key enter*/
			case SDLK_RETURN:
				if (ACTUATORSTATE::ACTING == actuators.at(current_actuator)->get_state())
				{
					actuators.at(current_actuator)->act();
				}
				else actuators.at(current_actuator)->set_state(ACTUATORSTATE::NONACTIVE);
				break;
			}
			break;
		}
		/*Keyboard key down*/
		case SDL_KEYDOWN:
			SDL_KeyboardEvent key_ev = std::move(ev_listener->get_key_event());
			switch (key_ev.keysym.sym)
			{
				/*Key enter*/
			case SDLK_RETURN:
				actuators.at(current_actuator)->set_state(ACTUATORSTATE::ACTING);
				break;
			}
			break;
		/*Mouse*/
		case SDL_MOUSEMOTION:
		{
			/*if cursor is in any actuator rectangle*/
			if (set_active_actuator())
				actuators.at(current_actuator)->set_state(ACTUATORSTATE::ACTIVE);
			else std::for_each(actuators.begin(), actuators.end(), 
				[](const std::shared_ptr<Actuator>& in) {in->set_state(ACTUATORSTATE::NONACTIVE); });
			break;
		}
		/*Mouse key down*/
		case SDL_MOUSEBUTTONDOWN:
			/*only left key*/
			if (ev_listener->get_mouseb_event().button == SDL_BUTTON_LEFT)
			{
				if (set_active_actuator())
					actuators.at(current_actuator)->set_state(ACTUATORSTATE::ACTING);
			}
			break;
		/*Mouse key up*/
		case SDL_MOUSEBUTTONUP:
		{
			/*only left key*/
			if (ev_listener->get_mouseb_event().button == SDL_BUTTON_LEFT)
			{
				if (set_active_actuator())
				{
					actuators.at(current_actuator)->act();
				}
			}
			break;
		}
		default:
			break;
		}
	}
}
			


/**
* @brief attaches actuators to control object
* @note  using this function to attach actuators of current menu object
* @note 	after remove_actuators() is called
* @param reference to a vector of actuators
* @retval none
*/
void Actuator_control::add_actuators(std::vector<std::shared_ptr<Actuator>>& _actuators)
{
	actuators.clear();
	/*copying actuator pointers*/
	std::copy(_actuators.begin(), _actuators.end(), back_inserter(actuators));
	current_actuator = 0;
}



/**
* @brief removes all actuators
* @note  called before add_actuators function
* @retval none
*/
void Actuator_control::remove_actuators()
{
	actuators.clear();
}


/**
* @brief sets the indicated by mouse cursor actuator as active
* @note
* @retval true if mouse cursor is in any of conrolled actuators rectangle
*/
bool Actuator_control::set_active_actuator()
{
	int x, y;
	/*getting cursor coordinates*/
	SDL_GetMouseState(&x, &y);
	/*checking collision*/
	std::vector<std::shared_ptr<Actuator>>::iterator it = std::find_if(actuators.begin(), actuators.end(),
		[&](const std::shared_ptr<Actuator>& in) {return in->check_collision(x, y); });
	/*if cursor is in some actuator rectangle*/
	if (it != actuators.end())
	{
		current_actuator = it - actuators.begin();
		return true;
	}
	return false;
}