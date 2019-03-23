/**
  *************************************************************************************************************************
  * @file    Observer.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Observer absract class
  **************************************************************************************************************************
*/
#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
public:
	/**
	* @brief update object
	* @note
	* @retval
	*/
	virtual void update() = 0;
	/*Destructor*/
	virtual ~Observer() { ; }
};


#endif
