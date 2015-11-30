//
//  CameraManager.cpp
//  FCGFileSystem
//
//  Created by Pietro Degrazia on 11/24/15.
//  Copyright © 2015 PietroHenrique. All rights reserved.
//

#include "CameraManager.hpp"


float initialY = 0.4f;
float speedX = 0.0f;
float speedY = 0.0f;
float speedZ = 0.0f;

float posX = 0.0f;
float posY = 5.0f;
float posZ = 20.0f;

float roty = 0.0f;
float rotx = 90.0f;

/*
 variavel auxiliar pra dar variaÁ„o na altura do ponto de vista ao andar.
 */
float headPosAux = 2.0f;

float maxSpeed = 1.0f;

void moveCamera(){
    // Deprecated in OS X 10.9
    windowXPos = glutGet(GLUT_WINDOW_X);
    windowYPos = glutGet(GLUT_WINDOW_Y);
    windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    
    // restrain mouse to the window
    //    bool isMouseInsideWindow = (mouseLastY > 0) && (mouseLastY < windowHeight) && (mouseLastX > 0) && (mouseLastX < windowWidth);
    //    if (isMouseInsideWindow){
    //        float mouseMoveX = (mouseLastX - mouseOldX);
    //        float mouseMoveY = (mouseLastY - mouseOldY);
    //
    //        if (mouseMoveX > 0){
    //            // Right
    //            roty += mouseMoveFactor;
    //        }else{
    //            // Left
    //            if (mouseMoveX < 0){
    //                roty -= mouseMoveFactor;
    //            }else{
    //                // no move
    //            }
    //        }
    //
    //        if (mouseMoveY > 0){
    //            // Up
    //            rotx += mouseMoveFactor;
    //        }else{
    //            // Down
    //            if (mouseMoveY < 0){
    //                rotx -= mouseMoveFactor;
    //            }else{
    //                // no move
    //            }
    //        }
    //
    //        mouseOldX = mouseLastX;
    //        mouseOldY = mouseLastY;
    //    }
}

void updateIndex(){
    currentIndex = posX/3;
}

float jumpSideFactor = 0.000001;

void moveOriginOnAxisX(){
    posX = 0;
}

void moveLeft(){
    float newPosition = posX - PADDING;
    if(newPosition >= 0){
        while (posX > newPosition) {
            posX -= jumpSideFactor;
        }
    }
    updateIndex();
    glutPostRedisplay();
}

void moveRight(){
    float maxPosition = currentDirList.size() * PADDING;
    float newPosition = posX + PADDING;
    if (newPosition < maxPosition) {
        while (posX < newPosition) {
            posX += jumpSideFactor;
        }
    }
    updateIndex();
    glutPostRedisplay();
}

float jumpUpFactor = 0.025f;
float jumpDownFactor = 0.025f;
float jumpHeight = 0.8f;
bool isJumping = false;
bool isJumpingUp = false;
bool isJumpingDown = false;
//void jump(){
//    if (spacePressed && !isJumping) {
//        isJumping = true;
//        isJumpingUp = true;
//        isJumpingDown = false;
//    }
//
//    if (isJumpingUp) {
//        posY += jumpUpFactor;
//        if (posY > jumpHeight) {
//            posY = jumpHeight;
//            isJumpingUp = false;
//            isJumpingDown = true;
//        }
//    }
//
//    if (isJumpingDown) {
//        posY -= jumpDownFactor;
//        if (posY < initialY) {
//            posY = initialY;
//            isJumping = false;
//            isJumpingDown = false;
//        }
//    }
//}

//float crawlingFactor = 0.025f;
//float crawlingHeight = 0.125f;
//bool isCrawling = false;
//void crawl(){
//    if (cPressed) {
//        if (!isJumping) {
//            isCrawling = true;
//            posY -= crawlingFactor;
//            if (posY < crawlingHeight) {
//                posY = crawlingHeight;
//            }
//        }
//    }else{
//        if (isCrawling){
//            posY += crawlingFactor;
//            if (posY > initialY) {
//                posY = initialY;
//                isCrawling = false;
//            }
//        }
//    }
//}

void rotateLeft(){
    if (leftPressed) {
        roty -= 4.0f;
    }
}

void rotateRight(){
    if (rightPressed) {
        roty += 4.0f;
    }
}

float runAccelerationFactor = 1.5f;
void goForward(){
    if (upPressed) {
        speedX = 0.025 * sin(roty*PI/180);
        speedZ = -0.025 * cos(roty*PI/180);
        
        if (rPressed) {
            speedX *= runAccelerationFactor;
            speedZ *= runAccelerationFactor;
        }
        posX += speedX;
        posZ += speedZ;
    }
}

void goBackwards(){
    if (downPressed) {
        speedX = 0.025 * sin(roty*PI/180);
        speedZ = -0.025 * cos(roty*PI/180);
        if (rPressed) {
            speedX *= runAccelerationFactor;
            speedZ *= runAccelerationFactor;
        }
        
        posX -= speedX;
        posZ -= speedZ;
    }
}

float moveHeadHeightVariation = 1.0f;
float initialYMoveHead = 0.0f;
float moveHeadFactor = 0.025f;
void moveHead(){
    if ((upPressed || downPressed) && (!isJumping) ){
        if (headPosAux == 0.0f){
            headPosAux = fmod(headPosAux, 90) - 1 * headPosAux / 90;
            headPosAux -= 4.0f;
            //            This controle is in the outside if to make it 'generic'
            //            if (headPosAux < 0.0f) {
            //                headPosAux = 0.0f;
            //            }
        }else{
            headPosAux += 7.0f;
            if (headPosAux > 180.0f) {
                headPosAux = 0.0f;
            }
        }
    }
}
