/**
  *************************************************************************************************************************
  * @file    Game_state.cpp
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    14-March-2019
  * @brief   Game state class. Part of state pattern
  **************************************************************************************************************************
*/
/*includes*/
#include "Game_State.h"
#include"Engine.h"
#include "File_Reader.h"
#include "Map.h"
#include "PacDots.h"
#include"Pacman.h"
#include"PacmanKeyboard.h"
#include"Observer.h"
#include"MovableObjects.h"
#include"Animation.h"
#include"PacmanMoveAlgorithm.h"
#include"Primitives.h"
#include"Dot.h"
#include"Score.h"
#include"RedGhost.h"
#include"SmartAlgoMove.h"
#include"DummyAlgoMove.h"
#include"RandomAlgoMove.h"
#include"GhostEngine.h"
#include"InteractiveObjEngine.h"
#include"PacmanLife.h"
#include"MixEngine.h"
#include"DefaultValues.h"

/**
* @brief constructor
* @param1 Engine pointer
* @param2 MixEngine pointer
* @param3 renderer pointer
* @param4 event listener pointer
*/
GameState::GameState(Engine* en, MixEngine* mix, std::shared_ptr<SDL_Renderer> r, std::shared_ptr<Event_listener> ev) :
	map(nullptr),
	pacman(nullptr),
	gamekeyboard(nullptr),
	engine(en),
	mixengine(mix),
	text(std::make_unique<Font>(
		DefaultValues::GameTextPosX, //x of text rect
		DefaultValues::GameTextPosY, //y of text rect
		DefaultValues::GameTextHeight, //text height
		r, DefaultValues::Font))
{

	/*reading the map file*/
	File_Reader MapRead(DefaultValues::MapShiftX, DefaultValues::MapShiftY, DefaultValues::MapPath);
	/*creating map object*/
	map = std::make_shared<Map>(MapRead.get_tiles(), r);
	/*creating pacman*/
	SDL_Rect PacmanRect; PacmanRect.x = DefaultValues::PacmanStartX; PacmanRect.y = DefaultValues::PacmanStartY;
	PacmanRect.w = DefaultValues::TileWidth; PacmanRect.h = DefaultValues::TileHeight;
	pacman = (std::make_unique<Pacman>(PacmanRect, r, map, MapRead.get_maze(),
		DefaultValues::PacmanNormalAnimationPath,
		DefaultValues::PacmanDeadAnimationPath));
	/**/
	IntObjEngine = std::make_unique<InteractiveObjEngine>(MapRead.get_pacdots(), r);
	/**/
	ghostengine = std::make_unique<GhostEngine>(std::static_pointer_cast<MovableObjects>(pacman),
		MapRead.get_maze(), map, r);
	/*keyboard*/
	gamekeyboard =  std::make_shared<PacmanKeyboard>(ev,pacman.get(),this);
	/*score*/
	score = std::make_unique<Score>(
	DefaultValues::ScorePosX, //x
	DefaultValues::ScorePosY, //y
	r, //renderer
	DefaultValues::Font);
	/*sounds*/
	sounds[0] = std::make_shared<Sound>(DefaultValues::DeathSound);
	sounds[1] = std::make_shared<Sound>(DefaultValues::WinSound);
	sounds[2] = std::make_shared<Sound>(DefaultValues::GameOverSound);
	/*text*/
	text->setColor(255, 215, 0);
	WinTextPos = GameOvetTextPos = TextPos = text->get_pos();
	WinTextPos.x += 10;
	GameOvetTextPos.x -= 18;

}
/*Destructor*/
GameState::~GameState()
{}

/**
* @brief runs the state
* @note
* @param1 Engine pointer
* @retval
*/
void GameState::run(Engine* engine)
{
	/*if state was activated*/
	if (!active)
	{
		active = true;
		game_state = GameStates::GAME_START_DELAY;
		/*save start time*/
		StartMsecond = SDL_GetTicks();
		/*attach game keyboard*/
		engine->EventListener->attach(std::static_pointer_cast<Observer>(gamekeyboard));
	}

	switch (game_state)
	{
	case GameStates::GAME_PLAY:
		StatePlay();
		break;
	case GameStates::GAME_RESET:
		StateReset();
		break;
	case GameStates::GAME_PAUSE:
		StatePause();
		break;
	case GameStates::GAME_OVER:
		StateOver();
		break;
	case GameStates::GAME_START_DELAY:
		StateDelay();
		break;
	case GameStates::GAME_WIN:
		StateWin();
		break;
	default :
		;
	}
}

