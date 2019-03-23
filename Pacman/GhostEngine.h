/**
  *************************************************************************************************************************
  * @file    GhostEngine.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    14-March-2019
  * @brief   Controls ghosts behavior
  **************************************************************************************************************************
*/
#ifndef GHOST_ENGINE
#define GHOST_ENGINE
/*includes*/
#include<array>
#include<memory>
#include<SDL.h>
#include<vector>
#include"GhostBase.h"
/*Predeclared  classes*/
class Map;
class MovableObjects;
enum class GhostState;

enum class GHOST_COLLISION
{
	MINUS_PACMAN_LIFE,
	GHOST_EATEN,
	NONE
};


class GhostEngine
{
public:
	/**
	* @brief constructor
	* @param1 pacman pointer
	* @param2 maze
	* @param3 map pointer
	* @param4 renderer pointer
	*/
	GhostEngine(std::shared_ptr<MovableObjects>, std::vector<int>,
		std::shared_ptr<Map>,std::shared_ptr<SDL_Renderer>);

	/**
	* @brief runs ghost engine
	* @note
	* @retval
	*/
	void run();

	/**
	* @brief render all ghosts
	* @note
	* @retval
	*/
	void render();

	/**
	* @brief set all ghosts as frightened
	* @note
	* @retval
	*/
	void SetFrightened();

	/**
	* @brief reset all ghosts
	* @note reset start time, number of active ghosts
	* @retval
	*/
	void Reset();

	/**
	* @brief return ghosts to a start position
	* @note
	* @retval
	*/
	void MoveToStartPos();

	/**
	* @brief pause the engine
	* @note
	* @retval
	*/
	void Pause();

	/**
	* @brief check possible intersection with all ghosts
	* @param1 pacman rectangle
	* @note
	* @retval enum GHOST_COLLISION
	*/
	GHOST_COLLISION check_ghost_collision(SDL_Rect);

private:
	/**
	* @brief scatter state behavior
	* @note
	* @retval
	*/
	void scatter();

	/**
	* @brief chase state behavior
	* @note
	* @retval
	*/
	void chase();

	/**
	* @brief frughtened state behavior
	* @note
	* @retval
	*/
	void frightened();

	/**
	* @brief set currrent state for all ghosts
	* @note
	* @retval
	*/
	void set_ghosts_state();

	/**
	* @brief move all ghosts
	* @note
	* @retval
	*/
	void move_ghosts();

	/**
	* @brief checks if delay time has elapsed
	* @note
	* @param1 delay in mseconds
	* @retval true if time elapsed
	*/
	bool time_elapsed( Uint32 delay);
	/**/
	typedef std::unique_ptr<GhostBase> Ghostptr;
	typedef std::array<Ghostptr, 4>::iterator GhostIt;
	std::array<Ghostptr, 4> ghosts; 
	std::array<std::pair<Uint32, Uint32> ,4> waves; 

	GhostState state;//current state
	GhostState prev_state;
	/**/
	Uint32 diff_time;//the remaining time of the current state interrupted by frightened state
	Uint32 start_msecond;//start time 
	Uint32 frightened_delay;
	short active_ghosts;//number of active ghosts
	short wave;//number of the current wave
	bool save_frightened_ms;//save current time at start of frightened state
	bool start;//true if engine is running
};
#endif // !GHOST_ENGINE

