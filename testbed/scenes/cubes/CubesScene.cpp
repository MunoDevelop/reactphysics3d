/********************************************************************************
* ReactPhysics3D physics library, http://www.reactphysics3d.com                 *
* Copyright (c) 2010-2016 Daniel Chappuis                                       *
*********************************************************************************
*                                                                               *
* This software is provided 'as-is', without any express or implied warranty.   *
* In no event will the authors be held liable for any damages arising from the  *
* use of this software.                                                         *
*                                                                               *
* Permission is granted to anyone to use this software for any purpose,         *
* including commercial applications, and to alter it and redistribute it        *
* freely, subject to the following restrictions:                                *
*                                                                               *
* 1. The origin of this software must not be misrepresented; you must not claim *
*    that you wrote the original software. If you use this software in a        *
*    product, an acknowledgment in the product documentation would be           *
*    appreciated but is not required.                                           *
*                                                                               *
* 2. Altered source versions must be plainly marked as such, and must not be    *
*    misrepresented as being the original software.                             *
*                                                                               *
* 3. This notice may not be removed or altered from any source distribution.    *
*                                                                               *
********************************************************************************/

// Libraries
#include "CubesScene.h"

// Namespaces
using namespace openglframework;
using namespace cubesscene;

// Constructor
CubesScene::CubesScene(const std::string& name, EngineSettings& settings, reactphysics3d::PhysicsCommon& physicsCommon)
      : SceneDemo(name, settings, physicsCommon, true, SCENE_RADIUS) {

    // Compute the radius and the center of the scene
    openglframework::Vector3 center(0, 10, 0);

    // Set the center of the scene
    setScenePosition(center, SCENE_RADIUS);
    setInitZoom(1.5);
    resetCameraToViewAll();

    mWorldSettings.worldName = name;
}

// Destructor
CubesScene::~CubesScene() {

    destroyPhysicsWorld();
}

void CubesScene::onContact(const CollisionCallback::CallbackData& callbackData) {
    // For each contact pair
    for (uint p = 0; p < callbackData.getNbContactPairs(); p++) {

        // Get the contact pair
        CollisionCallback::ContactPair contactPair = callbackData.getContactPair(p);
        std::cout<<contactPair.getBody1()->getEntity().id<<" || "<<contactPair.getBody2()->getEntity().id<<std::endl;
        CollisionCallback::ContactPair::EventType type = contactPair.getEventType();
        switch (type) {
            case reactphysics3d::CollisionCallback::ContactPair::EventType::ContactStart :
                std::cout<<"ContactStart"<<std::endl;
                break;
            case reactphysics3d::CollisionCallback::ContactPair::EventType::ContactStay :
                std::cout<<"ContactStay"<<std::endl;
                break;
            case reactphysics3d::CollisionCallback::ContactPair::EventType::ContactExit :
                std::cout<<"ContactExit"<<std::endl;
                break;
        }
        //contactPair.getBody1();


    }
}

// Create the physics world
void CubesScene::createPhysicsWorld() {

    // Gravity vector in the physics world
    mWorldSettings.gravity = rp3d::Vector3(mEngineSettings.gravity.x, mEngineSettings.gravity.y, mEngineSettings.gravity.z);

    // Create the physics world for the physics simulation
    mPhysicsWorld = mPhysicsCommon.createPhysicsWorld(mWorldSettings);
    mPhysicsWorld->setEventListener(this);
    mPhysicsWorld->getNbIterationsVelocitySolver()
    // Create all the cubes of the scene
//    for (int i=0; i<NB_CUBES; i++) {
//
//        // Create a cube and a corresponding rigid in the physics world
//        Box* cube = new Box(true, BOX_SIZE,  mPhysicsCommon, mPhysicsWorld, mMeshFolderPath);
//
//        // Set the box color
//        cube->setColor(mObjectColorDemo);
//        cube->setSleepingColor(mSleepingColorDemo);
//
//        // Change the material properties of the rigid body
//        rp3d::Material& material = cube->getCollider()->getMaterial();
//        material.setBounciness(rp3d::decimal(0.4));
//
//        // Add the box the list of box in the scene
//        mBoxes.push_back(cube);
//        mPhysicsObjects.push_back(cube);
//    }

//    reactphysics3d::CapsuleShape * capsuleShape = mPhysicsCommon.createCapsuleShape(1.0, 2.0);
//
//    //Capsule* mCapsule = new Capsule(false, 1, 2, mPhysicsCommon, mPhysicsWorld, mMeshFolderPath);
//    //mObjects.push_back(mCapsule);
//    rp3d::Vector3 position(0,1,0);
//    rp3d::Transform tmpTrans =  rp3d::Transform(position, rp3d::Quaternion::identity());
//    reactphysics3d::CollisionBody* body;
//    body = mPhysicsWorld->createCollisionBody(tmpTrans);
//    body->addCollider(capsuleShape,tmpTrans);
//
//    mObjects.push_back(body);


//    mCapsule->setTransform(tmpTrans);
//    mCapsule->getRigidBody()->setType(rp3d::BodyType::DYNAMIC);
//    mCapsule->getRigidBody()->setAngularLockAxisFactor(rp3d::Vector3(0,0,0));

    //mPhysicsObjects.push_back(mCapsule);

    Capsule* mCapsule = new Capsule(true, 1, 2, mPhysicsCommon, mPhysicsWorld, mMeshFolderPath);
    //mObjects.push_back(mCapsule);
    mObjects.push_back(mCapsule->getCollisionBody());
    rp3d::Vector3 position(0,2,0);
    rp3d::Transform tmpTrans =  rp3d::Transform(position, rp3d::Quaternion::identity());
    mCapsule->setTransform(tmpTrans);
    mCapsule->getRigidBody()->setType(rp3d::BodyType::DYNAMIC);
    mCapsule->getRigidBody()->setAngularLockAxisFactor(rp3d::Vector3(0,0,0));
    mPhysicsObjects.push_back(mCapsule);




    Capsule* mCapsule2 = new Capsule(true, 1, 2, mPhysicsCommon, mPhysicsWorld, mMeshFolderPath);
    //mObjects.push_back(mCapsule);
    mObjects.push_back(mCapsule2->getCollisionBody());
    rp3d::Vector3 position2(3,2,3);
    rp3d::Transform tmpTrans2 =  rp3d::Transform(position2, rp3d::Quaternion::identity());
    mCapsule2->setTransform(tmpTrans2);
    mCapsule2->getRigidBody()->setType(rp3d::BodyType::DYNAMIC);
    mCapsule2->getRigidBody()->setAngularLockAxisFactor(rp3d::Vector3(0,0,0));
    mPhysicsObjects.push_back(mCapsule2);


    // ------------------------- FLOOR ----------------------- //

    // Create the floor
    mFloor = new Box(true, FLOOR_SIZE, mPhysicsCommon, mPhysicsWorld, mMeshFolderPath);
    mFloor->setColor(mFloorColorDemo);
    mFloor->setSleepingColor(mFloorColorDemo);

    // The floor must be a static rigid body
    mFloor->getRigidBody()->setType(rp3d::BodyType::STATIC);
    mPhysicsObjects.push_back(mFloor);
}

