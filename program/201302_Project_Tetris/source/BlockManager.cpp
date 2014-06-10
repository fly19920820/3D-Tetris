#include "BlockManager.h"
#include "read_data.h"
#include <Math.h>

BlockManager::BlockManager(SceneManager *a_SceneMgr)
{
	mSceneMgr = a_SceneMgr;
	mCurBlocksNum = 0;
	mCurBlock = NULL;
	mEnd = false;
	mTileX = DATA_READER::getTileX();
	mTileY = DATA_READER::getTileY();
	for(int i=0;i < 512;i++)
		mBlockUsed[i] = false;
	for(int i = 0;i < 20;i++){
		mHaveBlock[i] = new bool*[mTileX];
		for(int j = 0;j < mTileX;j++){
			mHaveBlock[i][j] = new bool[mTileY];
			for(int k = 0;k < mTileY;k++)
				mHaveBlock[i][j][k] = false;
		}
	}
	count_rotate=0.0;
	initial=true;
	setupSound();
	score_plus=0;
	floorComplete_now=false;
	createNewBlock();
}


void BlockManager::setupSound(void)
{
	mSoundMgr = SoundManager::createManager();

	mSoundMgr->init();
	mSoundMgr->setAudioPath( (char*) "..\\..\\media\\music\\" );
	// Just for testing
	mSoundMgr->loadAudio( "02.wav", &Ex_audioId, false);
	mSoundMgr->loadAudio( "03.wav", &Fl_audioId, false);
}


void BlockManager::update(const Ogre::FrameEvent& evt)
{
	Vector3 position = mCurBlock->getPosition();
	for(int i = 0;i < 512;i++){
		if(mBlockUsed[i]){
			mBlockArr[i]->update(evt);
		}
	}
	
	resolveBoundCollision();
	
	bool collision = true;
	int  counter = 0;
	while(collision){
		collision = false;
		collision |= resolveBoundCollision();
		collision |= resolveBlockCollision();
		counter++;
		if(counter > 10)break;
	}

	recordLocation();

	if(floorComplete_now){
		floorComplete_now=false;
		mSoundMgr->playAudio( Ex_audioId, false );
	}
	else{}

	if(count_rotate>1.0){
		mBlockArr[next_b]->rotate(0x0002);
		count_rotate=0.0;
	}
	else{
		count_rotate+=evt.timeSinceLastFrame;
	}
}

bool BlockManager::isEnd()
{
	return mEnd;
}

void BlockManager::recordLocation()
{
	int top = 8;
	Real bound = 1500/mTileX;

	for(int i = 0;i < 20;i++){
		for(int j = 0;j < mTileX;j++){
			for(int k = 0;k < mTileY;k++)
				mHaveBlock[i][j][k] = false;
		}
	}

	for(int i = 0;i < 512;i++){
		if(mBlockUsed[i])
			if(mBlockArr[i] != mCurBlock){
				Vector3* pos = mBlockArr[i]->getAllPosition();
				for(int j = 0;j < 4;j++){
					if(mBlockArr[i]->getExist(j)){
						Vector3 position = pos[j];
						int height = Math::Floor((position.y- 500)/bound); //int height = Math::Floor((position.y + bound/2 /bound);
						int length = Math::Floor((position.x + 750 - 7500)/bound);
						int width  = Math::Floor((position.z + 750 - 7500)/bound);
						mHaveBlock[height][length][width] = true;
						if(height >= top)
							mEnd = true;
					}
				}
			}
	}
	
	for(int i = 0;i < 20;i++){
		bool floorComplete = true;
		for(int j = 0;j < mTileX;j++){
			for(int k = 0;k < mTileY;k++)
				if(!mHaveBlock[i][j][k]){
					floorComplete = false;
					break;
				}
			if(!floorComplete)
				break;
		}
		if(floorComplete){
			clearBlock(i);
			floorComplete_now=true;
			score_plus+=10;
		}
	}
}

int BlockManager::getScore(){
	int a=score_plus;
	if(score_plus>0){
		score_plus = 0;
	}
	return a;
}

