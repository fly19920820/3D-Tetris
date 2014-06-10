#ifndef __BLOCKS_H__
#define __BLOCKS_H__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreParticleSystem.h>
#include <OgreParticleEmitter.h>

#include "game_obj.h"
class Block{
private :
	static int mBlockNum;
	void setOffParticleSystem(Ogre::SceneNode *fNode, const Ogre::Vector3 &pos);
protected:
	SceneManager *mSceneMgr;
	GAME_OBJ* mMainBlock;
	int mType;
	SceneNode* mAttachedBlock[4];
	Vector3 mPosition[4];
	bool mBlockExist[4];
	SceneNode* fNode[4];
	bool mTurned[3];
	Real  mCounter;
public:
	Block(SceneManager *a_SceneMgr);
	~Block();
	virtual void update(const Ogre::FrameEvent& evt);
	virtual void updateLocation();
	virtual const Ogre::Vector3& getPosition() const;
	virtual Ogre::Vector3* getAllPosition();
	virtual bool getExist(int num);
	virtual void setVisible(bool b);
	virtual void setPosition(const Vector3 &pos);
	virtual void translate(const Vector3 &v);
	virtual void clear(int num);
	virtual bool isAllClear();
	virtual void rotate(int direction);
	virtual void rotateBack(int direction);

	const static int ROTATE_NONE	= 0x0000;
	const static int ROTATE_X		= 0x0001;
	const static int ROTATE_Y		= 0x0002;
	const static int ROTATE_Z		= 0x0004;

	const static int TYPE_TEST		= 0x0000;
	const static int TYPE_T			= 0x0001;
	const static int TYPE_L			= 0x0002;
	const static int TYPE_LINE		= 0x0004;
	const static int TYPE_SQUARE	= 0x0008;
};

#endif