//
//  ViewManager.cpp
//  FCGFileSystem
//
//  Created by Pietro Degrazia on 11/24/15.
//  Copyright © 2015 PietroHenrique. All rights reserved.
//

#include "ViewManager.hpp"
#include "FileManager.hpp"
char windowName[] = "FCG File System 2015";
/**
 Screen dimensions
 */
int windowWidth = 600;
int windowHeight = 480;

/**
 Screen position
 */
int windowXPos = 100;
int windowYPos = 150;
int mainWindowId = 0;


int currentIndex = 0;

int zero = 0;
void handleEnterPressed(){
    char* path = (char*)malloc(sizeof(char) * FILENAME_MAX);
    strcpy(path, getCurrentPathAppending(currentDirList[currentIndex].d_name));
    
    int file = isFile(path);
    if (file == 1) {
        printf("\nFILEEE\n");
    } else if (file == 0){
        printf("\nDIR '%s' WITH INDEX = %i", currentDirList[currentIndex].d_name, currentIndex);
        currentPathComponents.push_back(currentDirList[currentIndex].d_name);
        currentDirList.clear();
        getFileListForPath();
        moveOriginOnAxisX();
//        printf("%s", );
    }
}

void handleBackspace(){
    currentPathComponents.pop_back();
    currentDirList.clear();
    getFileListForPath();
}




/**
 Glut idle funtion
 */
void mainIdle() {
    /**
     Set the active window before send an glutPostRedisplay call
     so it wont be accidently sent to the glui window
     */
    glutSetWindow(mainWindowId);
    glutPostRedisplay();
}

/**
 Create mouse button menu
 */
void mainCreateMenu() {
//    glutCreateMenu(mainHandleMouseRightButtonMenuEvent);
    glutAddMenuEntry("Quit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


/**
 Initialize
 */
void mainInit() {
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f,0.0f,0.0f);
    setWindow();
    setViewport(0, windowWidth, 0, windowHeight);
    
    //	initSound();
    
    initTexture();
    
    printf("w - go forward \n");
    printf("s - go backward \n");
    printf("mouse - look around \n");
}




void setWindow() {
    //roty = 0.0f;
    //rotx = 90.0f;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)windowWidth/(GLfloat)windowHeight,0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posX,posY + 0.025 * std::abs(sin(headPosAux*PI/180)),posZ,
              posX + sin(roty*PI/180),posY + 0.025 * std::abs(sin(headPosAux*PI/180)) + cos(rotx*PI/180),posZ -cos(roty*PI/180),
              0.0,1.0,0.0);
}

/**
 Atualiza a posiÁ„o e orientaÁ„o da camera
 */
void updateCam() {
    gluLookAt(posX, posY + 0.025 * std::abs(sin(headPosAux*PI/180)),posZ,
              posX + sin(roty*PI/180),posY + 0.025 * std::abs(sin(headPosAux*PI/180)) + cos(rotx*PI/180),posZ -cos(roty*PI/180),
              0.0,1.0,0.0);
    
    /*listenerPos[0] = posX;
     listenerPos[1] = posY;
     listenerPos[2] = posZ;
     
     source0Pos[0] = posX;
     source0Pos[1] = posY;
     source0Pos[2] = posZ;*/
}

void setViewport(GLint left, GLint right, GLint bottom, GLint top) {
    glViewport(left, bottom, right - left, top - bottom);
}





void onWindowReshape(int x, int y) {
    windowWidth = x;
    windowHeight = y;
    setWindow();
    setViewport(0, windowWidth, 0, windowHeight);
}


void renderScene() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    updateCam();
    renderFloor();
    renderFileList();
}