void BlockManager::clearBlock(int layer)
{
	Real bound  = 1500/mTileX;
	//Real height = layer * bound + 150;
	for(int i = 0;i < 512;i++)
		if(mBlockUsed[i]){
			Vector3* pos = mBlockArr[i]->getAllPosition();
			for(int j = 0;j < 4;j++){
				Vector3 position = pos[j];
				int height = Math::Floor((position.y - 500)/bound);
				int length = Math::Floor((position.x + 750 - 7500)/bound);
				int width  = Math::Floor((position.z + 750 - 7500)/bound);
				if(height == layer){
				//if(Math::Floor(position.y + 0.5) == height){
					mBlockArr[i]->clear(j);
					if(mBlockArr[i]->isAllClear()){
						mBlockArr[i]->setVisible(false);
						mBlockUsed[i] = false;
						mBlockArr[i]->~Block();
					}
				}
			}
		}
}

void BlockManager::createNewBlock()
{
	int i;
	for(i = 0;i < 512;i++){
		if(i==next_b)
			continue;
		if(!mBlockUsed[i])
			break;
	}
	if(i >= 512)return;

	if(initial){
		mBlockUsed[i] = true;
		mBlockArr[i] = new Block(mSceneMgr);
		Vector3 position = Vector3(7500, (750/mTileX) * 21 + 500, 7500);
		mBlockArr[i]->setPosition(position);
		mBlockArr[i]->setVisible(true);
		mCurBlock = mBlockArr[i];
		for(i = 0;i < 512;i++)
			if(!mBlockUsed[i])
				break;
		initial=false;
	}
	else{
		mBlockUsed[next_b] = true;
		Vector3 position = Vector3(7500, (750/mTileX) * 21 + 500, 7500);
		mBlockArr[next_b]->setPosition(position);
		mCurBlock = mBlockArr[next_b];
		mSoundMgr->playAudio( Fl_audioId, false );
	}

	mBlockArr[i] = new Block(mSceneMgr);
	Vector3 position = Vector3(0,-6980,2780);
	mBlockArr[i]->setPosition(position);
	mBlockArr[i]->setVisible(true);

	next_b = i;
}

void BlockManager::moveBlock(int dir)
{
	Vector3 position = mCurBlock->getPosition();
	if(dir == MOVE_UP)
		mCurBlock->translate(Vector3(0,0,-1500/mTileY));
	else if(dir == MOVE_DOWN)
		mCurBlock->translate(Vector3(0,0, 1500/mTileY));
	else if(dir == MOVE_LEFT)
		mCurBlock->translate(Vector3(-1500/mTileX,0,0));
	else if(dir == MOVE_RIGHT)
		mCurBlock->translate(Vector3(1500/mTileX ,0,0));
	else if(dir == MOVE_SPEEDUP){
		projectCurrentBlock();
		return;
	}
	resolveMoveCollision(position);
}

void BlockManager::rotateBlock(int dir)
{
	mCurBlock->rotate(dir);
	resolveRotateCollision(dir);
}

void BlockManager::resolveRotateCollision(int dir)
{
	int bound = 1500/mTileX;
	Vector3* pos = mCurBlock->getAllPosition();
	for(int i = 0;i < 4;i++){
		if(mCurBlock->getExist(i)){
			Vector3 position = pos[i];
			Real x = position.x;
			Real z = position.z;
			if(x > 750 + 7500 || x < -750 + 7500 || z > 750 + 7500 || z < -750 +7500){
				mCurBlock->rotateBack(dir);
				return;
			}
		}
	}
	for(int i = 0;i < 512;i++)
		if(mBlockUsed[i])
			if(mCurBlock != mBlockArr[i]){
				Vector3* pos2 = mBlockArr[i]->getAllPosition();
				for(int j = 0;j < 4;j++){
					if(mCurBlock->getExist(j)){
						Vector3 p1 = pos[j];
						for(int k = 0;k < 4;k++){
							if(mBlockArr[i]->getExist(k)){
								Vector3 p2 = pos2[k];
								Vector3 p = (p1 - p2);
								int d = p.normalise();	
								if(Math::Abs(d) < bound){
									mCurBlock->rotateBack(dir);
									return;
								}
							}
						}
					}
				}
			}
}

