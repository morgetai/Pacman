#ifndef PACMAN_MOVE_ALGO_H
#define PACMAN_MOVE_ALGO_H

#include"MoveAlgorithmBase.h"
#include"DefaultValues.h"


class PacmanMoveAlgorithm:public MoveAlgorithmBase
{
public:
	//
	//PacmanMoveAlgorithm();
	virtual ~PacmanMoveAlgorithm();

	//
	virtual Move get_move(SDL_Point, int vel = DefaultValues::GhostVelocity);
	void keyboard_move(Direction);

private:
	Move move;
};

#endif
