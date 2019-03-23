/**
  *************************************************************************************************************************
  * @file    MixEngine.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   MixEngine class is designed for sound control
  **************************************************************************************************************************
*/
#ifndef MIXENGINE_H
#define MIXENGINE_H
/*includes*/
#include<memory>
/*Predeclared  classes*/
class Music;
class Sound;

class MixEngine
{
public:
	/*Constructor*/
	MixEngine();
	/*Destructor*/
	~MixEngine();

	/**
	* @brief play music
	* @note
	* @param1 pointer to a music object
	* @retval
	*/
	void Play(std::shared_ptr<Music>);

	/**
	* @brief play sound
	* @note
	* @param1 pointer to a sound object
	* @retval
	*/
	void Play(std::shared_ptr<Sound>);

	/**
	* @brief Stop/resume sound playing
	* @note
	* @retval
	*/
	void StopResumeSound();

	/**
	* @brief Stop/resume music playing
	* @note
	* @retval
	*/
	void StopResumeMusic();
private:
	bool stopmusic;//true if music is stoped
	bool stopsound;//true if music is stoped
	std::shared_ptr<Music> _music;//pointer to a played music object
};

#endif