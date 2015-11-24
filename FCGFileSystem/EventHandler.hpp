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


extern void onMouseButton(int button, int state, int x, int y);

extern void mainHandleMouseRightButtonMenuEvent(int option);


/**
 Mouse move while button pressed event handler
 */
extern void onMouseMove(int x, int y);

/**
 Mouse move with no button pressed event handler
 */
extern void onMousePassiveMove(int x, int y);
/**
 Key press event handler
 */
extern void onKeyDown(unsigned char key, int x, int y);
/**
 Key release event handler
 */
extern void onKeyUp(unsigned char key, int x, int y);

#endif /* EventHandler_hpp */
