////////////////////////////////////////
//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
////////////////////////////////////////
// Student Name:
// Student ID:
// Student Email:
//
////////////////////////////////////////
// You can delete everything and start from scratch.
////////////////////////////////////////

#include "TutorialApplication.h"
#include "BasicTools.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace Ogre;

const float PI = 3.141592654;
const float speed = 100;
float F;

float smallBallMass = 40;
float bigBallMass = 50;

float cosBall;

int ballNum = 175;

SceneNode *penguinSeneNode;
SceneNode *bigBallSceneNode;
SceneNode *smallBallSceneNode;
SceneNode *planeSceneNode;
SceneNode *testSceneNode;
SceneNode *testSceneNode2;

Ogre::Vector3 acceleration = Vector3(0.0, 20.8, 0.0);
Ogre::Vector3 velocity = Vector3(0.0, 0.0, 0.0);
Ogre::Vector3 position = Vector3(0, 20, 0);

Ogre::Vector3 bigballPosition = Vector3(-150, 0, 400);
Ogre::Vector3 smallballPosition = Vector3(400, 0, 400);
Ogre::Vector3 bGravity = Vector3(0, -980, 0);
Ogre::Vector3 sGravity = Vector3(0, -980, 0);
Ogre::Vector3 bigballVelocity = Vector3(.0, .0, .0);
Ogre::Vector3 smallballVelocity = Vector3(.0, .0, .0);

Ogre::Vector3 ballToBallVector = Vector3(.0, .0, .0);

Ogre::Vector3 smallballAcceleration = Vector3(.0, .0, .0);

bool down = false;
bool move = false;
bool change = false;
bool change2 = false;

bool test = true;

Entity *bigBallEntity;
Entity *smallBallEntity;

BasicTutorial_00::BasicTutorial_00(void)
{
	

}

void BasicTutorial_00::chooseSceneManager()
{
	mSceneMgrArr[0] = mRoot
		->createSceneManager(ST_GENERIC, "primary");
    //
    // add your own stuff
    //

	mSceneMgrArr[2] = mRoot->createSceneManager(ST_GENERIC, "third");
}