/**
* @brief closes the state
* @note
* @param1 Engine pointer
* @retval
*/
void GameState::close(Engine* engine)
{
	/**/
	active = false;
	pacman->reset();
	pacman->Life->reset();
	ghostengine->Reset();
	IntObjEngine->reset();
	score->reset();
	/*detach game keyboard*/
	engine->EventListener->detach(std::static_pointer_cast<Observer>(gamekeyboard));
	/**/
	chagestate(engine, EngineStateType::STATE_MAIN);
}

/**
* @brief render
* @note
* @retval
*/
void GameState::render()
{
	pacman->render();
	map->render();
	IntObjEngine->render();
	score->render();
	ghostengine->render();
}


/**
* @brief play state behavior
* @note
* @retval
*/
void GameState::StatePlay()
{
	/*collision with dots and fruits*/
	switch (IntObjEngine->CheckCollision(pacman->move()))
	{
	case ObjectCollisonType::DOT_EATEN:
		(*score) += ObjectCollisonType::DOT_EATEN;
		break;
	case ObjectCollisonType::BIG_DOT_EATEN:
		(*score) += ObjectCollisonType::BIG_DOT_EATEN;
		ghostengine->SetFrightened();
		break;
	case ObjectCollisonType::FRUIT_EATEN:
		(*score) += ObjectCollisonType::FRUIT_EATEN;
		break;
	case ObjectCollisonType::ALL_DOTS_EATEN:
		game_state = GameStates::GAME_WIN;
		/*save win time for the delay count*/
		StartMsecond = SDL_GetTicks();
		/*play win sound*/
		mixengine->Play(sounds[1]);
		break;
	}

	/*collision with ghosts*/
	switch (ghostengine->check_ghost_collision(pacman->get_rect()))
	{
	case GHOST_COLLISION::GHOST_EATEN:
		(*score) += GHOST_COLLISION::GHOST_EATEN;
		break;
	case GHOST_COLLISION::MINUS_PACMAN_LIFE:
		;
		/*minus pacman life*/
		if (!--(pacman->Life->lives()))//true if pacman life is less then "0"
		{
			game_state = GameStates::GAME_OVER;
			mixengine->Play(sounds[2]);
		}
		else
		{
			/*reset*/
			game_state = GameStates::GAME_RESET;
			mixengine->Play(sounds[0]);
			ghostengine->Pause();
		}
		pacman->set_state(PacmanState::STATE_DEAD);
		StartMsecond = SDL_GetTicks();
		goto Render;
	}

	/*run engines*/
	ghostengine->run();
	IntObjEngine->run();
	/**/
	Render:	render();
}

/**
* @brief delay before game is started
* @note 
* @retval
*/
void GameState::StateDelay()
{
	/*count delay*/
	if (TimeElapsed(3000, StartMsecond))
	{
		game_state = GameStates::GAME_PLAY;
	}
	/*Render "Ready" text*/
	text->loadText("Ready");
	text->render();
	/**/
	render();
}

void GameState::StateReset()
{
	if (TimeElapsed(1450, StartMsecond))
	{
		StartMsecond = SDL_GetTicks();
		game_state = GameStates::GAME_START_DELAY;
		pacman->reset();
		ghostengine->MoveToStartPos();
	}
	render();
}

/**
* @brief reset the game
* @note
* @retval
*/
void GameState::StatePause()
{
	text->loadText("Pause");
	text->render();
	StartMsecond = SDL_GetTicks();
	render();
}

/**
* @brief game over state behavior
* @note
* @retval
*/
void GameState::StateOver()
{
	if (!TimeElapsed(2000, StartMsecond))
	{
		text->set_pos(GameOvetTextPos);
		/*render "game over" text*/
		text->loadText("Game Over");
		text->render();
		/**/
		render();
	}
	else
	{
		text->set_pos(TextPos);
		close(engine);
	}
}

/**
* @brief pause the game
* @note
* @retval
*/
void GameState::GamePause()
{
	switch (game_state)
	{
	case GameStates::GAME_PAUSE:
		game_state = GameStates::GAME_PLAY;
		break;
	case GameStates::GAME_PLAY:
		game_state = GameStates::GAME_PAUSE;
		ghostengine->Pause();
		break;
	case GameStates::GAME_START_DELAY:
		game_state = GameStates::GAME_PAUSE;
		ghostengine->Pause();
		break;
	}
}

/**
* @brief win state behavior
* @note
* @retval
*/
void GameState::StateWin()
{
	if (!TimeElapsed(2000, StartMsecond))
	{
		text->set_pos(WinTextPos);
		/*render "WIN" text*/
		text->loadText("WIN");
		text->render();
		/**/
		render();
	}
	else
	{
		text->set_pos(TextPos);
		pacman->reset();
		ghostengine->Reset();
		IntObjEngine->reset();
		render();
		game_state = GameStates::GAME_START_DELAY;
	}
}