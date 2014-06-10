//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
/*!
\brief 3D Game Programming
\n
My Name: Wei-Sheng Zeng
\n
My ID: 9917144
\n
My Email: cvs5689@gmail.com

This is an assignment of 3D Game Programming

*/

#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include "BaseApplication.h"
#include "BlockManager.h"
#include "SoundManager.h"

typedef enum GameStage {
	GameStage_MainMenu,
	GameStage_About,
	GameStage_GameChoice,
	GameStage_TimeLimit,
	GameStage_Collect,
	GameStage_TimeLimit_Collect,
	GameStage_Play,
	GameStage_LittleMenu,
};

typedef enum GameType {
	GameType_None,
	GameType_Unlimit,
	GameType_TimeLimit_Most,
	GameType_TimeLimit_Collect,
	GameType_Collect,
	GameType_AI_type
};

class BasicTutorial_00 : public BaseApplication
{
public:
	BasicTutorial_00(void);
	virtual bool frameStarted(const Ogre::FrameEvent& evt);
	virtual void createViewports(void);
	virtual void createScene(void);
	virtual void createCamera(void);
	virtual void chooseSceneManager(void);
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
private:
	/*!
	\brief Create a viewport

	Create a viewport for the entire screen.

	\return The sum of two integers.
	*/
	void createMainMenuViewport(void);
	void createGameMainViewport(void);
	void createGameBackLittleViewport(void);
	void createGameRightLittleViewport(void);
	void createGameLefttLittleViewport(void);
	void createGameBackGroundViewport(void);
	void createNextBlockViewport(void);
	//
	void createMainMenuCamera();
	void createGameMainCamera();
	void createGameBackLittleCamera();
	void createGameRightLittleCamera();
	void createGameLeftLittleCamera();
	void createGameBackGroundCamera();
	void createNextBlockCamera();
	//
	void createGameScene();
	void createMainScene();

	void resetGameCamera();

	void createPlayScreen();
	void removePlayScreen();

	void showScore_Time();
	void removeScore_Time();

	void Button_AllHit(OgreBites::Button* b);

	void check_Button_All();
	bool Button_On(int i);

	Ogre::String value_int_string(const int& a);

	void updateTime(const Ogre::FrameEvent& evt);
	void updateScore(const Ogre::FrameEvent& evt);

	void setOffBackgroundSmoke(Ogre::SceneNode *fNode, const Ogre::Vector3 &pos);
	void setOffFirework(Ogre::SceneNode *fNode, const Ogre::Vector3 &pos);
	void setOffSnow(Ogre::SceneNode *fNode, const Ogre::Vector3 &pos);
	void setOffRain(Ogre::SceneNode *fNode, const Ogre::Vector3 &pos);
	void setOffSwarm(Ogre::SceneNode *fNode, const Ogre::Vector3 &pos);


	/** To initial the setting of OpenAL and to load the music in the audio buffer to play */
	void setupSound();


	Ogre::Camera* mCameraArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	OgreBites::SdkCameraMan* mCameraManArr[8];
	Ogre::Real time_resolve;
	bool moveDir[4];
	int	 blockMove;
	bool resolve;
	bool PlayEnable;
	int	 blockRotate;
	int score;
	int time_m;
	int time_s;
	int time_ms;

	unsigned int audioId_back;
	unsigned int audioId_speed;
	unsigned int audioId_click;
	unsigned int audioId_button_on;

	bool button_in;

	Ogre::Real time_for_All;
	BlockManager* blockMgr;
	Ogre::Viewport* vp[5];

	GameStage mGameStage;
	GameType mGameType;

	SoundManager* mSoundMgr;

};

#endif // #ifndef __BasicTutorial_00_h_