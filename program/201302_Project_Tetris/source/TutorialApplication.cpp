//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#include "TutorialApplication.h"
#include "BasicTools.h"
#include "read_data.h"
#define PI 3.14159265


using namespace Ogre;
BasicTutorial_00::BasicTutorial_00(void)
{
	for(int i=0;i<4;i++)
		moveDir[i] = false;
	resolve=true;
	time_resolve=0.0;
	PlayEnable=false;
	mGameStage = GameStage_MainMenu;
	mGameType = GameType_None;
	button_in = false;
}

/*!
	Simply create two scene manager.
*/
void BasicTutorial_00::chooseSceneManager()
{
	//create two scene managers
	/*
	mSceneMgrArr[0] = mRoot
		->createSceneManager(ST_GENERIC, "primary");*/
	mSceneMgrArr[0] = mRoot
		->createSceneManager(ST_EXTERIOR_CLOSE, "primary");
	mSceneMgrArr[1] = mRoot
		->createSceneManager(ST_GENERIC, "secondary");
}


void BasicTutorial_00::createMainMenuCamera(void)
{
	mSceneMgr = mSceneMgrArr[1];
	mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(0,0,125));
	mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);
	//mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createGameMainCamera(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[1] = mSceneMgr->createCamera("PlayerCam1");
    mCamera->setPosition(Ogre::Vector3(7500,1500/DATA_READER::getTileX() * 10 * 2 + 500,1500/DATA_READER::getTileX() * 10 * 2 + 7500));
    mCamera->lookAt(Ogre::Vector3(7500,500,7500));
    mCamera->setNearClipDistance(5);
	mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
	mCameraManArr[0]->setTopSpeed(40 * mCameraManArr[0]->getTopSpeed());
	
}


