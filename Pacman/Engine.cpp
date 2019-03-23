/**
  *************************************************************************************************************************
  * @file    Engine.cpp
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    14-March-2019
  * @brief   Main program engine
  **************************************************************************************************************************
*/
/*includes*/
#include"Engine.h"
#include"Engine_state.h"
#include"Event_listener.h"
#include"Actuator_constrol.h"
#include"Main_Menu_State.h"
#include"Game_State.h"
#include"Button.h"
#include"GlobalKeys.h"
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include"Menu_Option.h"
#include"MixEngine.h"
#include"OptionMenuState.h"
#include"CheckBox.h"
#include"Primitives.h"
#include"DefaultValues.h"

/*Constructor*/
Engine::Engine() :
	EventListener(std::make_shared<Event_listener>()),
	ActuatorControl(std::make_shared<Actuator_control>(EventListener)),
	current_state(EngineStateType::STATE_NOT_INITIALIZED),
	mixengine(std::make_unique<MixEngine>()),
	menumusic(std::make_shared<Music>(DefaultValues::MenuMusic)),
	gamemusic(std::make_shared<Music>(DefaultValues::GameMusic))
{
	current_state = EngineStateType::STATE_INITIALIZED;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL could not initialize! SDL Error " << SDL_GetError();
		current_state = EngineStateType::STATE_NOT_INITIALIZED;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) std::cerr << "Linear texture filtering not enabled!";
		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError();
			current_state = EngineStateType::STATE_NOT_INITIALIZED;
		}
		//Initializing TTF
		if (TTF_Init() == -1)
		{
			std::cerr << "SDL_TTF could not initialize! SDL_image Error: " << IMG_GetError();
			current_state = EngineStateType::STATE_NOT_INITIALIZED;
		}
	}
	//creating window
	window = std::make_unique<Window>("Pacman");
	//creating global keys (ESC, backspace, close)
	globalkeys = std::make_shared<GlobalKeys>(EventListener, this);
	//creating states
	states[0] = std::make_unique<MainMenuState>(ActuatorControl, this, window->get_renderer());
	states[1] = std::make_unique<OptionMenuState>(ActuatorControl, this, mixengine.get(), window->get_renderer());
	states[2] = std::make_unique<GameState>(this, mixengine.get(),window->get_renderer(), EventListener);
	//setting buttons sprite
	Button::set_button_sprite(window->get_renderer(), DefaultValues::ButtonSprite);
	//setting checkbox sprite
	CheckBox::set_checkbox_sprite(window->get_renderer(), DefaultValues::CheckboxSprite);
	//attach actuator control and buttons
	EventListener->attach(std::static_pointer_cast<Observer>(ActuatorControl));
	EventListener->attach(std::static_pointer_cast<Observer>(globalkeys));
}

/*Destructor*/
Engine::~Engine()
{
	IMG_Quit();
	SDL_Quit();
}

/**
* @brief runs the program
* @note run in main()
* @retval
*/
void Engine::run()
{
	/*if initialization failed*/
	if (current_state == EngineStateType::STATE_NOT_INITIALIZED)
		return;
	else
		current_state = EngineStateType::STATE_MAIN;
	/*while running*/
	while (current_state != EngineStateType::STATE_CLOSE)
	{
		EventListener->listen_events();
		/*clear the window screen*/
		window->clear_window();
		/*if some state was closed*/
		if (Close)
		{
			switch (prev_state)
			{
			case EngineStateType::STATE_MAIN:
				states[0]->close(this);
				break;
			case EngineStateType::STATE_OPTIONS:
				states[1]->close(this);
				break;
			case EngineStateType::STATE_GAME:
				states[2]->close(this);
				break;
			}
			Close = false;
		}
		else
		{
			switch (current_state)
			{
			case EngineStateType::STATE_MAIN:
				states[0]->run(this);
				mixengine->Play(menumusic);
				break;
			case EngineStateType::STATE_OPTIONS:
				states[1]->run(this);
				mixengine->Play(menumusic);
				break;
			case EngineStateType::STATE_GAME:
				states[2]->run(this);
				mixengine->Play(gamemusic);
				break;
			}
		}
		/*update the window screen*/
		window->update_window();
	}
}


/**
* @brief setting state
* @param1 new state
* @note
* @retval
*/
void Engine::change_state(EngineStateType state)
{
	switch (state)
	{
	case EngineStateType::STATE_CLOSE:
		current_state = EngineStateType::STATE_CLOSE;
		break;
	default:
		if (current_state != state)
		{
			prev_state = current_state;
			current_state = state;
			Close = true;
		}
	}
}
