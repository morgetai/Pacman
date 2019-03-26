/**
  *************************************************************************************************************************
  * @file    Animation.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    13-March-2019
  * @brief   Animation class
  **************************************************************************************************************************
*/

/*includes*/
#include"Animation.h"
#include"Primitives.h"

/**
* @brief constructor
* @param1,2 width and height
* @param3 number of images used in animation
* @param4 orientation of images
* @param5 renderer
* @param6 path to image files
*/
Animation::Animation(int w, int h,int qty, SpriteOrientation orientation, std::shared_ptr<SDL_Renderer> r, std::string path) :
	frames(std::make_unique<Sprite>(qty,r, path, orientation)),//sprite image object
	current_frame(0), // current rendered image from sprite
	frames_qty(qty) //number of images in sprite
{
	SDL_Rect rec;
	rec.w = w;
	rec.h = h;
	frames->set_rect(rec);
}

/*Destructor*/
Animation::~Animation()
{
	;
}


/**
* @brief renders the animation
* @note
* @retval none
*/
void Animation::render()
{
	/*8 times rendering current image*/
	frames->render(current_frame++ / 8);
	/*if had reached number of images set current_frame to 0*/
	if (current_frame / 8 >= frames_qty)
		current_frame = 0;
}

/**
* @brief setting a position of animation
* @note
* @retval none
*/
void Animation::setpos(SDL_Point p)
{
	frames->set_pos(p);
}