void BasicTutorial_00::createGameBackLittleCamera(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[2] = mSceneMgr->createCamera("PlayerCam2");
	//mCamera->setPosition(Ogre::Vector3(0,1500/DATA_READER::getTileX() * 10 * 1.2,1));
	mCamera->setPosition(Ogre::Vector3(7500,1500/DATA_READER::getTileX() * 10 * 1.5 + 500, -1500/DATA_READER::getTileX() * 10 * 1.5 + 7500));
	mCamera->lookAt(Ogre::Vector3(7500,500,7500));
    mCamera->setNearClipDistance(5);
	//mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}


void BasicTutorial_00::createGameRightLittleCamera(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[3] = mSceneMgr->createCamera("PlayerCam3");
	//mCamera->setPosition(Ogre::Vector3(0,1500/DATA_READER::getTileX() * 10 * 1.2,1));
	mCamera->setPosition(Ogre::Vector3(1500/DATA_READER::getTileX() * 10 * 1.5 + 7500,1500/DATA_READER::getTileX() * 10 * 1.5 + 500, 7500));
	mCamera->lookAt(Ogre::Vector3(7500,500,7500));
    mCamera->setNearClipDistance(5);
	//mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createGameLeftLittleCamera(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[4] = mSceneMgr->createCamera("PlayerCam4");
	//mCamera->setPosition(Ogre::Vector3(0,1500/DATA_READER::getTileX() * 10 * 1.2,1));
	mCamera->setPosition(Ogre::Vector3(-1500/DATA_READER::getTileX() * 10 * 1.5 + 7500,1500/DATA_READER::getTileX() * 10 * 1.5 + 500, 7500));
	mCamera->lookAt(Ogre::Vector3(7500,500,7500));
    mCamera->setNearClipDistance(5);
	//mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createGameBackGroundCamera(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[5] = mSceneMgr->createCamera("PlayerCam5");
	mCamera->setPosition(Ogre::Vector3(7500,-150,7500));
	mCamera->lookAt(Ogre::Vector3(7500,-200,7500));
    mCamera->setNearClipDistance(5);
	//mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}


void BasicTutorial_00::createNextBlockCamera(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[6] = mSceneMgr->createCamera("PlayerCam6");
    mCamera->setPosition(Ogre::Vector3(0,-5500,1500));
    mCamera->lookAt(Ogre::Vector3(0,-6980,2780));
    mCamera->setNearClipDistance(5);
	//mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createMainMenuViewport(void)
{
	mCamera = mCameraArr[0];
	vp[0] = mWindow->addViewport(mCamera, 7);
	setupSound();
}

void BasicTutorial_00::createGameMainViewport(void)
{
	mCamera = mCameraArr[1];
	vp[1] = mWindow->addViewport(mCamera, 2);
	vp[1]->setBackgroundColour(Ogre::ColourValue(0.2,0.2,0.2));
	vp[1]->setDimensions(0.25,0.0,0.5,1.0);
	mCamera->setAspectRatio(Ogre::Real(vp[1]->getActualWidth()) / Ogre::Real(vp[1]->getActualHeight()));
	vp[1]->setOverlaysEnabled(false);
	vp[1]->setSkiesEnabled(false);
}

void BasicTutorial_00::createGameBackLittleViewport(void)
{
	mCamera = mCameraArr[2];
	vp[2] = mWindow->addViewport(mCamera, 3);
	vp[2]->setBackgroundColour(Ogre::ColourValue(0.75,0.0025,0.25,0.33));
	vp[2]->setDimensions(0.75,0.0025,0.2475,0.33);
	mCamera->setAspectRatio(Ogre::Real(vp[2]->getActualWidth()) / Ogre::Real(vp[2]->getActualHeight()));
	vp[2]->setOverlaysEnabled(false);
	vp[2]->setSkiesEnabled(false);
}

void BasicTutorial_00::createGameRightLittleViewport(void)
{
	mCamera = mCameraArr[3];
	vp[3] = mWindow->addViewport(mCamera, 4);
	vp[3]->setBackgroundColour(Ogre::ColourValue(0.75,0.335,0.25,0.33));
	vp[3]->setDimensions(0.75,0.335,0.2475,0.33);
	mCamera->setAspectRatio(Ogre::Real(vp[3]->getActualWidth()) / Ogre::Real(vp[3]->getActualHeight()));
	vp[3]->setOverlaysEnabled(false);
	vp[3]->setSkiesEnabled(false);
}


void BasicTutorial_00::createGameLefttLittleViewport(void)
{
	mCamera = mCameraArr[4];
	vp[4] = mWindow->addViewport(mCamera, 5);
	vp[4]->setBackgroundColour(Ogre::ColourValue(0.75,0.6675,0.25,0.33));
	vp[4]->setDimensions(0.75,0.6675,0.2475,0.33);
	mCamera->setAspectRatio(Ogre::Real(vp[4]->getActualWidth()) / Ogre::Real(vp[4]->getActualHeight()));
	vp[4]->setOverlaysEnabled(false);
	vp[4]->setSkiesEnabled(false);
}


void BasicTutorial_00::createGameBackGroundViewport(void)
{
	mCamera = mCameraArr[5];
	vp[5] = mWindow->addViewport(mCamera,1);
	vp[5]->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));
	vp[5]->setDimensions(0.0,0,1.0,1.0);
	mCamera->setAspectRatio(Ogre::Real(vp[5]->getActualWidth()) / Ogre::Real(vp[5]->getActualHeight()));
	vp[5]->setOverlaysEnabled(true);
}

void BasicTutorial_00::createNextBlockViewport(void)
{
	mCamera = mCameraArr[6];
	vp[6] = mWindow->addViewport(mCamera,6);
	vp[6]->setBackgroundColour(Ogre::ColourValue(0.2,0.2,0.2));
	vp[6]->setDimensions(0.0,0.66,0.245,0.335);
	mCamera->setAspectRatio(Ogre::Real(vp[6]->getActualWidth()) / Ogre::Real(vp[6]->getActualHeight()));
	vp[6]->setOverlaysEnabled(false);
}

void BasicTutorial_00::setupSound(void)
{
	mSoundMgr = SoundManager::createManager();

	mSoundMgr->init();
	mSoundMgr->setAudioPath( (char*) "..\\..\\media\\music\\" );
	logMessage("==================================");
	logMessage("musicloading");
	// Just for testing

	mSoundMgr->loadAudio( "01.wav", &audioId_back, true); 
	mSoundMgr->loadAudio( "04.wav", &audioId_speed, false);	
	mSoundMgr->loadAudio( "05.wav", &audioId_click, false);	
	mSoundMgr->loadAudio( "06.wav", &audioId_button_on, false); 
	logMessage("==================================");
}
void BasicTutorial_00::setOffBackgroundSmoke(
	Ogre::SceneNode *fNode, const Ogre::Vector3 &pos) 
{
	static int num = 0;
	String name;
	fNode->setPosition(pos);
	fNode->setVisible(true);
	genNameUsingIndex("BackSmoke",num,name);
	num++;
	//ParticleSystem* p = mSceneMgr->createParticleSystem(name, "Examples/PurpleFountain");
	ParticleSystem* p = mSceneMgr->createParticleSystem(name, "Examples/Smoke");
	if (p == NULL) return;
	fNode->attachObject(p);
	//p->setKeepParticlesInLocalSpace(true);
	fNode->scale(10,10,10);
	//p->setSpeedFactor(3.0);
	p->setVisible(true);
	ParticleEmitter *e = p->getEmitter(0);
	e->setEnabled(true);
	//e->setDuration(5);
	//printf("set off particle\n");
}


void BasicTutorial_00::setOffFirework(
	Ogre::SceneNode *fNode, const Ogre::Vector3 &pos) 
{
	static int num = 0;
	String name;
	fNode->setPosition(pos);
	fNode->setVisible(true);
	genNameUsingIndex("firework",num,name);
	num++;
	ParticleSystem* p = mSceneMgr->createParticleSystem(name, "Examples/Fireworks");
	//ParticleSystem* p = mSceneMgr->createParticleSystem(name, "Examples/Smoke");
	if (p == NULL) return;
	fNode->attachObject(p);
	p->setKeepParticlesInLocalSpace(true);
	fNode->scale(10,10,10);
	//p->setSpeedFactor(3.0);
	p->setVisible(true);
	ParticleEmitter *e = p->getEmitter(0);
	e->setEnabled(true);
	e->setDuration(5);
	//printf("set off particle\n");
}

void BasicTutorial_00::setOffSnow(
	Ogre::SceneNode *fNode, const Ogre::Vector3 &pos) 
{
	static int num = 0;
	String name;
	fNode->setPosition(pos);
	fNode->setVisible(true);
	genNameUsingIndex("snow",num,name);
	num++;
	ParticleSystem* p = mSceneMgr->createParticleSystem(name, "Examples/Snow");
	//ParticleSystem* p = mSceneMgr->createParticleSystem(name, "Examples/Smoke");
	if (p == NULL) return;
	fNode->attachObject(p);
	p->setKeepParticlesInLocalSpace(true);
	fNode->scale(100,100,100);
	//p->setSpeedFactor(3.0);
	p->setVisible(true);
	ParticleEmitter *e = p->getEmitter(0);
	e->setEnabled(true);
	e->setEmissionRate(10);
	//e->setDuration(5);
	//printf("set off particle\n");
}

void BasicTutorial_00::setOffRain(
	Ogre::SceneNode *fNode, const Ogre::Vector3 &pos) 
{
	static int num = 0;
	String name;
	fNode->setPosition(pos);
	fNode->setVisible(true);
	genNameUsingIndex("rain",num,name);
	num++;
	ParticleSystem* p = mSceneMgr->createParticleSystem(name, "Examples/Rain");
	//ParticleSystem* p = mSceneMgr->createParticleSystem(name, "Examples/Smoke");
	if (p == NULL) return;
	fNode->attachObject(p);
	p->setKeepParticlesInLocalSpace(true);
	fNode->scale(100,100,100);
	fNode->rotate(Vector3(1,0,1),Radian(Degree(30)));
	//p->setSpeedFactor(3.0);
	p->setVisible(true);
	ParticleEmitter *e = p->getEmitter(0);
	e->setEnabled(true);
	//e->setEmissionRate(10);
	//e->setDuration(5);
	//printf("set off particle\n");
}

void BasicTutorial_00::setOffSwarm(
	Ogre::SceneNode *fNode, const Ogre::Vector3 &pos) 
{
	static int num = 0;
	String name;
	fNode->setPosition(pos);
	fNode->setVisible(true);
	genNameUsingIndex("swarm",num,name);
	num++;
	ParticleSystem* p = mSceneMgr->createParticleSystem(name, "Examples/PurpleFountain");
	if (p == NULL) return;
	fNode->attachObject(p);
	p->setKeepParticlesInLocalSpace(true);
	fNode->scale(10,10,10);
	//fNode->rotate(Vector3(1,0,1),Radian(Degree(30)));
	p->setVisible(true);
	ParticleEmitter *e = p->getEmitter(0);
	e->setEnabled(true);
	//e->setEmissionRate(10);
	e->setDuration(2);
	//printf("set off particle\n");
}



void BasicTutorial_00::createGameScene(void) 
{
	mSceneMgr = mSceneMgrArr[0];
	mSoundMgr->playAudio( audioId_back, false );
	mSceneMgr->setAmbientLight( ColourValue( 0.5, 0.5, 0.5 ) ); 
	//mSceneMgr->setAmbientLight( ColourValue( 1, 1, 1 ) );  
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	mSceneMgr->setWorldGeometry("terrain.cfg");
	mSceneMgr->setSkyBox(true, "Examples/TrippySkyBox");
	Plane plane(Vector3::UNIT_Y,0);
	MeshManager::getSingleton().createPlane("ground",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
											1500,1500, 	// width, height
											20,20, 		// x- and y-segments
											true, 		// normal
											1, 		// num texture sets
											DATA_READER::getTileX(),DATA_READER::getTileY(), 		// x- and y-tiles
											Vector3::UNIT_Z);	// upward vector 
	Entity *ent = mSceneMgr->createEntity("GroundEntity","ground");
	ent->setMaterialName("Examples/OgreLogo");
	SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	node->attachObject(ent);
	node->setPosition(7500,500,7500);
	ent->setCastShadows(false);
	

	String name;
	genNameUsingIndex("fireworkNode",0, name);
	SceneNode* fNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name);
	setOffFirework(fNode, Vector3(7500,1000,7500));

	genNameUsingIndex("snowNode",0, name);
	fNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name);
	setOffSnow(fNode, Vector3(7500,1000,7500));

	genNameUsingIndex("rainNode",0, name);
	fNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name);
	setOffRain(fNode, Vector3(7500,1000,7500));

	genNameUsingIndex("swarmNode",0, name);
	fNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name);
	setOffSwarm(fNode, Vector3(7500,500,7500));

	for(int i = 0;i < 10;i++){
		genNameUsingIndex("backSmokeNode",i, name);
		fNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name);
		setOffBackgroundSmoke(fNode, Vector3(Math::Cos((float)i / 5.0 * PI) * 1800 + 7500,500,Math::Sin((float)i / 5.0 * PI) * 1800 + 7500));
	}
	blockMove = BlockManager::MOVE_NONE;
	blockRotate = Block::ROTATE_NONE;
	blockMgr = new BlockManager(mSceneMgr);
	
	/*
	ent = mSceneMgr->createEntity("Penguin","penguin.mesh");
	AxisAlignedBox penguinSize =  ent->getBoundingBox();
	SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Penguin",Vector3(0,penguinSize.getMaximum().y - penguinSize.getMinimum().y,0));
	node->scale(2,2,2);
	node->attachObject(ent);
	ent->setCastShadows(true);*/

	Ogre::Light* light = mSceneMgr->createLight("Light1");
	light->setType(Light::LT_POINT);
	light->setPosition(Vector3(7500, 1500/DATA_READER::getTileX() * 10 * 1.2 * 10 + 500, 1.0 + 7500));
	light->setDiffuseColour(1.0, 1.0, 1.0);
	light->setSpecularColour(1.0, 1.0, 1.0);
	//light = mSceneMgr->createLight("Light2");
	//light->setType(Light::LT_POINT);
	//light->setPosition(Vector3(-100, 150, -250));
	//light->setDiffuseColour(0, 1.0, 0);
	//light->setSpecularColour(0, 1.0, 0);

}

