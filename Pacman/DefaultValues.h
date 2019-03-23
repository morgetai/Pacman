#pragma once
#include<string>

namespace DefaultValues
{
	/*Dots*/
	const int DotWeight = 5;
	const int DotHeight = 5;
	const int BigDotWeight = 10;
	const int BigDotHeight = 10;
	const int DotScore = 10;
	const int BigDotScore = 50;
	const std::string DotImage("images/dot.png");
	/*Ghosts*/
	const int GhostScore = 400;
	const int GhostVelocity = 1;
	const std::string GhostDeadImage("GhostImg/Dead_UP.png GhostImg/Dead_DOWN.png \
GhostImg/Dead_LEFT.png GhostImg/Dead_RIGHT.png");
	const std::string GhostFrightenedImage("GhostImg/Frightened.png");
	const std::string GhostFrightenedEndImage("GhostImg/FrightenedEnd.png");
	const std::string RedGhostAliveAnim("GhostImg/Red/RedAlive_UP.png GhostImg/Red/RedAlive_DOWN.png \
GhostImg/Red/RedAlive_LEFT.png GhostImg/Red/RedAlive_RIGHT.png");
	const std::string PinkGhostAliveAnim("GhostImg/Pink/PinkAlive_UP.png GhostImg/Pink/PinkAlive_DOWN.png \
GhostImg/Pink/PinkAlive_LEFT.png GhostImg/Pink/PinkAlive_RIGHT.png");
	const std::string BlueGhostAliveAnim("GhostImg/Blue/BlueAlive_UP.png GhostImg/Blue/BlueAlive_DOWN.png \
GhostImg/Blue/BlueAlive_LEFT.png GhostImg/Blue/BlueAlive_RIGHT.png");
	const std::string YellowGhostAliveAnim("GhostImg/Yellow/YellowAlive_UP.png GhostImg/Yellow/YellowAlive_DOWN.png \
GhostImg/Yellow/YellowAlive_LEFT.png GhostImg/Yellow/YellowAlive_RIGHT.png");
	const int RedGhostStartTile(407);
	const int RedGhostScatterTile(54);
	const int RedGhostEatenTile(407);
	const int PinkGhostStartTile(406);
	const int PinkGhostScatterTile(30);
	const int PinkGhostLeaveHouseTile(323);
	const int BlueGhostStartTile(405);
	const int BlueGhostScatterTile(838);
	const int BlueGhostLeaveHouseTile(321);
	const int YellowGhostStartTile(404);
	const int YellowGhostScatterTile(813);
	const int YellowGhostLeaveHouseTile(321);
	/*Tiles*/
	const int TileWidth = 20;
	const int TileHeight = 19;
	/*Music*/
	const std::string MenuMusic("audio/music/menu.ogg");
	const std::string GameMusic("audio/music/game.ogg");
	/*Sounds*/
	const std::string DeathSound("audio/sounds/death.wav");
	const std::string WinSound("audio/sounds/win.wav");
	const std::string GameOverSound("audio/sounds/gameOver.wav");
	/*Button sprite*/
	const std::string ButtonSprite("images/button.png");
	/*Checkbox sprite*/
	const std::string CheckboxSprite("images/checkbox.png");
	/*Map*/
	const int MapElementTypes = 40;//number of different kinds of tiles 
	const int MapWidthInTiles = 28;
	const int MapHeightInTiles = 31;
	const int MapWidthInPixels = MapWidthInTiles * TileWidth;
	const int MapHeightInPixels = MapHeightInTiles * TileHeight;
	const int MapShiftX = 120;
	const int MapShiftY = 5;
	const int MazeCorridor = -2;//Don't change
	const int MazeWall = -1;//Don't change
	const std::string MapPath("map/map.txt");
	const std::string Tile20x20Path("map/20x20_01.png");
	const std::string Tile20x40Path("map/20x40_01.png");
	const std::string Tile40x20Path("map/40x20_01.png");
	const std::string Tile40x40Path("map/40x40_01.png");
	/*Pacman*/
	const int PacmanStartX = 390;
	const int PacmanStartY = 442;
	const int PacmanVelocity = 2;
	const std::string PacmanNormalAnimationPath("PacmanImg/anim_U.png \
PacmanImg/anim_D.png PacmanImg/anim_L.png PacmanImg/anim_R.png");
	const std::string PacmanDeadAnimationPath("PacmanImg/death-anim_b.png");
	const std::string PacLifeImg("PacmanImg/PacLife.png");
	/*Font*/
	const std::string Font("Font/emulogic.ttf");
	/*Game*/
	const int ScorePosX = 680;
	const int ScorePosY = 100;
	const int GameTextPosX = 370;
	const int GameTextPosY = 330;
	const int GameTextHeight = 12;
	/*Fruits*/
	const int DisplayFruitX = 90;
	const int DisplayFruitY = 380;
	const int DisplayFruitW = 30;
	const int DisplayFruitH = 30;
	const int MapFruitX = 390;
	const int MapFruitY = 330;
	const int MapFruitW = TileWidth;
	const int MapFruitH = TileHeight;
	const std::string FruitImgPath("images/fruits.png");
	/*Main Menu*/
	const std::string MainMenuImg("images/main.jpg");
	/*Move Algorithm*/
	const int MinRandomMoves = 40;
	const int MaxRandomMoves = 200;
	/*Window*/
	const int WindowWidth = 800;
	const int WindowHeight = 600;
}

