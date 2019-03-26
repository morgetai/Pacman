/**
  *************************************************************************************************************************
  * @file    Score.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    17-March-2019
  * @brief   Game score
  **************************************************************************************************************************
*/
/*includes*/
#include"Score.h"
#include"MovableObjects.h"
#include"InteractiveObjEngine.h"
#include"Primitives.h"
#include"GhostEngine.h"
#include"Help.h"
#include"DefaultValues.h"

/**
* @brief constructor
* @param1 x position
* @param2 y position
* @param3 renderer pointer
* @param4 path to ttf file
*/
Score::Score(int x, int y, std::shared_ptr<SDL_Renderer> renderer, std::string font_path):
score(0),
ghost_multiplier(1),
						  
text(std::make_unique<Font>(
	x, y, 
	18, // text height
	renderer, font_path)),
score_text(std::make_unique<Font>(
	50,//w
	30,//h
	x,y+30,
	14,// text height
	renderer, font_path))

{
	text->setColor(255, 215, 0);
	score_text->setColor(255, 255, 255);
	text->loadText("Score");
	score_text->loadText("00000");
}

/**
* @brief render score
* @retval none
*/
void Score::render()
{
	text->render();
	score_text->render();
}

/**
* @brief increment score with dot or fruit
* @note
* @param1 ObjectCollisonType
* @retval score
*/
Score& Score::operator+=(ObjectCollisonType obj)
{
	switch (obj)
	{
	case ObjectCollisonType::DOT_EATEN:
		score += DefaultValues::DotScore;
		score_text->loadText(std::to_string(score), true);
		break;
	case ObjectCollisonType::BIG_DOT_EATEN:
		score += DefaultValues::BigDotScore;
		score_text->loadText(std::to_string(score), true);
		ghost_multiplier = 1;
		break;
	case ObjectCollisonType::FRUIT_EATEN:
	{
		int scores[3] = { 100,200,300 };
		Rand_int rand(0, 2);
		score += scores[rand()];
		score_text->loadText(std::to_string(score), true);
		break;
	}
	}
	return *this;
}

/**
* @brief increment score with ghost
* @note
* @param1 GHOST_COLLISION
* @retval score
*/
Score& Score::operator+=(GHOST_COLLISION)
{
	score += DefaultValues::GhostScore * ghost_multiplier++;
	score_text->loadText(std::to_string(score),true);
	return *this;
}

/**
* @brief reset
* @note set score to zero
* @retval
*/
void Score::reset()
{
	score = 0;
	score_text->loadText("00000");
}