void BasicTutorial_00::createMainScene(void) 
{
	mSceneMgr = mSceneMgrArr[1];

	mSceneMgr->setSkyBox(true, "Examples/TrippySkyBox");

	// set our camera to orbit around the origin and show cursor
	// the names of the four materials we will use
	String matNames[] = {"Examples/OgreDance", "Examples/OgreParade", "Examples/OgreSpin", "Examples/OgreWobble"};

	for (unsigned int i = 0; i < 4; i++)
	{
		// create a standard plane entity
		Entity* ent = mSceneMgr->createEntity("Plane" + StringConverter::toString(i + 1), SceneManager::PT_PLANE);

		// attach it to a node, scale it, and position appropriately
		SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		node->setPosition(i % 2 ? 25 : -25, i / 2 ? -25 : 25, 0);
		node->setScale(0.25, 0.25, 0.25);
		node->attachObject(ent);

		ent->setMaterialName(matNames[i]);  // give it the material we prepared
	}
	return;
}



/*!
	Set up two viewport with createGameMainViewport and createGameBackLittleViewport.
*/
void BasicTutorial_00::createViewports(void)
{
	createMainMenuViewport();
}

/*!
	Call createGameMainCamera and createGameBackLittleCamera to setup two cameras and set camera_00 to be main.
*/
void BasicTutorial_00::createCamera(void) {
	createMainMenuCamera();
	createGameMainCamera();
	createGameBackLittleCamera();
	createGameRightLittleCamera();
	createGameLeftLittleCamera();
	createGameBackGroundCamera();
	createNextBlockCamera();
	mCameraMan = mCameraManArr[0];
	//mCameraMan = mCameraManArr[1];
}

