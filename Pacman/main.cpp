#include "main.h"
#include <filesystem>
#include <Windows.h>

int main(int argc, char* args[])
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
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