/**
  *************************************************************************************************************************
  * @file    Primitives.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Primitives are: Texture, Image, Text, Sprite, Music, Sound
  **************************************************************************************************************************
*/
#ifndef PRIMITEVES_H
#define PRIMITIVES_H
/*includes*/
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>
#include<vector>
#include<SDL_mixer.h>
#include<functional>


class Texture
{
public:
	/**constructor*/
	Texture();
	/*Destructor*/
	virtual ~Texture();

	/**
	* @brief set texture color
	* @note
	* @param1 red
	* @param2 greeen 
	* @param3 blue
	* @retval
	*/
	virtual void setColor(Uint8 , Uint8 , Uint8 );

	/**
	* @brief set blending
	* @note
	* @param1 blend mode
	* @retval
	*/
	void setBlendMode(SDL_BlendMode blending);

	/**
	* @brief set alpha
	* @note
	* @param1 new alpha
	* @retval
	*/
	void setAlpha(Uint8 alpha);

	/**
	* @brief set position
	* @note
	* @param1 new position
	* @retval
	*/
	void set_pos(SDL_Point);

	/**
	* @brief set rectangle
	* @note
	* @param1 new rectangle
	* @retval
	*/
	void set_rect(SDL_Rect);

	/**
	* @brief get current rectangle
	* @note
	* @retval current rectangle
	*/
	SDL_Point get_pos();
 
protected:
	std::shared_ptr<SDL_Texture> _texture;//hardware texture pointer
	SDL_Rect _rect;//destination
	int _width; //real width
	int _height; //real height
};


class Image: public Texture
{
public:
	/**
	* @brief constructor
	* @param1 width
	* @param2 height
	* @param3 x position
	* @param4 y position
	* @param5 renderer pointer
	* @param6 path to image file
	*/
	Image(int,int,int,int,std::shared_ptr<SDL_Renderer>,std::string);

	/**
	* @brief constructor
	* @param1 destination rectangle
	* @param2 renderer pointer
	* @param3 path to image file
	*/
	Image(SDL_Rect, std::shared_ptr<SDL_Renderer>, std::string);
	/*Destructor*/
	virtual ~Image();

	/**
	* @brief render pacman
	* @note
	* @retval
	*/
	void render();
protected:
	std::shared_ptr<SDL_Renderer> renderer;//renderer pointer
};



class Font:public Texture
{
public:
	/**
	* @brief constructor
	* @param1 width
	* @param2 height
	* @param3 x position
	* @param4 y position
	* @param5 text size
	* @param6 renderer pointer
	* @param7 path to ttf file
	*/
	Font(int, int, int, int, int, std::shared_ptr<SDL_Renderer> , std::string);

	/**
	* @brief constructor
	* @param1 x position
	* @param2 y position
	* @param3 text size
	* @param4 renderer pointer
	* @param5 path to ttf file
	*/
	Font(int, int , int, std::shared_ptr<SDL_Renderer>, std::string);
	/*Destructor*/
	virtual ~Font();

	/**
	* @brief set text color
	* @note
	* @param1 red
	* @param2 greeen
	* @param3 blue
	* @retval
	*/
	void setColor(Uint8 , Uint8 , Uint8 ) override;

	/**
	* @brief set new text
	* @note by true size means to put draw text not to a pre-defined 
	* @note rectangle but use the size to draw it  
	* @param1 new text 
	* @param2 true by default
	* @retval true if text was loaded
	*/
	bool loadText(std::string Text,bool TrueSize = true);

	/**
	* @brief render text
	* @note
	* @retval
	*/
	void render();
private:
	std::shared_ptr<SDL_Renderer> renderer;
	std::shared_ptr<TTF_Font> _font;//ttf object pointer
	SDL_Colour color;//text color
	int _ttf_size;//text size
};

/*Sprite orientation*/
enum class SpriteOrientation
{
	HORIZONTAL,
	VERTICAL
};


class Sprite : public Texture
{
public:
	/**
	* @brief constructor
	* @param1 number of images used in sorite
	* @param2 renderer pointer
	* @param3 path to sprite file
	* @param4 orientation
	*/
	Sprite(int , std::shared_ptr<SDL_Renderer> ,
		std::string , SpriteOrientation orientation = SpriteOrientation::VERTICAL);
	/*Destructor*/
	virtual ~Sprite() { ; };

	/**
	* @brief render sprite
	* @note
	* @param1 number of image to be rendered
	* @retval
	*/
	void render(size_t sprite_num);
private:
	std::shared_ptr<SDL_Renderer> renderer;
	std::vector<SDL_Rect> sprites;//rectangle of every image readed from sprite file
};

/*Predeclared  classes*/
class MixEngine;


class Music
{
	friend class MixEngine;
public:
	/**
	* @brief constructor
	* @param1 path to music file
	*/
	Music(std::string);
	/*Destructor*/
	~Music();
private:
	std::shared_ptr<Mix_Music> music;
};


class Sound
{
	friend class MixEngine;
public:
	/**
	* @brief constructor
	* @param1 path to sound file
	*/
	Sound(std::string);
	/*Destructor*/
	~Sound();
private:
	std::shared_ptr<Mix_Chunk> sound;
};

#endif