// Initialize the bodies positions
void CubesScene::initBodiesPositions() {

    const float radius = 2.0f;

    // Create all the cubes of the scene
//    std::vector<PhysicsObject*>::iterator it;
//    int i = 0;
//    for (it = mObjects.begin(); it != mObjects.end(); ++it) {
//
//        // Position of the cubes
//       float angle = i * 30.0f;
//       rp3d::Vector3 position(radius * std::cos(angle),
//                              10 + i * (BOX_SIZE.y + 0.3f),
//                              0);
//
//       (*it)->setTransform(rp3d::Transform(position, rp3d::Quaternion::identity()));
//
//       i++;
//    }

    mFloor->setTransform(rp3d::Transform(rp3d::Vector3::zero(), rp3d::Quaternion::identity()));
}


bool CubesScene::keyboardEvent(int key, int scancode, int action, int mods) {

    // If the space key has been pressed
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {

        return true;
    }

    float stepDist = 0.2f;
    float stepAngle = 15 * (3.14f / 180.0f);



    if (key == GLFW_KEY_D && ((action == GLFW_REPEAT)||(action == GLFW_PRESS)||(action == GLFW_RELEASE))) {
        rp3d::Transform transform = mObjects[0]->getTransform();
        transform.setPosition(transform.getPosition() + rp3d::Vector3(stepDist, 0, 0));
        mObjects[0]->setTransform(transform);
    }else if (key == GLFW_KEY_A && ((action == GLFW_REPEAT)||(action == GLFW_PRESS)||(action == GLFW_RELEASE))) {
        rp3d::Transform transform = mObjects[0]->getTransform();
        transform.setPosition(transform.getPosition() + rp3d::Vector3(-stepDist, 0, 0));
        mObjects[0]->setTransform(transform);
    }else if (key == GLFW_KEY_W && ((action == GLFW_REPEAT)||(action == GLFW_PRESS)||(action == GLFW_RELEASE))) {
        rp3d::Transform transform = mObjects[0]->getTransform();
        transform.setPosition(transform.getPosition() + rp3d::Vector3(0, 0, -stepDist));
        mObjects[0]->setTransform(transform);
    }else if (key == GLFW_KEY_S && ((action == GLFW_REPEAT)||(action == GLFW_PRESS)||(action == GLFW_RELEASE))) {
        rp3d::Transform transform = mObjects[0]->getTransform();
        transform.setPosition(transform.getPosition() + rp3d::Vector3(0, 0, stepDist));
        mObjects[0]->setTransform(transform);
    }
//    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
//        rp3d::Transform transform = mAllShapes[mSelectedShapeIndex]->getTransform();
//        transform.setPosition(transform.getPosition() + rp3d::Vector3(-stepDist, 0, 0));
//        mAllShapes[mSelectedShapeIndex]->setTransform(transform);
//    }
//    else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
//        rp3d::Transform transform = mAllShapes[mSelectedShapeIndex]->getTransform();
//        transform.setPosition(transform.getPosition() + rp3d::Vector3(0, stepDist, 0));
//        mAllShapes[mSelectedShapeIndex]->setTransform(transform);
//    }
//    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
//        rp3d::Transform transform = mAllShapes[mSelectedShapeIndex]->getTransform();
//        transform.setPosition(transform.getPosition() + rp3d::Vector3(0, -stepDist, 0));
//        mAllShapes[mSelectedShapeIndex]->setTransform(transform);
//    }


    return false;
}

// Destroy the physics world
void CubesScene::destroyPhysicsWorld() {

    if (mPhysicsWorld != nullptr) {

        // Destroy all the cubes of the scene
        for (std::vector<reactphysics3d::CollisionBody*>::iterator it = mObjects.begin(); it != mObjects.end(); ++it) {

            // Destroy the cube
            delete (*it);
        }
        mObjects.clear();

        // Destroy the floor
        delete mFloor;

        mPhysicsObjects.clear();

        mPhysicsCommon.destroyPhysicsWorld(mPhysicsWorld);
        mPhysicsWorld = nullptr;
    }
}

// Reset the scene
void CubesScene::reset() {

    SceneDemo::reset();

    destroyPhysicsWorld();
    createPhysicsWorld();
    initBodiesPositions();
}
