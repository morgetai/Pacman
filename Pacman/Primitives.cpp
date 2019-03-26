/**
  *************************************************************************************************************************
  * @file    Primitives.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Primitives are: Texture, Image, Text, Sprite, Music, Sound
  **************************************************************************************************************************
*/
/*includes*/
#include "Primitives.h"

/* ===============================================================================
					   ##### Texture #####
 ===============================================================================  */

 /**constructor*/
Texture::Texture():
	_texture(nullptr)
{
}

/*Destructor*/
Texture::~Texture()
{
}

/**
* @brief set texture color
* @note
* @param1 red
* @param2 greeen
* @param3 blue
* @retval
*/
void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(_texture.get(), red, green, blue);
}

/**
* @brief set blending
* @note
* @param1 blend mode
* @retval
*/
void Texture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(_texture.get(), blending);
}

/**
* @brief set alpha
* @note
* @param1 new alpha
* @retval
*/
void Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(_texture.get(), alpha);
}

/**
* @brief set position
* @note
* @param1 new position
* @retval
*/
void Texture::set_pos(SDL_Point p)
{
	_rect.x = p.x;
	_rect.y = p.y;
}

/**
* @brief set rectangle
* @note
* @param1 new rectangle
* @retval
*/
void Texture::set_rect(SDL_Rect in)
{
	_rect.w = in.w;
	_rect.h = in.h;
	_rect.x = in.x;
	_rect.y = in.y;
}

/**
* @brief get current rectangle
* @note
* @retval current rectangle
*/
SDL_Point Texture::get_pos()
{
	SDL_Point p;
	p.x = _rect.x;
	p.y = _rect.y;
	return p;
}


/* ===============================================================================
								 ##### Image #####
 ===============================================================================  */

 /**
 * @brief constructor
 * @param1 width
 * @param2 height
 * @param3 x position
 * @param4 y position
 * @param5 renderer pointer
 * @param6 path to image file
 */
Image::Image(int w, int h, int x, int y, std::shared_ptr<SDL_Renderer> r, std::string path):
	renderer(r),
	Texture()
{
	_rect.x = x;
	_rect.y = y;
	_rect.w = w;
	_rect.h = h;
	/*craete surface*/
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL) std::cerr << "Unable to load image! IMG_Load Error! " << path << " " << IMG_GetError() <<"\n";
	
	else
	{
		Texture::_width = surface->w;
		Texture::_height = surface->h;
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

		/*set new texture with deleter*/
		Texture::_texture.reset(SDL_CreateTextureFromSurface(renderer.get(), surface), [](SDL_Texture* texture)
		{
			SDL_DestroyTexture(texture);
		});

		if (Texture::_texture == nullptr)	std::cerr << "Unable to create texture! " << path << " " << SDL_GetError() << "\n";
		/*delete surface*/
		SDL_FreeSurface(surface);
	}
}

/**
* @brief constructor
* @param1 destination rectangle
* @param2 renderer pointer
* @param3 path to image file
*/
Image::Image(SDL_Rect rect, std::shared_ptr<SDL_Renderer> r, std::string path):
	Image(rect.w, rect.h, rect.x, rect.y, r, path)
{
	;
}

/*Destructor*/
Image::~Image()
{
}

/**
* @brief render pacman
* @note
* @retval
*/
void Image::render()
{
	SDL_RenderCopyEx(renderer.get(), Texture::_texture.get(), NULL, &_rect,NULL,NULL, SDL_FLIP_NONE);	
}


/* ===============================================================================
								 ##### Font #####
 ===============================================================================  */

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
Font::Font(int w, int h, int x, int y, int size, std::shared_ptr<SDL_Renderer> r, std::string path) :
	renderer(r),
	_ttf_size(size),
	Texture()
{
	_rect.x = x;
	_rect.y = y;
	_rect.w = w;
	_rect.h = h;
	_font.reset(TTF_OpenFont(path.c_str(), size), [](TTF_Font* f)
	{
		TTF_CloseFont(f);
	});
	if (_font == NULL) std::cerr << "Unable to load font! SDL_ttf Error! " << path << " " << TTF_GetError() << "\n";
	/*set color to black*/
	color.r = 0; color.g = 0; color.b = 0; color.a = 0;
}

/**
* @brief constructor
* @param1 x position
* @param2 y position
* @param3 text size
* @param4 renderer pointer
* @param5 path to ttf file
*/
Font::Font(int x, int y, int size, std::shared_ptr<SDL_Renderer> r, std::string path) :
	Font(-1, -1, x, y, size, r, path)
{}

/*Destructor*/
Font::~Font()
{
}

/**
* @brief set text color
* @note
* @param1 red
* @param2 greeen
* @param3 blue
* @retval
*/
void Font::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	color.r = red;
	color.g = green;
	color.b = blue;
}

