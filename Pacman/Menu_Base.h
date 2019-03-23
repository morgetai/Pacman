/**
  *************************************************************************************************************************
  * @file    Menu_base.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Menu base class
  **************************************************************************************************************************
*/
#ifndef MANU_BASE_H
#define MANU_BASE_H
/*includes*/
#include "Actuator.h"
#include "Actuator_constrol.h"
#include <vector>
#include <memory>

class Menu_Base
{
public:
	/**
	* @brief renders current menu
	* @note
	* @retval
	*/
	virtual void render() = 0;
	/*Destructor*/
	virtual ~Menu_Base() { ; };

	/**
	* @brief attaches the current menu actuators to actuator control object
	* @note called when menu is activated
	* @retval
	*/
	void attach_actuators() { act_control->add_actuators(actuators); };

	/**
	* @brief deteches the current menu actuators to actuator control object
	* @note called when menu is closing
	* @retval
	*/
	void detach_actuators() { act_control->remove_actuators(); }
protected:
	/**
	* @brief constructor
	* @param1 actuator control pointer
	*/
	Menu_Base(std::shared_ptr<Actuator_control> _act_control) : act_control(_act_control){ actuators.reserve(5); }

	/**/
	std::vector<std::shared_ptr<Actuator>> actuators;//buttons, checkboxes
	std::shared_ptr<Actuator_control> act_control;
};

#endif