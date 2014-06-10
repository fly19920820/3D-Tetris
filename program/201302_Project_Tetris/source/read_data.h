#ifndef __DATA_READER_H__
#define __DATA_READER_H__

class DATA_READER {
protected:
	static int mTileX;
	static int mTileY;
public:
	DATA_READER();
	static void readData();
	static int getTileX();
	static int getTileY();
};

#endif