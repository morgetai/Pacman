/**
  *************************************************************************************************************************
  * @file    File_Reader.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    14-March-2019
  * @brief   Class is designed for reading map file.
  **************************************************************************************************************************
*/
#ifndef FILE_READER_H
#define FILE_READER_H
/*includes*/
#include"Tile.h"
#include<memory>
#include<iterator>
#include<fstream>
#include<vector>
#include<algorithm>


/*Predeclared  classes*/
class Dot;

class File_Reader
{
public:
	/**
	* @brief constructor
	* @param1 map start position x
	* @param2 map start position y
	* @param2 path to the map file
	*/
	File_Reader(int x, int y, std::string path);

	/**
	* @brief get tiles from map file that's been read
	* @note  
	* @retval vector of tiles objects
	*/
	std::vector<Tile> get_tiles();

	/**
	* @brief get dots from map file that's been read
	* @note
	* @retval vector of dots objects
	*/
	std::vector<Dot> get_pacdots();

	/**
	* @brief get maze from map file that's been read
	* @note
	* @retval maze
	*/
	std::vector<int> get_maze();
private:
	std::vector<Tile> tiles;
	std::vector<Dot> pac_dots;
	std::vector<int> maze;
};

#endif