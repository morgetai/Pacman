/**
  *************************************************************************************************************************
  * @file    Command_Base.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    13-March-2019
  * @brief   Base class for command objects
  **************************************************************************************************************************
*/

#ifndef COMMAND_BASE
#define COMMAND_BASE

class Command_Base
{
public:
	/*Destructor*/
	virtual ~Command_Base() { ; };

	/**
	* @brief doing the job
	* @note
	* @retval none
	*/
	virtual void execute() = 0;
protected :
	/*Constructor*/
	Command_Base() { ; };
};

#endif