void BasicTutorial_00::createCamera_00(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(120,300,600));
	mCamera->lookAt(Ogre::Vector3(0,0,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createCamera_01(void)
{
	// add your own stuff
	mSceneMgr87 = mSceneMgrArr[2];
	mCamera = mCameraArr[1] = mSceneMgr87->createCamera("SecondCam");
	mCamera->setPosition(120, 300, 600);
	mCamera->lookAt(0, 0, 0.0);
}



void BasicTutorial_00::createViewport_00(void)
{

		mCamera = mCameraArr[0];

		Ogre::Viewport* vp = mWindow->addViewport(mCamera, 1);
		vp->setBackgroundColour(Ogre::ColourValue(0, 0.0, 1.0));
		mCamera->setAspectRatio(
			Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

		mViewportArr[0] = vp;
}

void BasicTutorial_00::createViewport_01(void)
{
    // add your own stuff

	mCamera = mCameraArr[1];

	Ogre::Viewport *vp2 = mWindow->addViewport(mCamera,2,0.7,0,0.3,0.3);
	vp2->setBackgroundColour(Ogre::ColourValue(1, 0, 0));
	mCamera->setAspectRatio(Ogre::Real(vp2->getActualWidth()) / Ogre::Real(vp2->getActualHeight()));

	mViewportArr[1] = vp2;
}

void BasicTutorial_00::createScene_00(void) 
{
	mSceneMgr = mSceneMgrArr[0];

    // add your own stuff

	Entity *penguin = mSceneMgr->createEntity("penguin", "penguin.mesh");
	SceneNode *snode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	snode->attachObject(penguin);
	snode->setPosition(position);
	snode->setOrientation(Ogre::Quaternion(1,0,0));
	snode->setScale(Ogre::Vector3(1.3,1.8,1.3));
	penguinSeneNode = snode;

	Entity *penguin2 = mSceneMgr->createEntity("penguin2", "penguin.mesh");
	SceneNode *snode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	snode2->attachObject(penguin2);
	snode2->setPosition(Ogre::Vector3(150,20,0));
	snode2->setOrientation(Ogre::Quaternion(1,0,-1,0));
	snode2->setScale(Ogre::Vector3(0.5,0.5,0.5));

	createPlane();
	createCube();
	createWall();
	createCube2();
	createLight();
	createBall();

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

	Entity *sphere5 = mSceneMgr->createEntity("sphere2", Ogre::SceneManager::PT_SPHERE);
	SceneNode *snode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	snode3->attachObject(sphere5);
	snode3->setPosition(bigballPosition);
	snode3->setScale(1, 1, 1);
	sphere5->setMaterialName("Examples/yellow");

	bigBallSceneNode = snode3;
	
	Entity *sphere6 = mSceneMgr->createEntity("sphere3", Ogre::SceneManager::PT_SPHERE);
	SceneNode *snode4 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	snode4->attachObject(sphere6);
	snode4->setPosition(Vector3(400, 30, 400));
	snode4->setScale(.2, .2, .2);

	bigBallEntity = sphere5;
	smallBallEntity = sphere6;
	smallBallSceneNode = snode4;

	Entity *sphere7 = mSceneMgr->createEntity("sphere4", Ogre::SceneManager::PT_SPHERE);
	SceneNode *snode5 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	snode5->attachObject(sphere7);
	snode5->setPosition(600, 0, 600);

	Entity *cylinder = mSceneMgr->createEntity("cylinder", "column.mesh");
	SceneNode *snode6 = snode5->createChildSceneNode();
	snode6->attachObject(cylinder);
	snode6->setPosition(0, 0, 0);
	snode6->setScale(1, 1, 1);

	Entity *penguin3 = mSceneMgr->createEntity("penguin3", "penguin.mesh");
	SceneNode *snode7 = snode6->createChildSceneNode();
	snode7->attachObject(penguin3);
	snode7->setPosition(0, 400, 0);

	testSceneNode = snode5;
	testSceneNode2 = snode6;
}

void BasicTutorial_00::createScene_01(void) 
{
    // add your own stuff
	mSceneMgr87 = mSceneMgrArr[2];
	mSceneMgr87->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	createPlane87();
	createLight2();

	Entity *ball = mSceneMgr87->createEntity("sphere", Ogre::SceneManager::PT_SPHERE);
	SceneNode *snode = mSceneMgr87->getRootSceneNode()->createChildSceneNode();
	snode->attachObject(ball);
	snode->setPosition(50, 50, 0);
	snode->setScale(1.5,2,1.2);
}

void BasicTutorial_00::createViewports(void)
{
    //Do not modify
	createViewport_00();
	createViewport_01();
}

void BasicTutorial_00::createCamera(void) {
    //Do not modify
	createCamera_00();
	createCamera_01();
	mCameraMan = mCameraManArr[0];
	//mCameraMan = mCameraManArr[1];
}

void BasicTutorial_00::createScene( void ) {
    //Do not modify
	createScene_00();
	createScene_01();
	//mSceneMgr = mSceneMgrArr[0]; // active SceneManager
	//mSceneMgr = mSceneMgrArr[1]; // active SceneManager
    //
    mCamera = mCameraArr[0];
    //mCamera = mCameraArr[1];
}

//
// What is stored in the file for arg.key?
// ASCII code? If no, what is it?
//
// To find out the answer:
// Go to see the definition of KeyEvent
//
bool BasicTutorial_00::keyPressed( const OIS::KeyEvent &arg )
{
    bool flg = true;
    stringstream ss;
    ss << arg.key;
    String msg;
    ss >> msg;
	msg += ":*** keyPressed ***\n";
    Ogre::LogManager::getSingletonPtr()->logMessage( msg );

	if(arg.key == OIS::KC_U)
	{
		bigballVelocity.z = -speed;
		bigballVelocity.x = 0;
	}

	if (arg.key == OIS::KC_J)
	{
		bigballVelocity.z = speed;
		bigballVelocity.x = 0;
	}

	if (arg.key == OIS::KC_K) 
	{
		bigballVelocity.x = speed;
		bigballVelocity.z = 0;
	}

	if (arg.key == OIS::KC_H) 
	{
		bigballVelocity.x = -speed;
		bigballVelocity.z = 0;
	}
    
    if (arg.key == OIS::KC_C ) {
        
        //How to clear ss?
        ss.str("");
        ss.clear();
        
        //stringstream ss; // Second way

        // Third way?
        //=============

        // How to get camerea position?
        //-----------------------------
        //This is incorrect.
        //Vector3 pos = mCamera->getPosition();
        //-----------------------------
        Vector3 pos = mCameraMan->getCamera()->getPosition(); //Correct
        ss << std::fixed << std::setprecision(2) 
            << "CameraPosition:" 
            << pos.x << "\t" 
            << pos.y << "\t" 
            << pos.z << "\n";
        Ogre::LogManager::getSingletonPtr()
            ->logMessage( ss.str() );
        //
        ss.str("");
        ss.clear();
        Vector3 dir = mCameraMan->getCamera()->getDirection();
        ss << std::fixed << std::setprecision(2) 
            << "CameraDirection:" 
            << dir.x << "\t" 
            << dir.y << "\t" 
            << dir.z << "\n";
        Ogre::LogManager::getSingletonPtr()
            ->logMessage( ss.str() );
        //
    }

    if (arg.key == OIS::KC_1 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(98.14,	450.69,	964.20));
        mCameraMan->getCamera()
            ->setDirection(Vector3(-0.01,	-0.30,	-0.95));

        //98.14	450.69	964.20
        //-0.01	-0.30	-0.95
    }

    if (arg.key == OIS::KC_2 ) {
        // add your own stuff
		mCameraMan->getCamera()->setPosition(Vector3(-1463.00, 606.45, -513.24));
		mCameraMan->getCamera()->setDirection(Vector3(0.88, -0.47, 0.10));
        //-1463.00	606.45	-513.24
        //0.88	-0.47	0.10
    }

    if (arg.key == OIS::KC_3 ) {
        // add your own stuff
        //-1356.16	634.32	-964.51
        //0.71	-0.44	0.55
    }

    if (arg.key == OIS::KC_4 ) {
         // add your own stuff
        //40.39	155.23	251.20
        //-0.02	-0.41	-0.91
		changeViewPosition();
    }

    if (arg.key == OIS::KC_5 ) {
        // add your own stuff
        //19.94	822.63	30.79
        //0.00	-0.99	-0.11

		toggleView();
    }

    if (arg.key == OIS::KC_M ) {
        
       Camera *c_ptr = mCameraArr[0];
       mWindow->removeViewport(mViewportArr[0]->getZOrder());
	Ogre::Viewport* vp = mWindow->addViewport(
        c_ptr,
        0,
        0.15,
        0.55,
        0.45,
        0.3
        );
	vp->setBackgroundColour(Ogre::ColourValue(0,0.5,0.0));
	c_ptr->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
   //delete mViewportArr[0];    // program crashes
    mViewportArr[0] = vp;       // make sure to save the new pointer
    
    }

    if (arg.key == OIS::KC_N ) {
        // add your own stuff
		move = true;
    }

	if (arg.key == OIS::KC_B) 
	{
		move = false;
	}
    // Do not delete this line
    BaseApplication::keyPressed(arg);

    return flg;
}

//
// What is stored in the file for arg.key?
// ASCII code? If no, what is it?
// 
// To find out the answer:
// Go to see the definition of KeyEvent
//
bool BasicTutorial_00::keyReleased( const OIS::KeyEvent &arg )
{
    bool flg = true;
    stringstream ss;
    ss << arg.key;
    String msg;
    ss >> msg;
    msg += ":*** keyReleased ***\n";
    
    Ogre::LogManager::getSingletonPtr()->logMessage( msg );

    BaseApplication::keyReleased(arg);

    return flg;
}

bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
	bool flg = Ogre::FrameListener::frameStarted(evt);
    //
    // add your own stuff
    //
	//++frame;
	movePenguin(evt.timeSinceLastFrame);

	collisionTest();
	
	penguinSeneNode->yaw(Degree(.2));
	testSceneNode->yaw(Degree(.05));
	testSceneNode2->pitch(Degree(.05));

	bigballPosition = bigballPosition + bigballVelocity*evt.timeSinceLastFrame;
	
	bigBallSceneNode->setPosition(bigballPosition);
	for (int i = 0; i < ballNum; i++)
	{
		ballSceneNode[i]->setPosition(ballPosition[i]);

	}
    return flg;
}
int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}

