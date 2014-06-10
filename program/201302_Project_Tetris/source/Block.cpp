#include "Block.h"
#include "BasicTools.h"
#include "read_data.h"

int Block::mBlockNum = 0;

Block::Block(SceneManager *a_SceneMgr)
{
	Ogre::String name;
	mMainBlock = new GAME_OBJ(a_SceneMgr);
	mMainBlock->createGameObj("block","cube.mesh");
	mMainBlock->mEntity->setMaterialName("WoodPallet");
	
	const AxisAlignedBox bb =  mMainBlock->mEntity->getBoundingBox();
	Vector3 originSize = Vector3(bb.getMaximum().x - bb.getMinimum().x,bb.getMaximum().y - bb.getMinimum().y,bb.getMaximum().z - bb.getMinimum().z);
	int mSize = 1500/DATA_READER::getTileX();
	mMainBlock->scale(mSize/originSize[0],mSize/originSize[1],mSize/originSize[2]);
	//printf("SCALE: %f %f %f\n",mSize/originSize[0],mSize/originSize[1],mSize/originSize[2]);
	mAttachedBlock[0] = mMainBlock->getSceneNode();
	mBlockExist[0] = true;

	mSceneMgr = a_SceneMgr;
	mCounter = 0;

	srand(time(0));
	mType  = pow(2.0,rand() % 4);
	//mType = TYPE_T;
	//mType = TYPE_L;
	//mType = TYPE_LINE;

	for(int i = 1;i < 4;i++)
	{
		genNameUsingIndex("childBlock",mBlockNum * 4 + i,name);
		mAttachedBlock[i] = mMainBlock->getSceneNode()->createChildSceneNode(name);//(mAttachedBlock[i]->getSceneNode());
		Entity* ent = mSceneMgr->createEntity(name,"cube.mesh");
		mAttachedBlock[i]->attachObject(ent);
		ent->setMaterialName("WoodPallet");
		mBlockExist[i] = true;
	}
	mBlockNum++;

	for(int i = 0;i < 3;i++)
		mTurned[i] = false;
}

Block::~Block()
{
	//printf("block distructed\n");
}

void Block::update(const Ogre::FrameEvent& evt)
{
	Real time = evt.timeSinceLastFrame;
	int v = 1500 / DATA_READER::getTileX();
	Vector3 moveVec = Vector3(0, - v * time,0);
	translate(moveVec);
}

void Block::updateLocation()
{
	mPosition[0] = mMainBlock->getPosition();
	for(int i = 1;i < 4;i++)
	{
		mPosition[i] = mMainBlock->getSceneNode()->convertLocalToWorldPosition(mAttachedBlock[i]->getPosition());
		//printf("(%f,%f,%f)   ",mPosition[i].x,mPosition[i].y,mPosition[i].z);
	}
	//printf("\n");
}

const Ogre::Vector3& Block::getPosition() const
{
	return mMainBlock->getPosition();
}

Ogre::Vector3* Block::getAllPosition()
{
	return mPosition;
}

void Block::setVisible(bool b)
{
	//mMainBlock->setVisible(b);
	
	for(int i = 0;i < 4;i++){
		mAttachedBlock[i]->setVisible(b);
	}
}

void Block::clear(int num)
{
	if(num == 0)
		mAttachedBlock[num]->detachObject(mMainBlock->mEntity);
	else
		mAttachedBlock[num]->detachAllObjects();
	//static int nameNum = 0;
	//String name;
	//genNameUsingIndex("particleNode",nameNum, name);
	//nameNum++;
	//setOffParticleSystem(mSceneMgr->getRootSceneNode()->createChildSceneNode(name), mPosition[num]);
	//setOffParticleSystem(mSceneMgr->getSceneNode("particle"), "explosion", mAttachedBlock[num]->getPosition());
	static int nameNum = 0;
	String name;
	genNameUsingIndex("particleNode",nameNum, name);
	nameNum++;
	fNode[num] = mSceneMgr->getRootSceneNode()->createChildSceneNode(name);
	setOffParticleSystem(fNode[num], mPosition[num]);
	mBlockExist[num] = false;
}

bool Block::isAllClear()
{
	return !mBlockExist[0] & !mBlockExist[1] & !mBlockExist[2] & !mBlockExist[3];
}

void Block::setPosition(const Vector3 &pos)
{
	Real v = (1500 / DATA_READER::getTileX()) / mMainBlock->getSceneNode()->getScale().x;
	//const AxisAlignedBox bb =  mMainBlock->mEntity->getBoundingBox();
	//Real v = bb.getMaximum().x - bb.getMinimum().x;
	//printf("%f\n",v);
	mMainBlock->setPosition(pos);
	//printf("MainBlock set to (%f ,%f ,%f)\n",pos.x,pos.y,pos.z);
	
	if(mType == TYPE_TEST)
		for(int i = 1;i < 4;i++)
			mAttachedBlock[i]->setPosition(Vector3(0,-v * i,0));
	if(mType == TYPE_T){
		mAttachedBlock[1]->setPosition(Vector3(0,-v,0));
		mAttachedBlock[2]->setPosition(Vector3(v,0,0));
		mAttachedBlock[3]->setPosition(Vector3(-v,0,0));
	}
	if(mType == TYPE_L){
		mAttachedBlock[1]->setPosition(Vector3(0,v,0));
		mAttachedBlock[2]->setPosition(Vector3(0,v * 2,0));
		mAttachedBlock[3]->setPosition(Vector3(-v,0,0));
	}
	if(mType == TYPE_LINE){
		mAttachedBlock[1]->setPosition(Vector3(0,v,0));
		mAttachedBlock[2]->setPosition(Vector3(0,-v,0));
		mAttachedBlock[3]->setPosition(Vector3(0,-v * 2,0));
	}
	if(mType == TYPE_SQUARE){
		mAttachedBlock[1]->setPosition(Vector3(v,0,0));
		mAttachedBlock[2]->setPosition(Vector3(0,0,v));
		mAttachedBlock[3]->setPosition(Vector3(v,0,v));
	}

	updateLocation();
}

