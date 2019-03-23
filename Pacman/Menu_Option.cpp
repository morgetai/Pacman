/**
  *************************************************************************************************************************
  * @file    Menu_Option.cpp
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Option menu class
  **************************************************************************************************************************
*/
/*includes*/
#include"Menu_Option.h"
#include"CheckBox.h"
#include"Actuator.h"
#include"Command.h"
#include"Primitives.h"
#include"MixEngine.h"
#include"Button.h"
#include"Engine.h"
#include"DefaultValues.h"

/**
* @brief constructor
* @param1 path to image file
* @param2 actuator control pointer
* @param3 engine pointer
* @param3 MixEngine pointer
* @param4 Renderer pointer
*/
Menu_Option::Menu_Option(std::string img_path, std::shared_ptr<Actuator_control> _act_control,
	Engine* eng, MixEngine* mixengine,
	std::shared_ptr<SDL_Renderer> renderer):
	img(std::make_unique<Image>(
		300, //w
		200, //h
		250, //x
		10,  //y
		renderer, img_path)),
	SoundText(std::make_unique<Font>(
		330,//x
		305,//y
		16,//text height
		renderer, DefaultValues::Font)),
	MusicText(std::make_unique<Font>(
		330,//x
		355,//y
		16,//text height
		renderer, DefaultValues::Font)),
	Menu_Base(_act_control)
{
	SDL_Rect box1; box1.x = 430; box1.y = 300; box1.w = 30; box1.h = 30;
	SDL_Rect box2; box2.x = 430; box2.y = 350; box2.w = 30; box2.h = 30;

	/*actuators*/
	actuators.emplace_back(new CheckBox(
		box1,
		std::move(std::unique_ptr<Command_Base>(new Command <MixEngine>(mixengine,&MixEngine::StopResumeSound)))));

	actuators.emplace_back(new CheckBox(
		box2,
		std::move(std::unique_ptr<Command_Base>(new Command <MixEngine>(mixengine, &MixEngine::StopResumeMusic)))));

	actuators.emplace_back(new Button(
		150, //w
		50, //h
		320, //x
		420, //y
		DefaultValues::Font, "BACK", renderer,
		std::move(std::unique_ptr<Command_Base>
		(new Command<Engine, EngineStateType>(eng, &Engine::change_state, EngineStateType::STATE_MAIN)))));

	/*text*/
	SoundText->setColor(255, 215, 05);
	MusicText->setColor(255, 215, 0);
	SoundText->loadText("Sound"); 
	MusicText->loadText("Music");

}

/*Destructor*/
Menu_Option::~Menu_Option()
{
}

/**
* @brief render a menu
* @note
* @retval
*/
void Menu_Option::render()
{
	SoundText->render();
	MusicText->render();
	img->render();
	/*render actuators*/
	std::for_each(actuators.begin(), actuators.end(),[]
	(std::shared_ptr<Actuator>& act) 
	{act->render(); });
}