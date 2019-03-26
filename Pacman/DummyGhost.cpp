/**
  *************************************************************************************************************************
  * @file    DummyGhost.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    13-March-2019
  * @brief   Dummy ghost class
  **************************************************************************************************************************
*/
/*includes*/
#include<sstream>
#include "DummyGhost.h"
#include"Animation.h"
#include"GhostBase.h"
#include"SmartAlgoMove.h"
#include"DummyAlgoMove.h"
#include"RandomAlgoMove.h"
#include"Primitives.h"
#include"Tile.h"
#include"Map.h"
#include"MoveAlgorithmBase.h"
#include"Help.h"
#include"DefaultValues.h"

/**
* @brief constructor
* @param1 path to normal animation file
* @param2 path to eaten animation file
* @param3 path to frightened animation file
* @param4 path to second frightened animation file
* @param5 start rectangle
* @param6 scatter point
* @param7 point near ghost house
* @param8 pacman pointer
* @param9 maze
* @param9 map pointer
* @param10 renderer pointer
*/
DummyGhost::DummyGhost(std::string NormalAnimPath, std::string EatenAnimPath,
	std::string FrightenedAnimPath, std::string FrightenedEndAnimPath,
	SDL_Rect startpos, SDL_Point scatterpoint, SDL_Point getfromhousepoint,
	std::shared_ptr<MovableObjects> pacman, 
	std::vector<int> maze, std::shared_ptr<Map> map,
	std::shared_ptr<SDL_Renderer> r):
	FrightenedAnim(std::make_unique<Animation>(
		DefaultValues::TileWidth, DefaultValues::TileHeight,
		2,//number of images used in animation
		SpriteOrientation::HORIZONTAL, 
		r, FrightenedAnimPath)),

	FrightenedAnimEnd(std::make_unique<Animation>(
		DefaultValues::TileWidth, DefaultValues::TileHeight,
		2,//number of images used in animation
		SpriteOrientation::HORIZONTAL,
		r, FrightenedEndAnimPath)),

	SmartAlgo(std::make_unique<SmartAlgoMove>(maze, this)),
	DummyAlgo(std::make_unique<DummyAlgoMove>(map,this)),
	RandomAlgo(std::make_unique<RandomAlgoMove>(map, this)),

	Pacman(pacman),

	ScatterPoint(scatterpoint),
	GetFromHousePoint(getfromhousepoint),
	state(GhostState::SCATTER),
	GetFromHouse(true),
	GhostBase(startpos)
{
	/*creating rectangle from a point*/
	GetFromHouseRect.x = getfromhousepoint.x; GetFromHouseRect.y = getfromhousepoint.y;
	GetFromHouseRect.w = 2; GetFromHouseRect.h = 2;
	/*creating rectangle from a point*/
	EatenRect = startpos;  EatenRect.w = 3; EatenRect.h = 3;
	EatenPoint.x = startpos.x; EatenPoint.y = startpos.y;

	/*reading normal animation files*/
	std::istringstream ss(NormalAnimPath);
	std::string str;
	size_t index = 0;

	while (!ss.eof())
	{
		std::getline(ss, str, ' ');
		NormalAnimation[index++] = std::make_unique<Animation>(
			DefaultValues::TileWidth, DefaultValues::TileHeight,
			2, //number of images used in animation
			SpriteOrientation::HORIZONTAL, r, str);
	}
	index = 0;
	/*reading eaten animation files*/
	ss.str(EatenAnimPath);
	ss.clear();
	while (!ss.eof())
	{
		std::getline(ss, str, ' ');
		EatenImg[index++] = std::make_unique<Image>(
			DefaultValues::TileWidth, DefaultValues::TileHeight,
			0, 0, //position x and y
			r, str);
	}
}

/*Destructor*/
DummyGhost::~DummyGhost()
{
}

/**
* @brief move ghost
* @note
* @retval returns new ghost rectangle
*/
SDL_Rect DummyGhost::move()
{
	switch (state)
	{
	case GhostState::CHASE:
		move_chase();
		break;
	case GhostState::SCATTER:
		move_scatter();
		break;
	case GhostState::FRIGHTENED:
		move_frightened();
		break;
	case GhostState::EATEN:
		move_eaten();
		break;
	}
	return get_rect();
}

/**
* @brief moving in chase state
* @note
* @retval none
*/
void DummyGhost::move_chase()
{
	Move move;
	if (GetFromHouse)
	{
		move = move_from_home(DummyAlgo, Pacman->get_pos());
	}
	else
	{
		move = DummyAlgo->get_move(Pacman->get_pos());
	}

	/*if there is some direction*/
	if (!(move.direction == Direction::NONE))
	{
		direction = move.direction;
		set_pos(move.pos);
	}
}

