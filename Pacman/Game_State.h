/**
  *************************************************************************************************************************
  * @file    Game_state.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    14-March-2019
  * @brief   Game state class. Part of state pattern
  **************************************************************************************************************************
*/
#ifndef GAME_MENU_STATE_H
#define GAME_MENU_STATE_H
/*includes*/
#include "Engine_state.h"
#include"SDL.h"
#include<vector>
#include<memory>
#include<array>

/*Predeclared  classes*/
class Engine;
class InteractiveObjects;
class Map;
class MovableObjects;
class Pacman;
class PacmanKeyboard;
class Event_listener;
class Image;
class Score;
class GhostEngine;
class InteractiveObjEngine;
class Font;
class Sound;
class MixEngine;

class GameState :public EngineState
{
public:
	/**
	* @brief constructor
	* @param1 Engine pointer
	* @param2 MixEngine pointer
	* @param3 renderer pointer
	* @param4 event listener pointer
	*/
	GameState(Engine*, MixEngine*,std::shared_ptr<SDL_Renderer>, std::shared_ptr<Event_listener>);
	/*Destructor*/
	virtual ~GameState();

	/**
	* @brief runs the state
	* @note 
	* @param1 Engine pointer
	* @retval
	*/
	virtual void run(Engine*);

	/**
	* @brief closes the state
	* @note
	* @param1 Engine pointer
	* @retval
	*/
	virtual void close(Engine*);

	/**
	* @brief pause state
	* @note
	* @retval
	*/
	void GamePause();

private:
	/**
	* @brief render
	* @note
	* @retval
	*/
	void render();

	/**
	* @brief play state behavior
	* @note
	* @retval
	*/
	void StatePlay();

	/**
	* @brief delay before game is started
	* @note
	* @retval
	*/
	void StateDelay();

	/**
	* @brief reset the game
	* @note
	* @retval
	*/
	void StateReset();

	/**
	* @brief game over state behavior
	* @note
	* @retval
	*/
	void StateOver();

	/**
	* @brief pause the game
	* @note
	* @retval
	*/
	void StatePause();

	/**
	* @brief win state behavior
	* @note
	* @retval
	*/
	void StateWin();

	std::shared_ptr<Map> map;//map pointer
	std::unique_ptr<InteractiveObjEngine> IntObjEngine;//controls dots and fruits
	std::shared_ptr<Pacman> pacman;
	std::unique_ptr<Score> score;
	std::shared_ptr<PacmanKeyboard> gamekeyboard;
	std::unique_ptr<GhostEngine> ghostengine;//control all ghosts
	/*states inside game state*/
	enum class GameStates {
		GAME_PLAY,
		GAME_STOP,
		GAME_PAUSE,
		GAME_OVER,
		GAME_WIN,
		GAME_RESET,
		GAME_START_DELAY,
		GAME_NEW_LEVEL 
	};
	GameStates game_state;
	Uint32 StartMsecond;
	std::unique_ptr<Font> text;//shows "win", "game over", "pause" texts
	Engine* engine;
	MixEngine* mixengine;
	std::array<std::shared_ptr<Sound>, 3> sounds;
	SDL_Point GameOvetTextPos;
	SDL_Point WinTextPos;
	SDL_Point TextPos;//other text position

};

#endif