void BasicTutorial_00::createPlane(void)
{
	Plane floor(Vector3::UNIT_Y, 0);
	MeshPtr mFloor = MeshManager::getSingleton().createPlane(
		"floor1",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		floor,
		1500,1500,
		20,20,
		true,
		1,
		5,5,
		Vector3::UNIT_Z	
	);

	Entity *floorEnt = mSceneMgr->createEntity("floor1");

	SceneNode *fnode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	
	fnode->attachObject(floorEnt);
	
	planeSceneNode = fnode;
}
void BasicTutorial_00::createPlane87(void)
{
	Plane floor(Vector3::UNIT_Y, 0);
	MeshPtr mFloor = MeshManager::getSingleton().createPlane(
		"floor2",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		floor,
		1500, 1500,
		20, 20,
		true,
		1,
		5,5,
		Vector3::UNIT_Z
	);

	Entity *floorEnt = mSceneMgr87->createEntity("floor2");

	SceneNode *fnode = mSceneMgr87->getRootSceneNode()->createChildSceneNode();

	fnode->attachObject(floorEnt);
}

void BasicTutorial_00::createWall(void)
{
	Plane wall(Vector3::UNIT_Z, -700);
	MeshPtr mWall = MeshManager::getSingleton().createPlane(
		"wall",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
		wall,
		1500,1500,
		20,20,
		true,
		1,
		5,5,
		Vector3::UNIT_Y
		);
	Entity *ent4 = mSceneMgr->createEntity("wall");
	ent4->setMaterialName("Examples/Rockwall");
	SceneNode *fnode4 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	fnode4->attachObject(ent4);

}