/**
* @brief moving in scatter state
* @note
* @retval none
*/
void DummyGhost::move_scatter()
{
	Move move;
	if (GetFromHouse)
	{
		move = move_from_home(SmartAlgo, ScatterPoint);
	}
	else
	{
		move = SmartAlgo->get_move(ScatterPoint);
	}

	/*if there is some direction*/
	if (!(move.direction == Direction::NONE))
	{
		direction = move.direction;
		set_pos(move.pos);
	}
}

/**
* @brief moving in frightened state
* @note
* @retval none
*/
void DummyGhost::move_frightened()
{
	Move move;
	if (GetFromHouse)
	{
		move = move_from_home(RandomAlgo, SDL_Point{});
	}
	else
	{ 
		move = RandomAlgo->get_move(SDL_Point{});
	}

	/*if there is some direction*/
	if (!(move.direction == Direction::NONE))
	{
		direction = move.direction;
		set_pos(move.pos);
	}
}

/**
* @brief moving in eaten state
* @note
* @retval none
*/
void DummyGhost::move_eaten()
{
	Move move;
	move = SmartAlgo->get_move(EatenPoint, DefaultValues::GhostVelocity * 2);


	if (!(move.direction == Direction::NONE))
	{
		direction = move.direction;
		set_pos(move.pos);
	}
	else
	{
		/*if ghost is at start point return state to previous*/
		state = prev_state;
	}
}

/**
* @brief getting from ghost house
* @param1 reference to a current move algorithm
* @note
* @retval move
*/
Move DummyGhost::move_from_home(std::unique_ptr<MoveAlgorithmBase>& movealgo, SDL_Point dest)
{
	/*if got out of ghost home then use normal algorithm*/
	if (SDL_PointInRect(&get_pos(), &GetFromHouseRect))
	{
		GetFromHouse = false;
		return movealgo->get_move(dest);
	}
	/*use smart algorithm to get from house*/
	else
	{
		return SmartAlgo->get_move(GetFromHousePoint);
	}
}

/**
* @brief render ghost
* @retval none
*/
void DummyGhost::render()
{
	switch (state)
	{
	case GhostState::CHASE:
		NormalAnimation[static_cast<size_t>(direction)]->setpos(get_pos());
		NormalAnimation[static_cast<size_t>(direction)]->render();
		break;
	case GhostState::SCATTER:
		NormalAnimation[static_cast<size_t>(direction)]->setpos(get_pos());
		NormalAnimation[static_cast<size_t>(direction)]->render();
		break;
	case GhostState::FRIGHTENED:
		/*change animation when 2 seconds left*/
		if (!TimeElapsed(3000, StartFrTime))
		{
			FrightenedAnim->setpos(get_pos());
			FrightenedAnim->render();
		}
		else
		{
			if (!(SDL_GetTicks() % 4))
			{
				FrightenedAnim->setpos(get_pos());
				FrightenedAnim->render();
			}
			else
			{
				FrightenedAnimEnd->setpos(get_pos());
				FrightenedAnimEnd->render();
			}

		}
		break;
	case GhostState::EATEN:
		EatenImg[static_cast<size_t>(direction)]->set_pos(get_pos());
		EatenImg[static_cast<size_t>(direction)]->render();
		break;
	}
}

/**
* @brief returns ghost state
* @note
* @retval ghjost state
*/
GhostState DummyGhost::get_state()
{
	return state;
}

/**
* @brief setting ghost state
* @param1 new state
* @note
* @retval
*/
void DummyGhost::set_state(GhostState _state)
{
	switch (_state)
	{
	case GhostState::FRIGHTENED:
		if (state == GhostState::FRIGHTENED)
		{
			StartFrTime = SDL_GetTicks();
		}
		else if (state != GhostState::EATEN)
		{
			StartFrTime = SDL_GetTicks();
			prev_state = state;
			state = _state;
		}
		break;
	case GhostState::EATEN:
		if (state == GhostState::FRIGHTENED)
		{
			state = _state;
			GetFromHouse = true;
		}
		break;
	default:
		if (state == GhostState::EATEN)
		{
			prev_state = _state;
		}
		else
		{
			state = _state;
		}
	}
}


void DummyGhost::reset()
{
	SDL_Point p; p.x = EatenRect.x; p.y = EatenRect.y;
	set_pos(p);
	GetFromHouse = true;
	state = GhostState::SCATTER;
}