/*!
	Call createGameScene and createScene_01 to create two scenes.
*/
void BasicTutorial_00::createScene( void ) {
	createMainScene();
	mSceneMgr = mSceneMgrArr[1]; // active SceneManager
	//mSceneMgr = mSceneMgrArr[1]; // active SceneManager
}

bool BasicTutorial_00::keyPressed( const OIS::KeyEvent &arg )
{
	bool flg = BaseApplication::keyPressed(arg);
	//bool flg = true;
	if(PlayEnable){
		if (arg.key == OIS::KC_W)
			moveDir[0] = true;
		if (arg.key == OIS::KC_S)
			moveDir[1] = true;
		if (arg.key == OIS::KC_A)
			moveDir[2] = true;
		if (arg.key == OIS::KC_D)
			moveDir[3] = true;
		if (arg.key == OIS::KC_UP)
			blockMove = BlockManager::MOVE_UP;
		if (arg.key == OIS::KC_DOWN)
			blockMove = BlockManager::MOVE_DOWN;
		if (arg.key == OIS::KC_LEFT)
			blockMove = BlockManager::MOVE_LEFT;
		if (arg.key == OIS::KC_RIGHT)
			blockMove = BlockManager::MOVE_RIGHT;
		if (arg.key == OIS::KC_SPACE){
			mSoundMgr->playAudio( audioId_speed, false );
			blockMove = BlockManager::MOVE_SPEEDUP;
		}
		if (arg.key == OIS::KC_Z)
			blockRotate = Block::ROTATE_X;
		if (arg.key == OIS::KC_X)
			blockRotate = Block::ROTATE_Y;
		if (arg.key == OIS::KC_C)
			blockRotate = Block::ROTATE_Z;
	}
	if (arg.key == OIS::KC_F1){
		switch(mGameStage){
			case GameStage_Play:
				PlayEnable=false;
				mTrayMgr->moveWidgetToTray("Resume_Game", OgreBites::TL_CENTER);
				mTrayMgr->moveWidgetToTray("Restart", OgreBites::TL_CENTER);
				mTrayMgr->moveWidgetToTray("Exit_toMain", OgreBites::TL_CENTER);
				Button_All[9]->show();		
				Button_All[7]->show();
				Button_All[8]->show();
				mGameStage = GameStage_LittleMenu;
				vp[1]->setOverlaysEnabled(true);
				removeScore_Time();
				break;
			case GameStage_LittleMenu:
				PlayEnable=true;
				mTrayMgr->removeWidgetFromTray("Resume_Game");	
				mTrayMgr->removeWidgetFromTray("Restart");
				mTrayMgr->removeWidgetFromTray("Exit_toMain");
				Button_All[9]->hide();	
				Button_All[7]->hide();
				Button_All[8]->hide();
				mGameStage = GameStage_Play;
				showScore_Time();
				vp[1]->setOverlaysEnabled(false);
				break;
		}
	}
	return flg;
}



bool BasicTutorial_00::keyReleased( const OIS::KeyEvent &arg )
{
	bool flg = BaseApplication::keyReleased(arg);
	//bool flg = true;
	if (arg.key == OIS::KC_W)
		moveDir[0] = false;
	if (arg.key == OIS::KC_S)
		moveDir[1] = false;
	if (arg.key == OIS::KC_A)
		moveDir[2] = false;
	if (arg.key == OIS::KC_D)
		moveDir[3] = false;
	return flg;
}

bool BasicTutorial_00::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
	//bool flg = BaseApplication::mousePressed(arg,id);
	if(id == OIS::MouseButtonID::MB_Left){
		check_Button_All();
	}
	return true;
}

void BasicTutorial_00::check_Button_All(void){
	for(int i=0;i<23;i++){
		if(Button_On(i)){
			Button_AllHit(Button_All[i]);
			mSoundMgr->playAudio( audioId_click, false );
			break;
		}
	}
}

bool BasicTutorial_00::Button_On(int i){
	if(Button_All[i]->isCursorOver(Button_All[i]->getOverlayElement(),
			 Ogre::Vector2(mTrayMgr->getCursorContainer()->getLeft(),
			 mTrayMgr->getCursorContainer()->getTop()), 0)){
		return true;
	}
	return false;
}

