/**
  *************************************************************************************************************************
  * @file    Pacman.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Pacman class
  **************************************************************************************************************************
*/
#ifndef PACMAN_H
#define PACMAN_H
/*includes*/
#include<memory>
#include<vector>
#include<string>
#include<SDL.h>
#include"MovableObjects.h"
#include<array>

/*Predeclared  classes*/
class Animation;
class PacmanKeyboard;
class PacmanMoveAlgorithm;
class Map;
class PacmanLife;
enum class Direction;

enum class  PacmanState
{
	STATE_OK = 0,
	STATE_DEAD = 4
};


class Pacman:public MovableObjects
{
	friend class PacmanKeyboard;
private:
	/**
	* @brief nested class
	* @note this class is made to close acess to unique_ptr 
	*/
	class PacLife
	{
	public:
	/**
	* @brief constructor
	* @param1 pointer to paclife object
	*/
		PacLife(std::unique_ptr<PacmanLife>&&);
		PacmanLife* operator->()
		{
			return life.get();
		}
	private:
		std::unique_ptr<PacmanLife> life;
	};
public:
	/**
	* @brief constructor
	* @param1 start rectangle
	* @param2 renderer pointer
	* @param3 map pointer
	* @param4 maze
	* @param5 normal animation path
	* @param6 dead animation path
	*/
	Pacman(SDL_Rect rect,std::shared_ptr<SDL_Renderer> r, std::shared_ptr<Map>, std::vector<int>,
		std::string path,std::string death_image_path);
	/*Destructor*/
	virtual ~Pacman() { ; };

	/**
	* @brief render pacman
	* @note
	* @retval
	*/
	virtual void render();

	/**
	* @brief move object
	* @note
	* @retval new position
	*/
	virtual SDL_Rect move();

	/**
	* @brief set pacman state
	* @note
	* @param1 new pacman state
	* @retval
	*/
	void set_state(PacmanState);

	/**
	* @brief reset pacman 
	* @note return pacman to a start position
	* @retval
	*/
	void reset();

	PacLife Life;//pacman life

private:
	/**
	* @brief alignment by x
	* @note
	* @param1 tile
	* @param2 new position 
	* @retval true if alignment was done
	*/
	bool AlignByX(int, SDL_Point&);

	/**
	* @brief alignment by y
	* @note
	* @param1 tile
	* @param2 new position
	* @retval true if alignment was done
	*/
	bool AlignByY(int, SDL_Point&);

	/**
	* @brief alignment by x and y
	* @note
	* @param1 new position
	* @retval true if alignment was done
	*/
	bool Alignment(SDL_Rect&);

	/**
	* @brief check direction change
	* @note
	* @retval true if direction changed
	*/
	bool DirectionChanged();

	/**
	* @brief set new direction
	* @note
	* @param1 new direction
	* @retval 
	*/
	void set_direction(Direction);
	/**/
	std::shared_ptr<Map> map;//map pointer
	/**/
	Direction direction;
	Direction Prevdirection;
	/**/
	PacmanState state;//current state
	/**/
	std::array<std::unique_ptr<Animation>,5> animation;
	/**/
	//Uint32 StartMsecond;
	/**/
	SDL_Point StartPos;
	/**/
	const std::vector<int> Maze;
};

#endif
