#include "main.h"
#include <filesystem>

int main(int argc, char* args[])
{
	//std::filesystem::path p("audio/music/menu.ogg");
	//std::cout << exists(p) << std::endl;
	{
		Engine engine;
		engine.run();
	}
	TTF_Quit();//close TTF engine
	Mix_Quit();//close Mix engine
	return 0;
}