void BasicTutorial_00::Button_AllHit(OgreBites::Button* b){
	if(b->getName() == "Start"){
		if(!resolve){
			mGameStage = GameStage_GameChoice;
			//mTrayMgr->removeWidgetFromTray("Back", OgreBites::TL_RIGHT);
			mTrayMgr->removeWidgetFromTray("Start");
			mTrayMgr->removeWidgetFromTray("About");
			mTrayMgr->removeWidgetFromTray("Exit");
			Button_All[0]->hide();
			Button_All[1]->hide();
			Button_All[2]->hide();
			mTrayMgr->moveWidgetToTray("Unlimit", OgreBites::TL_CENTER);
			mTrayMgr->moveWidgetToTray("TimeLimit", OgreBites::TL_CENTER);
			mTrayMgr->moveWidgetToTray("Collect", OgreBites::TL_CENTER);
			mTrayMgr->moveWidgetToTray("AI_type", OgreBites::TL_CENTER);
			Button_All[4]->show();
			Button_All[5]->show();
			Button_All[6]->show();
			Button_All[22]->show();
			//mWindow->removeViewport(5);
			//createGameScene();
			//PlayEnable=true;
		}		
	}
	if(b->getName() == "About"){
		mGameStage = GameStage_About;
		mTrayMgr->removeWidgetFromTray("Start");
		mTrayMgr->removeWidgetFromTray("About");
		mTrayMgr->removeWidgetFromTray("Exit");
		Button_All[0]->hide();
		Button_All[1]->hide();
		Button_All[2]->hide();
		/*創造About視窗*/
		mTrayMgr->moveWidgetToTray("Back_toMain", OgreBites::TL_BOTTOM);
		Button_All[3]->show();
	}
	if(b->getName() == "Exit"){
		mShutDown = true;
	}
	if(b->getName() == "Back_toMain"){
		mGameStage = GameStage_MainMenu;
		mTrayMgr->removeWidgetFromTray("Back_toMain");
		Button_All[3]->hide();
		mTrayMgr->moveWidgetToTray("Start", OgreBites::TL_RIGHT);
		mTrayMgr->moveWidgetToTray("About", OgreBites::TL_RIGHT);
		mTrayMgr->moveWidgetToTray("Exit", OgreBites::TL_RIGHT);
		Button_All[0]->show();
		Button_All[1]->show();
		Button_All[2]->show();
		/*移除About視窗*/
	}
	if(b->getName() == "Unlimit" || b->getName() == "AI_type"){
		mTrayMgr->removeWidgetFromTray("Unlimit");
		mTrayMgr->removeWidgetFromTray("TimeLimit");
		mTrayMgr->removeWidgetFromTray("Collect");
		mTrayMgr->removeWidgetFromTray("AI_type");
		Button_All[4]->hide();
		Button_All[5]->hide();
		Button_All[6]->hide();
		Button_All[22]->hide();
		mWindow->removeViewport(7);
		showScore_Time();
		createPlayScreen();
		PlayEnable = true;
		mGameStage = GameStage_Play;
		mGameType = GameType_Unlimit;
		if(b->getName() == "AI_type"){
			mGameType = GameType_AI_type;
		}
		showScore_Time();
		score=0;
	}
	if(b->getName() == "TimeLimit"){
		mGameStage = GameStage_TimeLimit;
		mTrayMgr->removeWidgetFromTray("Unlimit");
		mTrayMgr->removeWidgetFromTray("TimeLimit");
		mTrayMgr->removeWidgetFromTray("Collect");
		mTrayMgr->removeWidgetFromTray("AI_type");
		Button_All[4]->hide();
		Button_All[5]->hide();
		Button_All[6]->hide();
		Button_All[22]->hide();
		mTrayMgr->moveWidgetToTray("TimeLimit_Most", OgreBites::TL_CENTER);
		mTrayMgr->moveWidgetToTray("TimeLimit_Collect", OgreBites::TL_CENTER);
		Button_All[10]->show();
		Button_All[11]->show();
	}
	if(b->getName() == "Collect"){
		mGameStage = GameStage_Collect;
		mTrayMgr->removeWidgetFromTray("Unlimit");
		mTrayMgr->removeWidgetFromTray("TimeLimit");
		mTrayMgr->removeWidgetFromTray("Collect");
		mTrayMgr->removeWidgetFromTray("AI_type");
		Button_All[4]->hide();
		Button_All[5]->hide();
		Button_All[6]->hide();
		Button_All[22]->hide();
		mTrayMgr->moveWidgetToTray("Collect_state_1", OgreBites::TL_CENTER);
		mTrayMgr->moveWidgetToTray("Collect_state_2", OgreBites::TL_CENTER);
		mTrayMgr->moveWidgetToTray("Collect_state_3", OgreBites::TL_CENTER);
		mTrayMgr->moveWidgetToTray("Collect_state_4", OgreBites::TL_CENTER);
		mTrayMgr->moveWidgetToTray("Collect_state_5", OgreBites::TL_CENTER);
		Button_All[17]->show();
		Button_All[18]->show();
		Button_All[19]->show();
		Button_All[20]->show();
		Button_All[21]->show();
	}
	if(b->getName() == "Restart"){
		mSceneMgrArr[0]->clearScene();
		mSoundMgr->stopAllAudio();
		createGameScene();
		if(mGameStage == GameStage_LittleMenu){
			mTrayMgr->removeWidgetFromTray("Resume_Game");
			Button_All[9]->hide();		
		}
		mTrayMgr->removeWidgetFromTray("Restart");
		mTrayMgr->removeWidgetFromTray("Exit_toMain");
		Button_All[7]->hide();
		Button_All[8]->hide();
		mGameStage = GameStage_Play;
		PlayEnable=true;
		showScore_Time();
		vp[1]->setOverlaysEnabled(false);
	}
	if(b->getName() == "Exit_toMain"){
		if(mGameStage == GameStage_LittleMenu){
			mTrayMgr->removeWidgetFromTray("Resume_Game");
			Button_All[9]->hide();		
		}
		mTrayMgr->removeWidgetFromTray("Restart");
		mTrayMgr->removeWidgetFromTray("Exit_toMain");
		Button_All[7]->hide();
		Button_All[8]->hide();
		mTrayMgr->moveWidgetToTray("Start", OgreBites::TL_RIGHT);
		mTrayMgr->moveWidgetToTray("About", OgreBites::TL_RIGHT);
		mTrayMgr->moveWidgetToTray("Exit", OgreBites::TL_RIGHT);
		Button_All[0]->show();
		Button_All[1]->show();
		Button_All[2]->show();
		removePlayScreen();
		/*移除所有遊戲viewport*/		
		PlayEnable=false;
		vp[1]->setOverlaysEnabled(false);
		mGameStage = GameStage_MainMenu;
		mGameType = GameType_None;
	}
	if(b->getName() == "Resume_Game"){
		mTrayMgr->removeWidgetFromTray("Resume_Game");
		mTrayMgr->removeWidgetFromTray("Restart");
		mTrayMgr->removeWidgetFromTray("Exit_toMain");
		Button_All[9]->hide();
		Button_All[7]->hide();
		Button_All[8]->hide();
		PlayEnable=true;
		mGameStage = GameStage_Play;
		showScore_Time();
		vp[1]->setOverlaysEnabled(false);
	}
	if(b->getName() == "TimeLimit_Most"){
		mTrayMgr->removeWidgetFromTray("TimeLimit_Most");
		mTrayMgr->removeWidgetFromTray("TimeLimit_Collect");
		Button_All[10]->hide();
		Button_All[11]->hide();
		mGameStage = GameStage_Play;
		mGameType = GameType_TimeLimit_Most;
	}
	if(b->getName() == "TimeLimit_Collect"){
		mGameStage = GameStage_TimeLimit_Collect;
		mTrayMgr->removeWidgetFromTray("TimeLimit_Most");
		mTrayMgr->removeWidgetFromTray("TimeLimit_Collect");
		Button_All[10]->hide();
		Button_All[11]->hide();
		mTrayMgr->moveWidgetToTray("TimeLimit_state_1", OgreBites::TL_CENTER);
		mTrayMgr->moveWidgetToTray("TimeLimit_state_2", OgreBites::TL_CENTER);
		mTrayMgr->moveWidgetToTray("TimeLimit_state_3", OgreBites::TL_CENTER);
		mTrayMgr->moveWidgetToTray("TimeLimit_state_4", OgreBites::TL_CENTER);
		mTrayMgr->moveWidgetToTray("TimeLimit_state_5", OgreBites::TL_CENTER);
		Button_All[12]->show();
		Button_All[13]->show();
		Button_All[14]->show();
		Button_All[15]->show();
		Button_All[16]->show();
	}
	if(b->getName() == "TimeLimit_state_1"){
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_1");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_2");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_3");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_4");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_5");
		Button_All[12]->hide();
		Button_All[13]->hide();
		Button_All[14]->hide();
		Button_All[15]->hide();
		Button_All[16]->hide();
		mWindow->removeViewport(7);
		createPlayScreen();
		PlayEnable = true;
		mGameStage = GameStage_Play;
		mGameType = GameType_TimeLimit_Collect;
		showScore_Time();
	}
	if(b->getName() == "TimeLimit_state_2"){
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_1");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_2");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_3");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_4");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_5");
		Button_All[12]->hide();
		Button_All[13]->hide();
		Button_All[14]->hide();
		Button_All[15]->hide();
		Button_All[16]->hide();
		mWindow->removeViewport(7);
		createPlayScreen();
		PlayEnable = true;
		mGameStage = GameStage_Play;
		mGameType = GameType_TimeLimit_Collect;
		showScore_Time();
	}
	if(b->getName() == "TimeLimit_state_3"){
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_1");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_2");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_3");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_4");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_5");
		Button_All[12]->hide();
		Button_All[13]->hide();
		Button_All[14]->hide();
		Button_All[15]->hide();
		Button_All[16]->hide();
		mWindow->removeViewport(7);
		createPlayScreen();
		PlayEnable = true;
		mGameStage = GameStage_Play;
		mGameType = GameType_TimeLimit_Collect;
		showScore_Time();
	}
	if(b->getName() == "TimeLimit_state_4"){
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_1");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_2");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_3");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_4");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_5");
		Button_All[12]->hide();
		Button_All[13]->hide();
		Button_All[14]->hide();
		Button_All[15]->hide();
		Button_All[16]->hide();
		mWindow->removeViewport(7);
		createPlayScreen();
		PlayEnable = true;
		mGameStage = GameStage_Play;
		mGameType = GameType_TimeLimit_Collect;
		showScore_Time();
	}
	if(b->getName() == "TimeLimit_state_5"){
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_1");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_2");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_3");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_4");
		mTrayMgr->removeWidgetFromTray("TimeLimit_state_5");
		Button_All[12]->hide();
		Button_All[13]->hide();
		Button_All[14]->hide();
		Button_All[15]->hide();
		Button_All[16]->hide();
		mWindow->removeViewport(7);
		createPlayScreen();
		PlayEnable = true;
		mGameStage = GameStage_Play;
		mGameType = GameType_TimeLimit_Collect;
		showScore_Time();
	}
	if(b->getName() == "Collect_state_1"){
		mTrayMgr->removeWidgetFromTray("Collect_state_1");
		mTrayMgr->removeWidgetFromTray("Collect_state_2");
		mTrayMgr->removeWidgetFromTray("Collect_state_3");
		mTrayMgr->removeWidgetFromTray("Collect_state_4");
		mTrayMgr->removeWidgetFromTray("Collect_state_5");
		Button_All[17]->hide();
		Button_All[18]->hide();
		Button_All[19]->hide();
		Button_All[20]->hide();
		Button_All[21]->hide();
		mWindow->removeViewport(7);
		createPlayScreen();
		PlayEnable = true;
		mGameStage = GameStage_Play;
		mGameType = GameType_Collect;
		showScore_Time();
	}
	if(b->getName() == "Collect_state_2"){
		mTrayMgr->removeWidgetFromTray("Collect_state_1");
		mTrayMgr->removeWidgetFromTray("Collect_state_2");
		mTrayMgr->removeWidgetFromTray("Collect_state_3");
		mTrayMgr->removeWidgetFromTray("Collect_state_4");
		mTrayMgr->removeWidgetFromTray("Collect_state_5");
		Button_All[17]->hide();
		Button_All[18]->hide();
		Button_All[19]->hide();
		Button_All[20]->hide();
		Button_All[21]->hide();
		mWindow->removeViewport(7);
		createPlayScreen();
		PlayEnable = true;
		mGameStage = GameStage_Play;
		mGameType = GameType_Collect;
		showScore_Time();
	}
	if(b->getName() == "Collect_state_3"){
		mTrayMgr->removeWidgetFromTray("Collect_state_1");
		mTrayMgr->removeWidgetFromTray("Collect_state_2");
		mTrayMgr->removeWidgetFromTray("Collect_state_3");
		mTrayMgr->removeWidgetFromTray("Collect_state_4");
		mTrayMgr->removeWidgetFromTray("Collect_state_5");
		Button_All[17]->hide();
		Button_All[18]->hide();
		Button_All[19]->hide();
		Button_All[20]->hide();
		Button_All[21]->hide();
		mWindow->removeViewport(7);
		createPlayScreen();
		PlayEnable = true;
		mGameStage = GameStage_Play;
		mGameType = GameType_Collect;
		showScore_Time();
	}
	if(b->getName() == "Collect_state_4"){
		mTrayMgr->removeWidgetFromTray("Collect_state_1");
		mTrayMgr->removeWidgetFromTray("Collect_state_2");
		mTrayMgr->removeWidgetFromTray("Collect_state_3");
		mTrayMgr->removeWidgetFromTray("Collect_state_4");
		mTrayMgr->removeWidgetFromTray("Collect_state_5");
		Button_All[17]->hide();
		Button_All[18]->hide();
		Button_All[19]->hide();
		Button_All[20]->hide();
		Button_All[21]->hide();
		mWindow->removeViewport(7);
		createPlayScreen();
		PlayEnable = true;
		mGameStage = GameStage_Play;
		mGameType = GameType_Collect;
		showScore_Time();
	}
	if(b->getName() == "Collect_state_5"){	
		mTrayMgr->removeWidgetFromTray("Collect_state_1");
		mTrayMgr->removeWidgetFromTray("Collect_state_2");
		mTrayMgr->removeWidgetFromTray("Collect_state_3");
		mTrayMgr->removeWidgetFromTray("Collect_state_4");
		mTrayMgr->removeWidgetFromTray("Collect_state_5");
		Button_All[17]->hide();
		Button_All[18]->hide();
		Button_All[19]->hide();
		Button_All[20]->hide();
		Button_All[21]->hide();
		mWindow->removeViewport(7);
		createPlayScreen();
		PlayEnable = true;
		mGameStage = GameStage_Play;
		mGameType = GameType_Collect;
		showScore_Time();
	}
}

