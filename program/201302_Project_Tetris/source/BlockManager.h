#ifndef __BLOCK_MGR__
#define __BLOCK_MGR__

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>


#include "game_obj.h"
#include "Block.h"
#include "SoundManager.h"


class BlockManager{
protected:
	int mCurBlocksNum;
	bool mEnd;
	int score_plus;
	bool mBlockUsed[512];
	Block *mBlockArr[512];
	Block *mCurBlock;
	bool **mHaveBlock[20];
	int mTileX;
	int mTileY;
	bool floorComplete_now;
	unsigned int Ex_audioId;
	unsigned int Fl_audioId;
	bool initial;
	int next_b;
	Real count_rotate;

	SceneManager *mSceneMgr;

	SoundManager* mSoundMgr;

	void resolveMoveCollision(Vector3& prePosition);
	void resolveRotateCollision(int direction);
	bool resolveBlockCollision();
	bool resolveBoundCollision();
	void projectCurrentBlock();
	void recordLocation();
	void clearBlock(int layer);
	void setupSound(void);
public:
BlockManager(SceneManager *a_SceneMgr);
virtual void update(const Ogre::FrameEvent& evt);
virtual void createNewBlock();
virtual void moveBlock(int dir);
virtual void rotateBlock(int dir);
virtual bool isEnd();
virtual int getScore();



const static int MOVE_NONE		= 0x0000;
const static int MOVE_UP		= 0x0001;
const static int MOVE_DOWN		= 0x0002;
const static int MOVE_LEFT		= 0x0004;
const static int MOVE_RIGHT		= 0x0008;
const static int MOVE_SPEEDUP	= 0x0010;
};

#endif