/**
  *************************************************************************************************************************
  * @file    Animation.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    13-March-2019
  * @brief   Animation class
  **************************************************************************************************************************
*/


#ifndef ANIMATION_H
#define ANIMATION_H

/*includes*/
#include<memory>
#include<SDL.h>
#include<string>

/*Predeclared  classes*/
class Sprite;
enum class SpriteOrientation;


class Animation
{
public:
	/**
	* @brief constructor
	* @param1,2 width and height 
	* @param3 number of images used in animation
	* @param4 orientation of images
	* @param5 renderer
	* @param6 path to image files
	*/
	Animation(int w, int h ,int qty, SpriteOrientation orientation, std::shared_ptr<SDL_Renderer> r, std::string path);
	/*Destructor*/
	~Animation();

	/**
	* @brief renders the animation
	* @note  
	* @retval none
	*/
	void render();

	/**
	* @brief setting a position of animation
	* @note
	* @retval none
	*/
	void setpos(SDL_Point);
private:
	const std::unique_ptr<Sprite> frames;//sprite image object
	size_t current_frame;//current rendered image from sprite
	const size_t frames_qty;//number of images in sprite
};



#endif 