void BasicTutorial_00::createPlayScreen(void){
	createGameScene();
	createGameMainViewport();
	createGameBackLittleViewport();
	createGameRightLittleViewport();
	createGameLefttLittleViewport();
	createGameBackGroundViewport();
	createNextBlockViewport();
	score=0;
	time_m = 0;
	time_s = 0;
	time_ms = 0.0;
	time_for_All = 0.0;
	score = 0;
}

void BasicTutorial_00::removePlayScreen(void){
	mWindow->removeViewport(2);
	mWindow->removeViewport(3);
	mWindow->removeViewport(4);
	mWindow->removeViewport(5);
	mWindow->removeViewport(1);
	mWindow->removeViewport(6);
	mSceneMgrArr[0]->clearScene();
	createMainMenuViewport();
	mSoundMgr->stopAudio(audioId_back);
	mSoundMgr->stopAllAudio();
}



void BasicTutorial_00::showScore_Time(void){
	if(mGameType==GameType_TimeLimit_Collect || mGameType==GameType_TimeLimit_Most || mGameType==GameType_Collect){
		mTrayMgr->moveWidgetToTray("Time_Show_Label", OgreBites::TL_TOPLEFT);
		mTrayMgr->moveWidgetToTray("Time_Value_Label", OgreBites::TL_TOPLEFT);
		Time_Show->show();
		Time_Value_Show->show();
	}
	if(mGameType==GameType_TimeLimit_Most || mGameType==GameType_Unlimit  || mGameType==GameType_AI_type){
		mTrayMgr->moveWidgetToTray("Score_Show_Label", OgreBites::TL_TOPLEFT);
		mTrayMgr->moveWidgetToTray("Score_Value_Label", OgreBites::TL_TOPLEFT);
		Score_Show->show();
		Score_Value_Show->show();
	}


}

