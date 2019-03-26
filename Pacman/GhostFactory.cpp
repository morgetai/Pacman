/**
  *************************************************************************************************************************
  * @file    GhostFactory.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    15-March-2019
  * @brief   Creats ghosts
  **************************************************************************************************************************
*/
/*includes*/
#include "GhostFactory.h"
#include"GhostBase.h"
#include"RedGhost.h"
#include"DummyGhost.h"
#include"Tile.h"
#include"Help.h"
#include"DefaultValues.h"

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
GhostFactory::GhostFactory(std::shared_ptr<MovableObjects> _Pacman, std::vector<int> _Maze,
	std::shared_ptr<Map> _map, std::shared_ptr<SDL_Renderer> R,
	std::string _EatenAnimPath, std::string _FrighteneAnimPath, std::string _FrighteneEndAnimPath):
	Pacman(_Pacman),
	Maze(_Maze),
	map(_map),
	Renderer(R),
	EatenAnimPath(_EatenAnimPath),
	FrighteneAnimPath(_FrighteneAnimPath),
	FrightenedEndAnimPath(_FrighteneEndAnimPath)
{

}

/*Destructor*/
GhostFactory::~GhostFactory()
{}

/**
* @brief creates red ghost
* @param1 path to the red ghost alive animation file
* @note
* @retval pointer to the red ghost object
*/
std::unique_ptr<GhostBase> GhostFactory::getRedGhost(std::string RedAliveAnim)
{
	/*starting point*/
	SDL_Point p(TileToSDL_Point(DefaultValues::RedGhostStartTile));
	SDL_Rect RedRect; 
	RedRect.x = p.x; RedRect.y = p.y;
	RedRect.w = DefaultValues::TileWidth; RedRect.h = DefaultValues::TileHeight;
	/**/
	SDL_Point scatter(TileToSDL_Point(DefaultValues::RedGhostScatterTile));
	/**/
	SDL_Point eaten(TileToSDL_Point(DefaultValues::RedGhostEatenTile));
	/*create red ghost*/
	return std::make_unique<RedGhost>(
		RedAliveAnim,
		EatenAnimPath,
		FrighteneAnimPath,
		FrightenedEndAnimPath,
		RedRect, scatter, eaten, 
		Pacman,
		Maze,
		map,
		Renderer);
}

/**
* @brief creates pink ghost
* @param1 path to the red ghost alive animation file
* @note
* @retval pointer to the red ghost object
*/
std::unique_ptr<GhostBase> GhostFactory::getPinkGhost(std::string PinkAliveAnim)
{
	/*starting point*/
	SDL_Point p(TileToSDL_Point(DefaultValues::PinkGhostStartTile));
	SDL_Rect PinkRect; 
	PinkRect.x = p.x; PinkRect.y = p.y;
	PinkRect.w = DefaultValues::TileWidth; PinkRect.h = DefaultValues::TileHeight;
	/**/
	SDL_Point scatter(TileToSDL_Point(DefaultValues::PinkGhostScatterTile));
	/**/
	SDL_Point getfromhouse(TileToSDL_Point(DefaultValues::PinkGhostLeaveHouseTile));
	/*create pink ghost*/
	return std::make_unique<DummyGhost>(
		PinkAliveAnim,
		EatenAnimPath,
		FrighteneAnimPath,
		FrightenedEndAnimPath,
		PinkRect, scatter, getfromhouse,
		Pacman,
		Maze,
		map,
		Renderer);
}

/**
* @brief creates blue ghost
* @param1 path to the red ghost alive animation file
* @note
* @retval pointer to the red ghost object
*/
std::unique_ptr<GhostBase> GhostFactory::getBlueGhost(std::string BlueAliveAnim)
{
	/*starting point*/
	SDL_Point p(TileToSDL_Point(DefaultValues::BlueGhostStartTile));
	SDL_Rect BlueRect;
	BlueRect.x = p.x; BlueRect.y = p.y;
	BlueRect.w = DefaultValues::TileWidth; BlueRect.h = DefaultValues::TileHeight;
	/**/
	SDL_Point scatter(TileToSDL_Point(DefaultValues::BlueGhostScatterTile));
	/**/
	SDL_Point getfromhouse(TileToSDL_Point(DefaultValues::BlueGhostLeaveHouseTile));
	/*create blue ghost*/
	return std::make_unique<DummyGhost>(
		BlueAliveAnim,
		EatenAnimPath,
		FrighteneAnimPath,
		FrightenedEndAnimPath,
		BlueRect, scatter, getfromhouse,
		Pacman,
		Maze,
		map,
		Renderer);
}

/**
* @brief creates yellow ghost
* @param1 path to the red ghost alive animation file
* @note
* @retval pointer to the red ghost object
*/
std::unique_ptr<GhostBase> GhostFactory::getYellowGhost(std::string YellowAliveAnim)
{
	/*starting point*/
	SDL_Point p(TileToSDL_Point(DefaultValues::YellowGhostStartTile));
	SDL_Rect YellowRect;
	YellowRect.x = p.x; YellowRect.y = p.y;
	YellowRect.w = DefaultValues::TileWidth; YellowRect.h = DefaultValues::TileHeight;
	/**/
	SDL_Point scatter(TileToSDL_Point(DefaultValues::YellowGhostScatterTile));
	/**/
	SDL_Point getfromhouse(TileToSDL_Point(DefaultValues::YellowGhostLeaveHouseTile));
	/*create yellow ghost*/
	return std::make_unique<DummyGhost>(
		YellowAliveAnim,
		EatenAnimPath,
		FrighteneAnimPath,
		FrightenedEndAnimPath,
		YellowRect, scatter, getfromhouse,
		Pacman,
		Maze,
		map,
		Renderer);
}