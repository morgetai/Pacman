/**
  *************************************************************************************************************************
  * @file    MixEngine.cpp
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   MixEngine class is designed for sound control
  **************************************************************************************************************************
*/
/*includes*/
#include "MixEngine.h"
#include"Primitives.h"

/*Constructor*/
MixEngine::MixEngine()
{
	/*Open mixer*/
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) < 0)
	{
		std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << "\n";
	}
}

/*Destructor*/
MixEngine::~MixEngine()
{

}

/**
* @brief play music
* @note
* @param1 pointer to a music object
* @retval
*/
void MixEngine::Play(std::shared_ptr<Music> m)
{
	if (_music != m)
	{
		_music = m;
		if (!stopmusic)
			Mix_PlayMusic(_music->music.get(), -1);
	}
}

/**
* @brief play sound
* @note
* @param1 pointer to a sound object
* @retval
*/
void MixEngine::Play(std::shared_ptr<Sound> s)
{
	if (!stopsound)
	{
		Mix_PlayChannel(-1, s->sound.get(), 0);
	}
}

/**
* @brief Stop/resume sound playing
* @note
* @retval
*/
void MixEngine::StopResumeSound()
{
	if (!stopsound)
	{
		stopsound = true;
	}
	else
	{
		stopsound = false;
	}
}

/**
* @brief Stop/resume music playing
* @note
* @retval
*/
void MixEngine::StopResumeMusic()
{
	if (Mix_PlayingMusic() == 1)
	{
		Mix_HaltMusic();
		stopmusic = true;
	}
	else
	{
		Mix_PlayMusic(_music->music.get(), -1);
		stopmusic = false;
	}
}