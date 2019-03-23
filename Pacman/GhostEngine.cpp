/**
  *************************************************************************************************************************
  * @file    GhostEngine.cpp
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    14-March-2019
  * @brief   Controls ghosts behavior
  **************************************************************************************************************************
*/
/*includes*/
#include"GhostEngine.h"
#include"RedGhost.h"
#include"Tile.h"
#include"MovableObjects.h"
#include"Map.h"
#include"DummyAlgoMove.h"
#include"SmartAlgoMove.h"
#include"Animation.h"
#include"GhostBase.h"
#include"GhostFactory.h"
#include"DefaultValues.h"
#include<algorithm>
#include<SDL_timer.h>

/**
* @brief constructor
* @param1 pacman pointer
* @param2 maze
* @param3 map pointer
* @param4 renderer pointer
*/
GhostEngine::GhostEngine(std::shared_ptr<MovableObjects> pacman, std::vector<int> maze, 
	std::shared_ptr<Map> map, std::shared_ptr<SDL_Renderer> r):

state(GhostState::SCATTER),
frightened_delay(5000),
active_ghosts(1),
wave(0),
save_frightened_ms(false),
start(false)
{

GhostFactory Factory(pacman, maze, map, r,
	DefaultValues::GhostDeadImage,
	DefaultValues::GhostFrightenedImage, DefaultValues::GhostFrightenedEndImage);

	ghosts[0] = std::move(
		Factory.getRedGhost(DefaultValues::RedGhostAliveAnim));
	ghosts[1] = std::move(
		Factory.getPinkGhost(DefaultValues::PinkGhostAliveAnim));
	ghosts[2] = std::move(
		Factory.getBlueGhost(DefaultValues::BlueGhostAliveAnim));
	ghosts[3] = std::move(
		Factory.getYellowGhost(DefaultValues::YellowGhostAliveAnim));
	/*waves*/
	waves[0].first = 7000;
	waves[0].second = 20000;
	waves[1].first = 7000;
	waves[1].second = 20000;
	waves[2].first = 5000;
	waves[2].second = 20000;
	waves[3].first = 5000;
	waves[3].second = 0;
}

/**
* @brief runs ghost engine
* @note
* @retval
*/
void GhostEngine::run()
{
	/*if not running*/
	if (!start)
	{
		start_msecond = SDL_GetTicks();
		set_ghosts_state();
		start = true;
	}
	switch (state)
	{
	case GhostState::SCATTER:
		scatter();
		break;
	case GhostState::CHASE:
		chase();
		break;
	case GhostState::FRIGHTENED:
		frightened();
		break;
	default:
		;
	}
}

/**
* @brief scatter state behavior
* @note
* @retval
*/
void GhostEngine::scatter()
{
	/*changing state*/
	if (time_elapsed(waves[wave].first))
	{
		state = GhostState::CHASE;
		if (active_ghosts < 4)
		{
			++active_ghosts;
		}
		set_ghosts_state();
	}

	/*acting state*/
	else
	{
		move_ghosts();
	}
}

/**
* @brief chase state behavior
* @note
* @retval
*/
void GhostEngine::chase()
{
	/*changing state*/
	if (time_elapsed(waves[wave].second))
	{
		if (wave < 3)
		{
			++wave;
			state = GhostState::SCATTER;
		}
		if (active_ghosts < 4)
		{
			++active_ghosts;
		}
		set_ghosts_state();
		start_msecond = SDL_GetTicks();
	}

	/*acting state*/
	else
	{
		move_ghosts();
	}
}

