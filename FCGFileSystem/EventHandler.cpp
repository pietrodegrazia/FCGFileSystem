//
//  EventHandler.cpp
//  FCGFileSystem
//
//  Created by Pietro Degrazia on 11/24/15.
//  Copyright © 2015 PietroHenrique. All rights reserved.
//

#include "EventHandler.hpp"

bool rightPressed = false;
bool leftPressed = false;
bool upPressed = false;
bool downPressed = false;
bool rPressed = false;
bool cPressed = false;
bool spacePressed = false;
bool enterPressed = false;
float mouseOldX = 0;
float mouseOldY = 0;
float mouseMoveFactor = 1.0f;
int mouseLastX = 0;
int mouseLastY = 0;

/**
 Mouse button event handler
 */
void onMouseButton(int button, int state, int x, int y) {
    //printf("onMouseButton button: %d \n", button);
//    glutPostRedisplay();
}


/**
 Handles events from the mouse right button menu
 */
void mainHandleMouseRightButtonMenuEvent(int option) {
    switch (option) {
        case 1 :
            exit(0);
            break;
        default:
            break;
    }
}


/**
// Mouse move while button pressed event handler
// */
//void onMouseMove(int x, int y) {
//    mouseLastX = x;
//    mouseLastY = y;
//    //    printf("%d, %d\n", x, y);
//    
//    glutPostRedisplay();
//}
//
///**
// Mouse move with no button pressed event handler
// */
//void onMousePassiveMove(int x, int y) {
//    mouseLastX = x;
//    mouseLastY = y;
//}

/**
 Key press event handler
 */
void onKeyDown(unsigned char key, int x, int y) {
    switch (key) {
        case 13:
            enterPressed = true;
            break;
        case 32: //space
            spacePressed = true;
            break;
            
        case 119: //w
            //            if (!upPressed) {
            //				alSourcePlay(source[0]);
            //PlaySound((LPCSTR) "..\\..\\Footsteps.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            //            }
            upPressed = true;
            break;
            
        case 115: //s
            downPressed = true;
            break;
            
        case 97: //a
            moveLeft();
            leftPressed = true;
            break;
            
        case 99:
            cPressed = true;
            break;
            
        case 100: //d
            moveRight();
            rightPressed = true;
            break;
            
        case 114:
            rPressed = true;
            break;
            
        default:
            break;
    }
    
    //glutPostRedisplay();
}

/**
 Key release event handler
 */
void onKeyUp(unsigned char key, int x, int y) {
    switch (key) {
        case 13:
            handleEnterPressed();
            enterPressed = false;
            break;
        case 32:
            // the control to release space will be in the jump function
            spacePressed = false;
            break;
            
        case 119: //w
            //            if (upPressed) {
            //				alSourceStop(source[0]);
            //PlaySound(NULL, 0, 0);
            //            }
            upPressed = false;
            break;
            
        case 115: //s
            downPressed = false;
            break;
            
        case 97: //a
            leftPressed = false;
            break;
            
        case 99:
            cPressed = false;
            break;
            
        case 100: //d
            rightPressed = false;
            break;
            
        case 114:
            rPressed = false;
            break;
            
        case 27:
            exit(0);
            break;
            
        default:
            break;
    }
    
    //glutPostRedisplay();
}