/**
  *************************************************************************************************************************
  * @file    GhostFactory.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    15-March-2019
  * @brief   Creats ghosts
  **************************************************************************************************************************
*/

#ifndef GHOST_FACTORY_H
#define GHOST_FACTORY_H
/*includes*/
#include<memory>
#include<string>
#include<vector>
#include<SDL.h>
/*Predeclared  classes*/
class GhostBase;
class MovableObjects;
class Map;

class GhostFactory
{
public:
	/**
	* @brief constructor
	* @param1 pacman pointer
	* @param2 maze
	* @param3 map pointer
	* @param4 renderer pointer
	* @param5 path to the eaten ghost animation file
	* @param6 path to the frightened ghost animation file
	* @param7 path to the second frightened ghost animation file
	*/
	GhostFactory(std::shared_ptr<MovableObjects>, std::vector<int>,
		std::shared_ptr<Map>, std::shared_ptr<SDL_Renderer>,
		std::string, std::string, std::string);
	/*Destructor*/
	~GhostFactory();

	/**
	* @brief creates red ghost
	* @param1 path to the red ghost alive animation file 
	* @note
	* @retval pointer to the red ghost object
	*/
	std::unique_ptr<GhostBase> getRedGhost(std::string);

	/**
	* @brief creates pink ghost
	* @param1 path to the red ghost alive animation file
	* @note
	* @retval pointer to the red ghost object
	*/
	std::unique_ptr<GhostBase> getPinkGhost(std::string);

	/**
	* @brief creates blue ghost
	* @param1 path to the red ghost alive animation file
	* @note
	* @retval pointer to the red ghost object
	*/
	std::unique_ptr<GhostBase> getBlueGhost(std::string);

	/**
	* @brief creates yellow ghost
	* @param1 path to the red ghost alive animation file
	* @note
	* @retval pointer to the red ghost object
	*/
	std::unique_ptr<GhostBase> getYellowGhost(std::string);
private:
	std::shared_ptr<MovableObjects> Pacman;//pacman pointer
	std::vector<int> Maze;
	std::shared_ptr<Map> map;
	std::shared_ptr<SDL_Renderer> Renderer;
	/**/
	std::string EatenAnimPath;
	std::string FrighteneAnimPath;
	std::string FrightenedEndAnimPath;
};

#endif