/**
* @brief frughtened state behavior
* @note
* @retval
*/
void GhostEngine::frightened()
{
	/*save start time*/
	if (!save_frightened_ms)
	{
		/**/
		save_frightened_ms = true;
		Uint32 current_msecond = SDL_GetTicks();
		/*calculate the remaining for the current state*/
		diff_time = current_msecond - start_msecond;
		start_msecond = current_msecond;
		/*set all ghosts as frightened*/
		set_ghosts_state();
	}
	/*if time elapsed*/
	if (time_elapsed(frightened_delay))
	{
		save_frightened_ms = false;
		/*setting the start time of previous state*/
		start_msecond = SDL_GetTicks() - diff_time;
		/*setting current state as previous*/
		state = prev_state;
		set_ghosts_state();
	}
	else
	{
		move_ghosts();
	}
}

/**
* @brief set all ghosts as frightened
* @note
* @retval
*/
void GhostEngine::SetFrightened()
{
	switch (state)
	{
	case GhostState::FRIGHTENED:
		save_frightened_ms = false;
		break;
	default:
		prev_state = state;
		state = GhostState::FRIGHTENED;
	}
}

/**
* @brief checks if delay time has elapsed
* @note
* @param1 delay in mseconds
* @retval true if time elapsed
*/
bool GhostEngine::time_elapsed( Uint32 delay)
{
	if (delay == 0) return false;
	Uint32 current_msecond = SDL_GetTicks();

	if ((current_msecond - start_msecond) >= delay)
		return true;
	else return false;
}

/**
* @brief set currrent state for all ghosts
* @note set state of active ghosts
* @retval
*/
void GhostEngine::set_ghosts_state()
{
	uint16_t i = 0;
	for (GhostIt ghost = ghosts.begin(); ghost < ghosts.end() && i < active_ghosts; ++ghost, ++i)
	{
		(*ghost)->set_state(state);
	}
}

/**
* @brief move all ghosts
* @note move active ghosts
* @retval
*/
void GhostEngine::move_ghosts()
{
	uint16_t i = 0;
	for (GhostIt ghost = ghosts.begin(); ghost < ghosts.end() && i < active_ghosts; ++ghost, ++i)
	{
		(*ghost)->move();
	}
}

/**
* @brief render all ghosts
* @note
* @retval
*/
void GhostEngine::render()
{
	std::for_each(ghosts.begin(), ghosts.end(), [](const Ghostptr& ghost)
	{
		ghost->render();
	});
}

/**
* @brief check possible intersection with all ghosts
* @param1 pacman rectangle
* @note
* @retval enum GHOST_COLLISION
*/
GHOST_COLLISION GhostEngine::check_ghost_collision(SDL_Rect pacman)
{
	for (GhostIt ghost = ghosts.begin(); ghost < ghosts.end(); ++ghost)
	{

		if (SDL_HasIntersection(&pacman, &(*ghost)->get_rect()))
		{
			switch (state)
			{
			case GhostState::FRIGHTENED:
				if ((*ghost)->get_state() != GhostState::EATEN)
				{
					(*ghost)->set_state(GhostState::EATEN);
					return GHOST_COLLISION::GHOST_EATEN; // returning ghost eaten
				}
			default:
				if ((*ghost)->get_state() != GhostState::EATEN)
					return GHOST_COLLISION::MINUS_PACMAN_LIFE; // returning -life to pacman
			}
		}

	}
	return GHOST_COLLISION::NONE; // nothing happened
}

/**
* @brief reset all ghosts
* @note reset start time, number of active ghosts
* @retval
*/
void GhostEngine::Reset()
{
	std::for_each(ghosts.begin(), ghosts.end(), [](Ghostptr& ghost)
	{
		ghost->reset();
	});
	start = false;
	save_frightened_ms = false;
	active_ghosts = 1;
	wave = 0;
	state = GhostState::SCATTER;
}

/**
* @brief return ghosts to a start position
* @note
* @retval
*/
void GhostEngine::MoveToStartPos()
{
	std::for_each(ghosts.begin(), ghosts.end(), [](Ghostptr& ghost)
	{
		ghost->reset();
	});
}

/**
* @brief pause the engine
* @note
* @retval
*/
void GhostEngine::Pause()
{
	start = false;
}

