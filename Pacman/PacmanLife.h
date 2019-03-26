/**
  *************************************************************************************************************************
  * @file    PacLife.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Pacman life
  **************************************************************************************************************************
*/
#ifndef  PACMAN_LIFE_H
#define PACMAN_LIFE_H
/*includes*/
#include<memory>
#include<SDL.h>
#include<string>

/*Predeclared  classes*/
class Image;

class PacmanLife
{
public:
	/**
	* @brief constructor
	* @param1 path to image
	* @param2 renderer pointer
	*/
	PacmanLife(std::string,std::shared_ptr<SDL_Renderer>);
	/*Destructor*/
	~PacmanLife();

	/**
	* @brief render pacman
	* @note
	* @retval
	*/
	void render();

	/**
	* @brief decrement operator
	* @note 
	* @retval paclife reference
	*/
	PacmanLife& operator--();

	/**
	* @brief cast to bool
	* @note 
	* @retval true if life is greater then 0
	*/
	operator bool() const;

	/**
	* @brief return pacman to a start position
	* @note
	* @retval
	*/
	void reset();

	/**
	* @brief return life object
	* @note
	* @retval reference to the paclife
	*/
	PacmanLife& lives()
	{
		return *this;
	}
private:
	std::unique_ptr<Image> LifeImg;
	int life;//number of lives
	SDL_Point pos;//position at which image will be rendered
};

#endif // ! 