void BasicTutorial_00::createCube(void)
{
	float radius = 100.0;
	int cubeNum = 72;
	float x = radius;
	float z = 0;
	float h = 0;
	float angle = (2*PI/360.0)*5.0;
	float angle2 = 0;
	float rate = 0.013;

	String test;

	for(int i=0;i<cubeNum;i++)
	{
		String name;


		x = radius*cos(angle2);
		z = radius*sin(angle2);

		h = abs(radius*cos(angle2 + (2 * PI / 360.0)*120.0)*rate);

		genNameUsingIndex("c", i, name); 

		Entity *cube = mSceneMgr->createEntity(name, "cube.mesh");
		cube->setMaterialName("Examples/SphereMappedRustySteel");
		SceneNode *snode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		snode3->attachObject(cube);
		snode3->setPosition(x,0,z);
		snode3->setScale(0.05, h, 0.05);

		angle2 = angle2 + angle;
	}
}

void BasicTutorial_00::createCube2(void)
{
	float radius = 100.0;
	int cubeNum = 72;
	float h = 0;
	float angle = (2 * PI / 360.0)*5.0;
	float angle2 = 0;
	float rate = 0.007;
	float rotation = 0;

	for (int i = 0; i<cubeNum; i++)
	{
		String name;	

		h = abs(radius*cos(angle2)*rate);

		genNameUsingIndex("b", i, name);

		Entity *cube = mSceneMgr->createEntity(name, "cube.mesh");
		cube->setMaterialName("Examples/SphereMappedRustySteel");
		SceneNode *snode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		snode3->attachObject(cube);
		snode3->setPosition(i * 8 - 150, 35, 200);
		snode3->setScale(0.05, h, 0.05);
		snode3->setOrientation(Ogre::Quaternion(1, sin(angle2), 0, 0));

		angle2 = angle2 + angle;
	}
}

void BasicTutorial_00::movePenguin(float time)
{
	
	if (move == true) 
	{
		if (position.y >= 280)
		{
			acceleration = Vector3(0.0, -50.8, 0.0);
			velocity = Vector3(0.0, 0.0, 0.0);
			down = true;
		}
		if (position.y <= 80 && down == true)
		{
			acceleration = Vector3(0.0, 20.8, 0.0);
			velocity = Vector3(0.0, 0.0, 0.0);
			down = false;
		}

		velocity = velocity + acceleration*time;
		position = position + velocity*time;

		penguinSeneNode->setPosition(position);

	}
	else
	{
		return;
	}
}

void BasicTutorial_00::createLight(void)
{
	Light *light = mSceneMgr->createLight("Light1");
	light->setType(Light::LT_POINT);
	light->setDiffuseColour(0, 0.5, 0);
	light->setSpecularColour(0, 0.5, 0);
	light->setPosition(Vector3(150, 250, 100));

	Light *light2 = mSceneMgr->createLight("Light2");
	light2->setType(Light::LT_POINT);
	light2->setDiffuseColour(0.5, 0.5, 0.5);
	light2->setSpecularColour(0.5, 0.5, 0.5);
	light2->setPosition(Vector3(-150, 300, 250));
}

