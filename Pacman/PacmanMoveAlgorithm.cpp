#include "PacmanMoveAlgorithm.h"
#include"Help.h"

/*PacmanMoveAlgorithm::PacmanMoveAlgorithm(int i) :
	velocity(i)
{
	//rect.h = 0; rect.w = 0; rect.x = 0; rect.y = 0;
}*/
PacmanMoveAlgorithm::~PacmanMoveAlgorithm()
{
	;
}


void PacmanMoveAlgorithm::keyboard_move(Direction pacmove)
{
	//rect.x = 0; rect.y = 0;
	switch (pacmove)
	{
	case Direction::UP:
		//rect.y -= velocity;
		move.direction = Direction::UP;
		break;
	case Direction::DOWN:
		//rect.y += velocity;
		move.direction = Direction::DOWN;
		break;
	case Direction::LEFT:
		//rect.x -= velocity;
		move.direction = Direction::LEFT;
		break;
	case Direction::RIGHT:
		//rect.x += velocity;
		move.direction = Direction::RIGHT;
		break;
	}
}


Move PacmanMoveAlgorithm::get_move(SDL_Point, int vel)
{
	/*Move ret;
	ret.first = rect;*/
	return move;
}