/**
* @brief set new text
* @note by true size means to put draw text not to a pre-defined
* @note rectangle but use the size to draw it
* @param1 new text
* @param2 true by default
* @retval true if text was loaded
*/
bool Font::loadText(std::string Text, bool TrueSize)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(_font.get(), Text.c_str(),color);
	if (textSurface == NULL) std::cerr << "Unable to render text! SDL_ttf Error! " << Text << " " << TTF_GetError()<<"\n";
	else
	{
		/*set new texture with deleter*/
		_texture.reset(SDL_CreateTextureFromSurface(renderer.get(), textSurface), [](SDL_Texture* texture)
		{
			SDL_DestroyTexture(texture);
		});

		if (TrueSize)
		{
			_rect.w = textSurface->w; _rect.h = textSurface->h;
		}
		if (_texture == NULL) std::cerr << "Unable to render text! SDL Error! " << Text << " " << SDL_GetError() << "\n";
		SDL_FreeSurface(textSurface);
		return true;
	}
	return false;
}

/**
* @brief render text
* @note
* @retval
*/
void Font::render()
{
	SDL_RenderCopyEx(renderer.get(), Texture::_texture.get(), NULL, &_rect, NULL, NULL, SDL_FLIP_NONE);
}

/* ===============================================================================
								 ##### Sprite #####
 ===============================================================================  */

 /**
 * @brief constructor
 * @param1 number of images used in sorite
 * @param2 renderer pointer
 * @param3 path to sprite file
 * @param4 orientation
 */
Sprite::Sprite(int qty, std::shared_ptr<SDL_Renderer> r, std::string path, SpriteOrientation orientation) :
	renderer(r),
	Texture()
{
	sprites.resize(qty);
	/*load whole image*/
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL) std::cerr << "Unable to load image! IMG_Load Error! " << path << " " << IMG_GetError() << "\n";
	else
	{
		/*save real width and height*/
		Texture::_width = surface->w;
		Texture::_height = surface->h;
		/*set color*/
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
		/*save texture*/
		Texture::_texture.reset(SDL_CreateTextureFromSurface(renderer.get(), surface), [](SDL_Texture* texture)
		{
			SDL_DestroyTexture(texture);
		});

		if (!Texture::_texture)	std::cerr << "Unable to create texture! " << path << " " << SDL_GetError() << "\n";

		SDL_FreeSurface(surface);
	}

	/*split sprite into number of images*/
	if (orientation == SpriteOrientation::VERTICAL)
	{
		sprites[0].w = Texture::_width;
		sprites[0].h = (Texture::_height / qty);
		sprites[0].x = 0;
		sprites[0].y = 0;

		for (int i = 1; i < sprites.size(); ++i)
		{
			sprites[i].w = sprites[0].w;
			sprites[i].h = sprites[0].h;
			sprites[i].x = 0;
			sprites[i].y = sprites[i > 0 ? (i- 1): i].y + sprites[0].h;
		}
	}
	/*horizontal orientation*/
	else
	{
		sprites[0].w = Texture::_width / qty;
		sprites[0].h = Texture::_height;
		sprites[0].x = 0;
		sprites[0].y = 0;

		for (int i = 1; i < sprites.size(); ++i)
		{
			sprites[i].w = sprites[0].w;
			sprites[i].h = sprites[0].h;
			sprites[i].x = sprites[i > 0 ? (i - 1) : i].x + sprites[0].w;
			sprites[i].y = 0;
		}
	}
}

/**
* @brief render sprite
* @note
* @param1 number of image to be rendered
* @retval
*/
void Sprite::render(size_t sprite_num)
{
	SDL_RenderCopyEx(renderer.get(), Texture::_texture.get(), &sprites[sprite_num], &_rect, NULL, NULL, SDL_FLIP_NONE);
}

/* ===============================================================================
								 ##### Music #####
 ===============================================================================  */

 /**
 * @brief constructor
 * @param1 path to music file
 */
Music::Music(std::string path)
{
	/*set ptr and deleter*/
	music.reset(Mix_LoadMUS(path.c_str()), [](Mix_Music* mus)
	{
		Mix_FreeMusic(mus);
	});

	if (!music)
	{
		std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << "\n";
	}
}

/*Destructor*/
Music::~Music()
{
	;
}

/* ===============================================================================
								 ##### Sound #####
 ===============================================================================  */
 /**
 * @brief constructor
 * @param1 path to sound file
 */
Sound::Sound(std::string path)
{
	/*set ptr and deleter*/
	sound.reset(Mix_LoadWAV(path.c_str()), [](Mix_Chunk* chunk)
	{
		Mix_FreeChunk(chunk);
	});

	if (!sound)
	{
		std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << "\n";
	}
}

/*Destructor*/
Sound::~Sound()
{
	;
}