void BasicTutorial_00::createLight2(void)
{
	Light *light = mSceneMgr87->createLight("Light3");
	light->setType(Light::LT_POINT);
	light->setDiffuseColour(0, 0, 1);
	light->setSpecularColour(0, 0, 1);
	light->setPosition(Vector3(150, 250, 100));
}
void BasicTutorial_00::toggleView(void)
{
	if (change == false && change2 == false) {
		mWindow->removeViewport(mViewportArr[0]->getZOrder());
		mWindow->removeViewport(mViewportArr[1]->getZOrder());

		mCamera = mCameraArr[1];

		Ogre::Viewport* vp = mWindow->addViewport(mCamera, 1);
		vp->setBackgroundColour(Ogre::ColourValue(0, 0.0, 1.0));
		mCamera->setAspectRatio(
			Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

		mCamera = mCameraArr[0];

		Ogre::Viewport *vp2 = mWindow->addViewport(mCamera, 2, 0.7, 0, 0.3, 0.3);
		vp2->setBackgroundColour(Ogre::ColourValue(1, 0, 0));
		mCamera->setAspectRatio(Ogre::Real(vp2->getActualWidth()) / Ogre::Real(vp2->getActualHeight()));

		change = true;
		mViewportArr[0] = vp;
		mViewportArr[1] = vp2;

	}
	else if(change == true && change2 == false){
		mWindow->removeViewport(mViewportArr[0]->getZOrder());
		mWindow->removeViewport(mViewportArr[1]->getZOrder());

		mCamera = mCameraArr[0];

		Ogre::Viewport* vp = mWindow->addViewport(mCamera, 1);
		vp->setBackgroundColour(Ogre::ColourValue(0, 0.0, 1.0));
		mCamera->setAspectRatio(
			Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

		mCamera = mCameraArr[1];

		Ogre::Viewport *vp2 = mWindow->addViewport(mCamera, 2, 0.7, 0, 0.3, 0.3);
		vp2->setBackgroundColour(Ogre::ColourValue(1, 0, 0));
		mCamera->setAspectRatio(Ogre::Real(vp2->getActualWidth()) / Ogre::Real(vp2->getActualHeight()));

		change = false;
		mViewportArr[0] = vp;
		mViewportArr[1] = vp2;
	}
	else if (change == false && change2 == true) {
		mWindow->removeViewport(mViewportArr[0]->getZOrder());
		mWindow->removeViewport(mViewportArr[1]->getZOrder());

		mCamera = mCameraArr[1];

		Ogre::Viewport* vp = mWindow->addViewport(mCamera, 1);
		vp->setBackgroundColour(Ogre::ColourValue(0, 0.0, 1.0));
		mCamera->setAspectRatio(
			Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

		mCamera = mCameraArr[0];

		Ogre::Viewport *vp2 = mWindow->addViewport(mCamera, 2, 0.7, 0.7, 0.3, 0.3);
		vp2->setBackgroundColour(Ogre::ColourValue(1, 0, 0));
		mCamera->setAspectRatio(Ogre::Real(vp2->getActualWidth()) / Ogre::Real(vp2->getActualHeight()));

		change = true;
		mViewportArr[0] = vp;
		mViewportArr[1] = vp2;

	}
	else if (change == true && change2 == true) {
		mWindow->removeViewport(mViewportArr[0]->getZOrder());
		mWindow->removeViewport(mViewportArr[1]->getZOrder());

		mCamera = mCameraArr[0];

		Ogre::Viewport* vp = mWindow->addViewport(mCamera, 1);
		vp->setBackgroundColour(Ogre::ColourValue(0, 0.0, 1.0));
		mCamera->setAspectRatio(
			Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

		mCamera = mCameraArr[1];

		Ogre::Viewport *vp2 = mWindow->addViewport(mCamera, 2, 0.7, 0.7, 0.3, 0.3);
		vp2->setBackgroundColour(Ogre::ColourValue(1, 0, 0));
		mCamera->setAspectRatio(Ogre::Real(vp2->getActualWidth()) / Ogre::Real(vp2->getActualHeight()));

		change = false;
		mViewportArr[0] = vp;
		mViewportArr[1] = vp2;
	}
}

void BasicTutorial_00::changeViewPosition(void)
{
	if (change2 == false&& change == false) {
		mWindow->removeViewport(mViewportArr[1]->getZOrder());

		mCamera = mCameraArr[1];

		Ogre::Viewport *vp2 = mWindow->addViewport(mCamera, 2, 0.7, 0.7, 0.3, 0.3);
		vp2->setBackgroundColour(Ogre::ColourValue(1, 0, 0));
		mCamera->setAspectRatio(Ogre::Real(vp2->getActualWidth()) / Ogre::Real(vp2->getActualHeight()));

		change2 = true;
	}
	else if(change2 == true && change == false)
	{
		mWindow->removeViewport(mViewportArr[1]->getZOrder());


		mCamera = mCameraArr[1];

		Ogre::Viewport *vp2 = mWindow->addViewport(mCamera, 2, 0.7, 0, 0.3, 0.3);
		vp2->setBackgroundColour(Ogre::ColourValue(1, 0, 0));
		mCamera->setAspectRatio(Ogre::Real(vp2->getActualWidth()) / Ogre::Real(vp2->getActualHeight()));

		change2 = false;
	}
	else if (change2 == false && change == true)
	{
		mWindow->removeViewport(mViewportArr[1]->getZOrder());

		mCamera = mCameraArr[0];

		Ogre::Viewport *vp2 = mWindow->addViewport(mCamera, 2, 0.7, 0.7, 0.3, 0.3);
		vp2->setBackgroundColour(Ogre::ColourValue(1, 0, 0));
		mCamera->setAspectRatio(Ogre::Real(vp2->getActualWidth()) / Ogre::Real(vp2->getActualHeight()));

		change2 = true;
	}
	else if (change2 == true && change == true)
	{
		mWindow->removeViewport(mViewportArr[1]->getZOrder());

		mCamera = mCameraArr[0];

		Ogre::Viewport *vp2 = mWindow->addViewport(mCamera, 2, 0.7, 0, 0.3, 0.3);
		vp2->setBackgroundColour(Ogre::ColourValue(1, 0, 0));
		mCamera->setAspectRatio(Ogre::Real(vp2->getActualWidth()) / Ogre::Real(vp2->getActualHeight()));

		change2 = false;
	}
}

void BasicTutorial_00::createBall(void) 
{
	String name;

	float x, z;

	int c;

	for(int i =0; i<ballNum; i++)
	{
		genNameUsingIndex("ball", i, name);
		
		Entity *ball = mSceneMgr->createEntity(name, Ogre::SceneManager::PT_SPHERE);

		SceneNode *sonde10 = mSceneMgr->getRootSceneNode()->createChildSceneNode();

		ballSceneNode[i] = sonde10;
		ballEntity[i] = ball;

		x = rand() % 600;
		z = rand() % 600;
		c = rand() % 3;
		
		sonde10->attachObject(ball);
		sonde10->setPosition(x-300, 0, z-300);
		sonde10->setScale(.25, .25, .25);

		ballPosition[i] = sonde10->getPosition();

		switch (c)
		{
			case 0:
				ball->setMaterialName("Examples/red");
				break;
			case 1:
				ball->setMaterialName("Examples/green");
				break;
			case 2:
				ball->setMaterialName("Examples/blue");
				break;
		}
	}
}

void BasicTutorial_00::collisionTest(void)
{
	// bigball to smallball
	for (int i = 0; i < ballNum; i++)
	{
		Vector3 dv = ballSceneNode[i]->getPosition() - bigballPosition;
		float d = sqrt(dv.x*dv.x + dv.y*dv.y + dv.z*dv.z);
		float w = bigBallEntity->getBoundingRadius() + ballEntity[i]->getBoundingRadius() - d;

		if (w > 0)
			ballPosition[i] += dv / d * w;
	}

	// smallball to smallball
	for (int i = 0; i < ballNum; i++)
	{
		for (int j = i + 1; j < ballNum; j++)
		{

			Vector3 dv = ballSceneNode[j]->getPosition() - ballSceneNode[i]->getPosition();
			float d = sqrt(dv.x*dv.x + dv.y*dv.y + dv.z*dv.z);
			float w = ballEntity[j]->getBoundingRadius() + ballEntity[i]->getBoundingRadius() - d;

			if (w > 0)
			{
				ballPosition[j] += dv / d * w * 0.5f;
				ballPosition[i] -= dv / d * w * 0.5f;
			}

		}
	}
}