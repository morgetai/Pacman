/**
  *************************************************************************************************************************
  * @file    Subject.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    17-March-2019
  * @brief   Subject absract class
  **************************************************************************************************************************
*/
#ifndef SUBJECT_H
#define SUBJECT_H
/*includes*/
#include"Observer.h"
#include <memory>
#include <vector>
#include <algorithm>

class Subject
{
protected:
	/*Constructor*/
	Subject();
	/*destructor*/
	virtual ~Subject() { ; }

	/**
	* @brief attach observers
	* @note
	* @param1 observer pointer
	* @retval 
	*/
	void attach(std::shared_ptr<Observer>) ;

	/**
	* @brief detach observers
	* @note
	* @param1 observer pointer
	* @retval
	*/
	void detach(std::shared_ptr<Observer>) ;

	/**
	* @brief notify all attached observers
	* @note
	* @param1 observer pointer
	* @retval
	*/
	virtual void notify();

private:
	std::vector<std::shared_ptr<Observer>> observers;
};
#endif
