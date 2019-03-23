/**
  *************************************************************************************************************************
  * @file    Actuator_conrol.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    13-March-2019
  * @brief   Class for controlling buttons, checkboxes. When menu is being active actuators are attached to this 
  * @brief		constrol object via "add_actuators" function. Uses pointer to a Event_listener object to listen for events.
  **************************************************************************************************************************
*/

#ifndef ACTUATOR_CONTROL_H
#define ACTUATOR_CONTROL_H


/*includes*/
#include <memory>
#include <vector>
#include <SDL.h>
#include "Observer.h"
#include "Actuator.h"
#include "Event_listener.h"


class Actuator_control:public Observer
{
public:
	/*Constructor*/
	Actuator_control(std::shared_ptr<Event_listener>);
	/*Destructor*/
	virtual ~Actuator_control() { ; };

	/**
	* @brief updates actuators state
	* @note  called when keyboard or mouse event occurred
	* @retval none
	*/
	virtual void update();

	/**
	* @brief attaches actuators to control object
	* @note  using this function to attach actuators of current menu object 
	* @note 	after remove_actuators() is called
	* @param reference to a vector of actuators
	* @retval none
	*/
	void add_actuators(std::vector<std::shared_ptr<Actuator>>&);

	/**
	* @brief removes all actuators
	* @note  called before add_actuators function
	* @retval none
	*/
	void remove_actuators();

private:
	/**
	* @brief sets the indicated by mouse cursor actuator as active 
	* @note 
	* @retval true if mouse cursor is in any of conrolled actuators rectangle
	*/
	bool set_active_actuator();
private:
	std::vector<std::shared_ptr<Actuator>> actuators; //vector of controlled actuators
	std::shared_ptr<Event_listener> ev_listener; //listen to mouse and keyboard event via this pointer
	Uint32 ev_type; // current event type
	size_t current_actuator; // the index of a current active actuator
};

#endif