void BasicTutorial_00::removeScore_Time(void){
	if(mGameType==GameType_TimeLimit_Collect || mGameType==GameType_TimeLimit_Most || mGameType==GameType_Collect){
		mTrayMgr->removeWidgetFromTray("Time_Show_Label");
		mTrayMgr->removeWidgetFromTray("Time_Value_Label");
		Time_Show->hide();
		Time_Value_Show->hide();
	}
	if(mGameType==GameType_TimeLimit_Most || mGameType==GameType_Unlimit || mGameType==GameType_AI_type){
		mTrayMgr->removeWidgetFromTray("Score_Show_Label");
		mTrayMgr->removeWidgetFromTray("Score_Value_Label");
		Score_Show->hide();
		Score_Value_Show->hide();
		
	}
}

String BasicTutorial_00::value_int_string(const int& a){
	Ogre::String msg;
	std::stringstream out0;
	out0 << a;
	msg = out0.str();
	return msg;
}

void BasicTutorial_00::updateTime(const Ogre::FrameEvent& evt){
	Ogre::String msg;
	time_for_All+=evt.timeSinceLastFrame;
	time_ms=((int)(time_for_All*100.0))%100;
	time_m=time_for_All/60.0;
	time_s=time_for_All-time_m*60;
	if(time_s < 10){
		msg = msg+ value_int_string(time_m)+" : 0" + value_int_string(time_s);
	}
	else{
		msg = msg+ value_int_string(time_m)+": " + value_int_string(time_s);
	}
	if(time_ms<10){
		msg = msg+" : 0"+value_int_string(time_ms);
	}
	else{
		msg = msg+" : "+value_int_string(time_ms);
	}
	Time_Value_Show->setCaption(msg);
}

