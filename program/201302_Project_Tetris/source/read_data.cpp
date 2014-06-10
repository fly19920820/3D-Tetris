#include <fstream>
#include <iostream>
#include <string>
#include "read_data.h"
#define DATA_FILE_NAME	"9917144_game_data.txt"

using namespace std;

int	DATA_READER::mTileX = 5;
int	DATA_READER::mTileY = 5;

DATA_READER::DATA_READER()
{

}

void DATA_READER::readData()
{
	using namespace std;
	std::ifstream *fp;
	fp = new std::ifstream(DATA_FILE_NAME, ios::in | ios::binary);
	if (fp == 0 || fp->fail()) {
		cout << "Cannot open data file:" << DATA_FILE_NAME << endl;
		return;
	}
	
	std::string key;
	double num[2];
	while (!fp->eof()) {
		*fp >> key;
		
		if (key.compare("TILE_X") == 0) {
			*fp >> num[0];
			mTileX = num[0];
		}

		if (key.compare("TILE_Y") == 0) {
			*fp >> num[1];
			mTileY = num[1];
		}
	}
}

int DATA_READER::getTileX()
{
	return mTileX;
}

int DATA_READER::getTileY()
{
	return mTileY;
}