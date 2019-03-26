/**
  *************************************************************************************************************************
  * @file    Subject.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    17-March-2019
  * @brief   Subject absract class
  **************************************************************************************************************************
*/
/*includes*/
#include"Subject.h"

/*Constructor*/
Subject::Subject()
{
	observers.reserve(5);
}

/**
* @brief attach observers
* @note
* @param1 observer pointer
* @retval
*/
void Subject::attach(std::shared_ptr<Observer> in)
{
	if (in != nullptr)
		observers.push_back(in);
}

/**
* @brief detach observers
* @note
* @param1 observer pointer
* @retval
*/
void Subject::detach(std::shared_ptr<Observer> in)
{
	if (in != nullptr)
	{
		std::vector<std::shared_ptr<Observer>>::iterator it = std::find(observers.begin(), observers.end(), in);
		if (it != observers.end())
			observers.erase(std::find(observers.begin(), observers.end(), in));
	}
}

/**
* @brief notify all attached observers
* @note
* @param1 observer pointer
* @retval
*/
void Subject::notify()
{
	if (!observers.empty())
	{
		std::for_each(observers.begin(), observers.end(), [](std::shared_ptr<Observer>& in) {in->update(); });
	}
}