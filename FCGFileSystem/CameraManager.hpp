//
//  CameraManager.hpp
//  FCGFileSystem
//
//  Created by Pietro Degrazia on 11/24/15.
//  Copyright © 2015 PietroHenrique. All rights reserved.
//

#ifndef CameraManager_hpp
#define CameraManager_hpp

#include <stdio.h>
#include "ViewManager.hpp"
#include "EventHandler.hpp"

extern float speedX;
extern float speedY;
extern float speedZ;

extern float posX;
extern float posY;
extern float posZ;

extern float roty;
extern float rotx;

extern float headPosAux;


extern void moveCamera();
extern void jump();
extern void crawl();
extern void rotateLeft();
extern void rotateRight();
extern void goForward();
extern void goBackwards();
extern void moveHead();


#endif /* CameraManager_hpp */
