/**
  *************************************************************************************************************************
  * @file    Engine_state.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    14-March-2019
  * @brief   EngineState class. Part of state pattern
  **************************************************************************************************************************
*/
#ifndef ENGINE_STATE_H
#define ENGINE_STATE_H


/*Predeclared  classes*/
enum class EngineStateType;
class Engine;

class EngineState
{
public :
	/**
	* @brief runs current state
	* @note  
	* @param1 pointer to the engine
	* @retval 
	*/
	virtual void run(Engine*) = 0;

	/**
	* @brief close current state
	* @note
	* @param1 pointer to the engine
	* @retval
	*/
	virtual void close(Engine*) = 0;
	/*Destructor*/
	virtual ~EngineState() { ; };

	/**
	* @brief active state
	* @note
	* @retval true if state is active
	*/
	bool is_active() { return active; }
protected:
	/*Constructor*/
	EngineState() = default;
	/**
	* @brief changes the engine state
	* @note
	* @param1 pointer to the engine
	* @param1 new state
	* @retval 
	*/
	void chagestate(Engine* engine, EngineStateType state);
	bool active;//true if state is active
};

#endif
