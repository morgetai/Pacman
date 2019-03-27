/**
  *************************************************************************************************************************
  * @file    RedGhost.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   RedGhost class
  **************************************************************************************************************************
*/
/*includes*/
#include"RedGhost.h"
#include"SmartAlgoMove.h"
#include"Animation.h"
#include"MoveAlgorithmBase.h"
#include"Tile.h"
#include"Map.h"
#include"RandomAlgoMove.h"
#include"Primitives.h"
#include"DefaultValues.h"
#include<sstream>

/**
* @brief constructor
* @param1 path to normal animation file
* @param2 path to eaten animation file
* @param3 path to frightened animation file
* @param4 path to second frightened animation file
* @param5 start rectangle
* @param6 scatter point
* @param7 eaten point
* @param8 pacman pointer
* @param9 maze
* @param10 map pointer
* @param11 renderer pointer
*/
RedGhost::RedGhost(std::string NormalAnimPath, std::string EatenAnimPath,
	std::string FrighteneAnimPath, std::string FrightenedEndAnimPath,
	SDL_Rect startpos, SDL_Point scatterpoint, SDL_Point eatenpoint,
	std::shared_ptr<MovableObjects> pacman, 
	std::vector<int> maze, std::shared_ptr<Map> _map,
	std::shared_ptr<SDL_Renderer> r):

	FrightenedAnim(std::make_unique<Animation>(DefaultValues::TileWidth, DefaultValues::TileHeight,
		2,//number of images
		SpriteOrientation::HORIZONTAL, r, FrighteneAnimPath)),

	FrightenedAnimEnd(std::make_unique<Animation>(DefaultValues::TileWidth, DefaultValues::TileHeight,
		2,//number of images
		SpriteOrientation::HORIZONTAL, r, FrightenedEndAnimPath)),

	Pacman(pacman),
	SmartAlgo(std::make_unique<SmartAlgoMove>(maze,this)),
	RandomAlgo(std::make_unique<RandomAlgoMove>(_map,this)),
	state ( GhostState::SCATTER),
	GhostBase(startpos)

{
	ScatterPoint = scatterpoint;
	EatenPoint = eatenpoint;
	EatenRect.w = 3; EatenRect.h = 3; EatenRect.x = eatenpoint.x; EatenRect.y = eatenpoint.y;
	StartPoint.x = startpos.x; StartPoint.y = startpos.y;
	
	/*read normal animation*/
	std::istringstream ss(NormalAnimPath);
	std::string str;
	size_t index = 0;
	while (!ss.eof())
	{
		std::getline(ss, str, ' ');
		NormalAnimation[index++] = std::make_unique<Animation>(DefaultValues::TileWidth, DefaultValues::TileHeight,
			2, //number of images
			SpriteOrientation::HORIZONTAL, r, str);
	}


	index = 0;
	/*read eaten animation*/
	ss.str(EatenAnimPath);
	ss.clear();
	while (!ss.eof())
	{
		std::getline(ss, str, ' ');
		EatenImg[index++]  = std::make_unique<Image>(DefaultValues::TileWidth, DefaultValues::TileHeight, 0, 0, r, str);
	}
}

/*Destructor*/
RedGhost::~RedGhost() { ; }

/**
* @brief move ghost
* @note
* @retval returns new ghost rectangle
*/
SDL_Rect RedGhost::move()
{
	switch (state)
	{
	case GhostState::CHASE:
		move_base(SmartAlgo->get_move(Pacman->get_pos()));
		break;
	case GhostState::SCATTER:
		move_base(SmartAlgo->get_move(ScatterPoint));
		break;
	case GhostState::FRIGHTENED:
		move_base(RandomAlgo->get_move(SDL_Point{}));
		break;
	case GhostState::EATEN:
		move_eaten(SmartAlgo->get_move(EatenPoint, DefaultValues::GhostVelocity * 2 ));
		break;
	}
	return get_rect();
}

/**
* @brief render ghost
* @retval none
*/
void RedGhost::render()
{
	switch(state)
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
* @brief move in all states except eaten
* @note
* @param1 new move
* @retval
*/
void RedGhost::move_base(Move move)
{
	if (!(move.direction == Direction::NONE))
	{
		direction = move.direction;
		set_pos(move.pos);
	}
}

/**
* @brief move in eaten state
* @note
* @param1 new move
* @retval
*/
void RedGhost::move_eaten(Move move)
{
	move_base(move);

	if (SDL_PointInRect(&get_pos(), &EatenRect))
	{
		state = prev_state;
	}
}

/**
* @brief setting ghost state
* @note
* @param1 new state
* @retval
*/
void RedGhost::set_state(GhostState _state)
{	
	switch (_state)
	{
	case GhostState::FRIGHTENED:
		if (state == GhostState::FRIGHTENED)
		{
			StartFrTime = SDL_GetTicks();
		}
		if ( state != GhostState::EATEN)
		{
			StartFrTime = SDL_GetTicks();
			prev_state = state;
			state = _state;
		}
		break;
	case GhostState::EATEN:
		if (state == GhostState::FRIGHTENED)
			state = _state;
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

/**
* @brief returns ghost state
* @note
* @retval ghjost state
*/
GhostState RedGhost::get_state() const
{
	return state;
}

/**
* @brief returns ghost to a start point
* @note
* @retval
*/
void RedGhost::reset()
{
	set_pos(StartPoint);
	state = GhostState::SCATTER;
}