void BlockManager::projectCurrentBlock()
{
	Real bound = 1500/mTileX;
	Vector3* pos = mCurBlock->getAllPosition();
	int highest = 0;
	int num = 0;
	for(int i = 0;i < 4;i++){
		if(mCurBlock->getExist(i)){
			Vector3 position = pos[i];
			int height = Math::Floor((position.y - 500)/bound);
			int length = Math::Floor((position.x + 750 - 7500)/bound);
			int width  = Math::Floor((position.z + 750 - 7500)/bound);
			for(;height >= 0;height--)
				if(mHaveBlock[height][length][width] == true)break;
			height++;
			if(height > highest){
				highest = height;
				num = i;
			}
		}
	}

	Vector3 position = pos[num];
	int height = highest;
	int length = Math::Floor((position.x + 750 - 7500)/bound);
	int width  = Math::Floor((position.z + 750 - 7500)/bound);

	Real x = length * bound + (pos[0].x - pos[num].x) - mTileX/2 * bound + 7500;
	Real y = height * bound + (pos[0].y - pos[num].y) + bound/2 + 500;
	Real z = width  * bound + (pos[0].z - pos[num].z) - mTileY/2 * bound + 7500;
	mCurBlock->setPosition(Vector3(x,y,z));
}

void BlockManager::resolveMoveCollision(Vector3& prePosition)
{
	int bound = 1500/mTileX;
	Vector3* pos = mCurBlock->getAllPosition();

	for(int i = 0;i < 4;i++){
		if(mCurBlock->getExist(i)){
			Vector3 position = pos[i];
			Real x = position.x;
			Real z = position.z;
			if(x > 750 + 7500 || x < -750 + 7500 || z > 750 + 7500 || z < -750 + 7500){
				mCurBlock->setPosition(prePosition);
				return;
			}
		}
	}
	for(int i = 0;i < 512;i++)
		if(mBlockUsed[i])
			if(mCurBlock != mBlockArr[i]){
				Vector3* pos2 = mBlockArr[i]->getAllPosition();
				for(int j = 0;j < 4;j++){
					if(mCurBlock->getExist(j)){
						Vector3 p1 = pos[j];
						for(int k = 0;k < 4;k++){
							if(mBlockArr[i]->getExist(k)){
								Vector3 p2 = pos2[k];
								Vector3 p = (p1 - p2);
								int d = p.normalise();	
								if(Math::Abs(d) < bound){
									mCurBlock->setPosition(prePosition);
									return;
								}
							}
						}
					}
				}
			}
}
	
bool BlockManager::resolveBlockCollision()
{
	bool collision = false;
	int bound = 1500/mTileX;
	bool create = false;
	for(int i = 0;i < 512;i++){
		if(mBlockUsed[i]){
			Vector3* pos = mBlockArr[i]->getAllPosition();
			for(int j = i + 1;j < 512;j++)
				if(i != j)
				if(mBlockUsed[j]){
					Vector3* pos2 = mBlockArr[j]->getAllPosition();
					for(int k = 0;k < 4;k++){
						if(mBlockArr[i]->getExist(k)){
							Vector3 p1 = pos[k];
							for(int l = 0;l < 4;l++){
								if(mBlockArr[j]->getExist(l)){
									Vector3 p2 = pos2[l];
									Vector3 p = (p1 - p2);
									int d = p.normalise();;	
									if(Math::Abs(d) < bound && p.y != 0){
										collision = true;
										d = bound - d;
										p.x = 0;
										p.z = 0;
										if(p1.y > p2.y)
											mBlockArr[i]->translate(p * d);
										else
											mBlockArr[j]->translate(-p * d);
										create |= (mBlockArr[i] == mCurBlock || mBlockArr[j] == mCurBlock);
										//pos = mBlockArr[i]->getAllPosition();
										//pos2 = mBlockArr[j]->getAllPosition();
										//p1 = pos[k];
									}
								}
							}
						}
					}
				}
		}
	}
	if(create){
		createNewBlock();
	}
	return collision;
}

bool BlockManager::resolveBoundCollision()
{
	bool collision = false;
	bool create = false;
	SceneNode* node = mSceneMgr->getEntity("GroundEntity")->getParentSceneNode();
	Real limit_y = node->getPosition().y + (1500.0/mTileX)/2;
	for(int i = 0;i < 512;i++)
		if(mBlockUsed[i]){
			Vector3* position = mBlockArr[i]->getAllPosition();
			for(int j = 0;j < 4;j++){
				if(mBlockArr[i]->getExist(j)){
					if(position[j].y < limit_y){
						collision = true;
						position = mBlockArr[i]->getAllPosition();
						position[0].y = limit_y + (position[0].y - position[j].y);// + 500;
						mBlockArr[i]->setPosition(position[0]);
						position = mBlockArr[i]->getAllPosition();
						create |= (mBlockArr[i] == mCurBlock);
					}
					if(mBlockArr[i] == mCurBlock)
						create |= (position[j].y == limit_y);
				}
			}
		}
	if(create)
		createNewBlock();
	return collision;
}