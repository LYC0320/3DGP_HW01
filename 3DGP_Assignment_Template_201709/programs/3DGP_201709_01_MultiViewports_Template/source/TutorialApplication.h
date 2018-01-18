//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
/*!
\brief 3D Game Programming
\n
My Name: AA BB CC
\n
My ID: 0123456789
\n
My Email: aaa@cs.nctu.edu.tw
\n Date: 2017/09/24

This is an assignment of 3D Game Programming
*/

////////////////////////////////////////
// You can delete everything and start from scratch.
////////////////////////////////////////

#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include "BaseApplication.h"

class BasicTutorial_00 : public BaseApplication
{
public:
	BasicTutorial_00(void);
	virtual void createViewports(void);
	virtual void createScene(void);
	virtual void createCamera(void);
	virtual void chooseSceneManager(void);
    //
    virtual bool frameStarted(const Ogre::FrameEvent& evt);
    //
    // Add your own stuff.
    //
protected:
	/*!
	\brief Create a viewport

	Create a viewport for the entire screen.

	\return The sum of two integers.
	*/
	void createViewport_00(void);
	void createViewport_01(void);
	//
	void createCamera_00();
	void createCamera_01();

	void createScene_00();
	void createScene_01();
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    //
    // Add your own stuff.
    //
	void createPlane(void);
	void createPlane87(void);
	void createCube(void);
	void createWall(void);
	void createCube2(void);
	void movePenguin(float);
	void createLight(void);
	void createLight2(void);
	void toggleView(void);
	void changeViewPosition(void);
	void collisionTest(void);
	void createBall(void);

protected:

	

    Ogre::Viewport* mViewportArr[8];
	Ogre::Camera* mCameraArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	OgreBites::SdkCameraMan* mCameraManArr[8];
	Ogre::SceneNode* ballSceneNode[175];
	Ogre::Entity* ballEntity[175];
	Ogre::Vector3 ballPosition[175];
	
    //
    // Add your own stuff.
    //
};


#endif // #ifndef __BasicTutorial_00_h_