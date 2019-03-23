/**
  *************************************************************************************************************************
  * @file    File_Reader.cpp
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    14-March-2019
  * @brief   Class is designed for reading map file.
  **************************************************************************************************************************
*/
/*includes*/
#include"File_Reader.h"
#include"PacDots.h"
#include"Map.h"
#include"Dot.h"
#include"Primitives.h"
#include"DefaultValues.h"
#include<iostream>
#include<string>

/**
* @brief constructor
* @param1 map start position x
* @param2 map start position y
* @param2 path to the map file
*/
File_Reader::File_Reader(int x, int y,std::string path)
{
	std::ifstream map_file(path);
	if (map_file.fail())
	{
		std::cerr << "Unable to open map file: " << path << "\n";
		std::terminate();
	}

	tiles.reserve(DefaultValues::MapWidthInTiles*DefaultValues::MapHeightInTiles);
	pac_dots.reserve(100);
	maze.reserve(DefaultValues::MapWidthInTiles*DefaultValues::MapHeightInTiles);

	std::istream_iterator<int> in_iter(map_file);
	std::istream_iterator<int> eos;

	/*Map reading*/
	int map_x = x; int map_y = y; 
	for (; in_iter != eos; ++in_iter)
	{
		/*read all wall types*/
		if (*in_iter <= DefaultValues::MapElementTypes - 1)
		{
			/*build maze. type 15 and 12 are gates for ghost home. in maze it's a corridor*/
			if (*in_iter == 15 || *in_iter == 12)
				maze.push_back(DefaultValues::MazeCorridor);
			else 
				maze.push_back(DefaultValues::MazeWall);


			/*read types from 0 to 21*/
			if (*in_iter < 22)
			{
				tiles.emplace_back(map_x, map_y, *in_iter);
				map_x += DefaultValues::TileWidth;
			}

			/*read types from 22 to 26. this part is two tiles high */
			else if (*in_iter >= 22 && *in_iter < 27)
			{
				/*find the first part that's located above current*/
				std::vector<Tile>::iterator elem = std::find_if(tiles.begin(), tiles.end(),
					[this, map_y,map_x](Tile& t)
				{
					SDL_Rect box = t.get_rect();
					if (box.y == map_y - DefaultValues::TileHeight && box.x == map_x && t.get_type() >= 22)
						return true;
					else return false;
				});
				/*if first part was found*/
				if (elem == tiles.end())
				{
					tiles.emplace_back(map_x, map_y, 
						DefaultValues::TileWidth, DefaultValues::TileHeight * 2, *in_iter);
					map_x += (DefaultValues::TileWidth);
				}
				else
				{
					map_x += DefaultValues::TileWidth;
				}
			}

			/*read types from 27 to 31. this part is two tiles width */
			else if (*in_iter >= 27 && *in_iter < 32)
			{
				tiles.emplace_back(map_x, map_y, DefaultValues::TileWidth * 2, 
					DefaultValues::TileHeight, *in_iter);

				/*skip next element*/
				++in_iter;
				map_x += (DefaultValues::TileWidth * 2 );
				/*add wall to maze*/
				maze.push_back(DefaultValues::MazeWall);
			}

			/*read types from 32 to 39. this part is two tiles width and height*/
			else if (*in_iter >= 32)
			{
				/*find the first part that's located above current*/
				std::vector<Tile>::iterator elem = std::find_if(tiles.begin(), tiles.end(),
					[this, map_y, map_x](Tile& t)
				{
					SDL_Rect box = t.get_rect();
					if (box.y == map_y - DefaultValues::TileHeight && box.x == map_x && t.get_type() >= 32)
						return true;
					else return false;
				});
				/*if first part was found*/
				if (elem == tiles.end())
				{
					tiles.emplace_back(map_x, map_y, 
						DefaultValues::TileWidth * 2, DefaultValues::TileHeight * 2, *in_iter);
					/*skip next element*/
					++in_iter;
					map_x += (DefaultValues::TileWidth * 2);
				}
				else
				{
					++in_iter;
					map_x += (DefaultValues::TileWidth * 2);
				}
				/*add wall to maze*/
				maze.push_back(DefaultValues::MazeWall);
			}
		}
		/*read dots*/
		else if (*in_iter == DefaultValues::MapElementTypes)
		{
			pac_dots.emplace_back(map_x + (DefaultValues::TileWidth/2 - DefaultValues::DotWeight/2), map_y +
				(DefaultValues::TileHeight/2 - DefaultValues::DotHeight/ 2));
			map_x += DefaultValues::TileWidth;
			/*add corridor to maze*/
			maze.push_back(DefaultValues::MazeCorridor);
		}
		else
		{
			map_x += DefaultValues::TileWidth;
			/*add corridor to maze*/
			maze.push_back(DefaultValues::MazeCorridor);
		}
		/*if reached end of line*/
		if ((map_x - x) >= DefaultValues::MapWidthInPixels)
		{
			/*reset x position*/
			map_x = x;
			/*go to next line*/
			map_y += DefaultValues::TileHeight;
		}
	}
	/*close file*/
	map_file.close();
	/*shrink*/
	tiles.shrink_to_fit();
	pac_dots.shrink_to_fit();
	maze.shrink_to_fit();

	
}

/**
* @brief get tiles from map file that's been read
* @note
* @retval vector of tiles objects
*/
std::vector<Tile> File_Reader::get_tiles()
{
	return tiles;
}

/**
* @brief get dots from map file that's been read
* @note
* @retval vector of dots objects
*/
std::vector<Dot> File_Reader::get_pacdots()
{
	return pac_dots;
}

/**
* @brief get maze from map file that's been read
* @note
* @retval maze
*/
std::vector<int> File_Reader::get_maze()
{
	return maze;
}