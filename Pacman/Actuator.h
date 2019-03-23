/**
  *************************************************************************************************************************
  * @file    Actuator.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    13-March-2019
  * @brief   Asbtract base class for buttons, checkboxes.
  **************************************************************************************************************************
*/




#ifndef ACTION_H
#define ACTION_H



enum class ACTUATORSTATE
{
	NONACTIVE = 0xFF,
	ACTIVE = 0x01,
	ACTING = 0x2
};

class Actuator
{
public:

	/*Constructor*/
	Actuator() : state(ACTUATORSTATE::NONACTIVE) { ; }

	/*Destructor*/
	virtual ~Actuator() { ; };
	
	/**
	* @brief rendring the actuator
	* @retval none
	*/
	virtual void render() = 0;
	  
	/**
	* @brief performs the action
	* @note  this function is called when actuator is in ACTING state.
	* @retval none
	*/
	virtual void act() = 0; //
	 
	/**
	* @brief checks to see if sursor is in the actuator rectangle
	* @note  this function is called when actuator is in ACTING state.
	* @param1 x of mause position
	* @param2 y of mause position
	* @retval true when mouse coursor is in actuator rectangle
	*/
	virtual bool check_collision(int x, int y) = 0;
	
	/**
	* @brief sets current state
	* @note  
	* @retval none
	*/
	void set_state(ACTUATORSTATE _state) { state = _state; }
	
	/**
	* @brief returns current state
	* @note  
	* @retval ACTUATORSTATE
	*/
	ACTUATORSTATE get_state() { return state; }

	/**/
protected:
	ACTUATORSTATE state; //Current state
};

#endif
