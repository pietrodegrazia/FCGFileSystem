//
//  EventHandler.hpp
//  FCGFileSystem
//
//  Created by Pietro Degrazia on 11/24/15.
//  Copyright © 2015 PietroHenrique. All rights reserved.
//

#ifndef EventHandler_hpp
#define EventHandler_hpp

#include <stdio.h>
#include <GLUT/glut.h>
#include <iostream>
#include "CameraManager.hpp"

extern bool rightPressed;
extern bool leftPressed;
extern bool upPressed;
extern bool downPressed;
extern bool rPressed;
extern bool cPressed;
extern bool spacePressed;
extern float mouseOldX;
extern float mouseOldY;
extern float mouseMoveFactor;

extern int mouseLastX;
extern int mouseLastY;


//extern void onMouseButton(int button, int state, int x, int y);
//extern void mainHandleMouseRightButtonMenuEvent(int option);
extern void onMouseMove(int x, int y);
extern void onMousePassiveMove(int x, int y);

extern void onKeyDown(unsigned char key, int x, int y);
extern void onKeyUp(unsigned char key, int x, int y);
extern void registerEventHandlers();


#endif /* EventHandler_hpp */