void BasicTutorial_00::updateScore(const Ogre::FrameEvent& evt){
	score+=blockMgr->getScore();
	Ogre::String msg = value_int_string(score);
	Score_Value_Show->setCaption(msg);
}	

bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
	bool flg = Ogre::FrameListener::frameStarted(evt);
	if(PlayEnable){
		mCamera = mCameraManArr[0]->getCamera();
		Vector3 currentPos = mCamera->getPosition();
		Real time  = evt.timeSinceLastFrame;
		Real speed = mCameraManArr[0]->getTopSpeed() * time;
		Real Angle_Radius=sqrt(currentPos.x*currentPos.x+currentPos.z*currentPos.z);
		Real Angle = asin(currentPos.z/Angle_Radius) * 180.0 / PI;
		Real y = currentPos.y;
		if(currentPos.x<0.0){
			Angle = 180.0 - Angle;
		}
		if(Angle < 0.0){
			Angle+=360.0;
		}
		if(moveDir[0]){
			Vector3 moveDirection = (currentPos - Vector3(7500,500,7500)).normalisedCopy();
			mCamera->move(- moveDirection * speed);
		}
		if(moveDir[1]){
			Vector3 moveDirection = (currentPos - Vector3(7500,500,7500)).normalisedCopy();
			mCamera->move( moveDirection * speed);
		}
		if(moveDir[2]){
			Vector3 moveDirection = (currentPos - Vector3(7500,500,7500)).normalisedCopy().crossProduct(mCamera->getUp().normalisedCopy());
			mCamera->move( moveDirection * speed);
		}
		if(moveDir[3]){
			Vector3 moveDirection = (currentPos - Vector3(7500,500,7500)).normalisedCopy().crossProduct(mCamera->getUp().normalisedCopy());
			mCamera->move(- moveDirection * speed);
		}
		mCamera->setPosition(mCamera->getPosition().x,y,mCamera->getPosition().z);

		currentPos = mCamera->getPosition();
		Real distance = (currentPos - Vector3(7500,500,7500)).length();
		//printf("%f\n",distance);
		if(distance < 2000)
			mCamera->setPosition(2000 * (currentPos - Vector3(7500,500,7500)).normalisedCopy() + Vector3(7500,500,7500));

		mCamera->lookAt(7500,500,7500);

		//currentPos = mCamera->getPosition();
		//currentPos.reflect(Vector3::UNIT_Y);
		//Real y = currentPos.y;

		//mCameraArr[1]->setPosition(Vector3(-currentPos.x,currentPos.y,-currentPos.z));
		//mCameraArr[1]->lookAt(0,0,0);

		blockMgr->moveBlock(blockMove);
		blockMgr->rotateBlock(blockRotate);
		blockMove = BlockManager::MOVE_NONE;
		blockRotate = Block::ROTATE_NONE;
		blockMgr->update(evt);
		if(blockMgr->isEnd()){
			Ogre::LogManager::getSingletonPtr()->logMessage("GAME OVER");
			mShutDown = true;
		}
		updateTime(evt);
		updateScore(evt);
	}
	if(resolve){
		mTrayMgr->removeWidgetFromTray("Start");
		mTrayMgr->removeWidgetFromTray("About");
		mTrayMgr->removeWidgetFromTray("Exit");
		mTrayMgr->moveWidgetToTray("Start", OgreBites::TL_RIGHT);
		mTrayMgr->moveWidgetToTray("About", OgreBites::TL_RIGHT);
		mTrayMgr->moveWidgetToTray("Exit", OgreBites::TL_RIGHT);
		time_resolve+=evt.timeSinceLastFrame;		
		if(time_resolve>0.5)
			resolve=false;
	}
	for(int i=0;i<23;i++){
		if(Button_On(i)){
			if(button_in){
			}
			else{
				mSoundMgr->playAudio( audioId_button_on, false );
				button_in=true;
			}
			break;
		}
		if(i==21){
			button_in=false;
		}
	}
	return flg;
}


int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
