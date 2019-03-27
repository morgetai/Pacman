/**
  *************************************************************************************************************************
  * @file    Command.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    15-March-2019
  * @brief   Command object
  **************************************************************************************************************************
*/
#ifndef COMMAND_H
#define COMMAND_H
/*includes*/
#include"Command_base.h"

/*Base class*/
template <typename ...Args> 
class  Command;

/*Specialization*/
template <typename Receiver>
class Command <Receiver> :public Command_Base
{
public:
	/*Action is a member function pointer type*/
	typedef void (Receiver::* Action)();

	/**
	* @brief constructor
	* @param1 receiver class pointer
	* @param2 member function
	*/
	Command(Receiver* _receiver, Action _action) : receiver(_receiver), action(_action) {}
	/*Destructor*/
	virtual ~Command() { ; }
	/**
	* @brief runs given member function on a given class object
	* @note
	* @retval
	*/
	void execute() override { (receiver->*action)(); }
private:
	Receiver* const receiver;//receiver class
	Action action;//member function
};

/*Specialization*/
template <typename Receiver, typename Parameter_Type> 
class Command<Receiver, Parameter_Type>:public Command_Base
{
public:
	/*Action is a member function pointer type*/
	typedef void (Receiver::* Action)(Parameter_Type);

	/**
	* @brief constructor
	* @param1 receiver class pointer
	* @param2 member function
	* @param3 parameter
	*/
	Command(Receiver* _receiver, Action _action, Parameter_Type _param) : receiver(_receiver), 
		action(_action), param(_param){}
	/*Destructor*/
	virtual ~Command() { ; }

	/**
	* @brief runs given member function on a given class object
	* @note
	* @retval
	*/
	void execute() override { (receiver->*action)(param); }
private:
	Receiver* const receiver;//receiver class
	Action action;//member function
	Parameter_Type param;//parameter type
};

#endif