void Block::translate(const Vector3 &v)
{
	mMainBlock->translate(v);
	updateLocation();
}

bool Block::getExist(int num)
{
	return mBlockExist[num];
}

void Block::rotate(int direction)
{
	//if(direction == ROTATE_X){
	//	if(!mTurned[0]){
	//		mMainBlock->getSceneNode()->pitch(Radian(Degree(90).valueRadians()));
	//		mTurned[0] = true;
	//	}
	//	else{
	//		mMainBlock->getSceneNode()->pitch(Radian(Degree(-90).valueRadians()));
	//		mTurned[0] = false;
	//	}
	//}
	//if(direction == ROTATE_Y){
	//	if(!mTurned[1]){
	//		mMainBlock->getSceneNode()->yaw(Radian(Degree(90).valueRadians()));
	//		mTurned[1] = true;
	//	}
	//	else{
	//		mMainBlock->getSceneNode()->yaw(Radian(Degree(-90).valueRadians()));
	//		mTurned[1] = false;
	//	}
	//}
	//if(direction == ROTATE_Z){
	//	if(!mTurned[2]){
	//		mMainBlock->getSceneNode()->roll(Radian(Degree(90).valueRadians()));
	//		mTurned[2] = true;
	//	}
	//	else{
	//		mMainBlock->getSceneNode()->roll(Radian(Degree(-90).valueRadians()));
	//		mTurned[2] = false;
	//	}
	//}
	if(direction == ROTATE_X){
			mMainBlock->getSceneNode()->pitch(Radian(Degree(90).valueRadians()));
	}
	if(direction == ROTATE_Y){
			mMainBlock->getSceneNode()->yaw(Radian(Degree(90).valueRadians()));
	}
	if(direction == ROTATE_Z){
			mMainBlock->getSceneNode()->roll(Radian(Degree(90).valueRadians()));
	}
	updateLocation();
}

void Block::rotateBack(int direction)
{
	//if(direction == ROTATE_X){
	//	if(mTurned[0]){
	//		mMainBlock->getSceneNode()->pitch(Radian(Degree(-90).valueRadians()));
	//		mTurned[0] = false;
	//	}
	//	else{
	//		mMainBlock->getSceneNode()->pitch(Radian(Degree(90).valueRadians()));
	//		mTurned[0] = true;
	//	}
	//}
	//if(direction == ROTATE_Y){
	//	if(mTurned[1]){
	//		mMainBlock->getSceneNode()->yaw(Radian(Degree(-90).valueRadians()));
	//		mTurned[1] = false;
	//	}
	//	else{
	//		mMainBlock->getSceneNode()->yaw(Radian(Degree(90).valueRadians()));
	//		mTurned[1] = true;
	//	}
	//}
	//if(direction == ROTATE_Z){
	//	if(mTurned[2]){
	//		mMainBlock->getSceneNode()->roll(Radian(Degree(-90).valueRadians()));
	//		mTurned[2] = false;
	//	}
	//	else{
	//		mMainBlock->getSceneNode()->roll(Radian(Degree(90).valueRadians()));
	//		mTurned[2] = true;
	//	}
	//}
	if(direction == ROTATE_X){
			mMainBlock->getSceneNode()->pitch(Radian(Degree(-90).valueRadians()));
	}
	if(direction == ROTATE_Y){
			mMainBlock->getSceneNode()->yaw(Radian(Degree(-90).valueRadians()));
	}
	if(direction == ROTATE_Z){
			mMainBlock->getSceneNode()->roll(Radian(Degree(-90).valueRadians()));
	}
	updateLocation();
}

void Block::setOffParticleSystem(
	Ogre::SceneNode *fNode, const Ogre::Vector3 &pos) 
{
	static int num = 0;
	String name;
	fNode->setPosition(pos);
	fNode->setVisible(true);
	genNameUsingIndex("particle",num,name);
	num++;
	ParticleSystem* p = mSceneMgr->createParticleSystem(name, "Examples/Smoke");
	if (p == NULL) return;
	fNode->attachObject(p);
	p->setKeepParticlesInLocalSpace(true);
	fNode->scale(10,10,10);
	p->setSpeedFactor(3.0);
	p->setVisible(true);
	ParticleEmitter *e = p->getEmitter(0);
	e->setEnabled(true);
	e->setDuration(1);
	//printf("set off particle\n");
}