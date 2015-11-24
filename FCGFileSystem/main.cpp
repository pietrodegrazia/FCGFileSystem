/**
 Implementa a movimentaÁ„o simples de uma camera em primeira pessoa para um personagem que anda
 sobre um plano.
 */

//#include <windows.h>



#include <unistd.h>

#include <time.h>
#include <string.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <iostream>
using namespace std;
#include <GLUT/glut.h>

#include "FileManager.hpp"
#include "ViewManager.hpp"
#include "EventHandler.hpp"
#include "CameraManager.hpp"
#include "Render.hpp"
//bitmap class to load bitmaps for textures


//#include <mmsystem.h>
//#pragma comment(lib, "winmm.lib")



// sound stuff
#define NUM_BUFFERS 1
#define NUM_SOURCES 1
#define NUM_ENVIRONMENTS 1

int main(int argc, char **argv);

int main(int argc, char **argv) {
    
    getFileListForPath();
    
    printf("FOI\n");
    for ( int i = 0; i < currentDirList.size(); i++) {
        
        printf("%s\n", currentDirList[i].d_name);
        
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth,windowHeight);
    glutInitWindowPosition(windowXPos,windowYPos);
    
    /**
     Store main window id so that glui can send it redisplay events
     */
    mainWindowId = glutCreateWindow(windowName);
    glutDisplayFunc(mainRender);
    glutReshapeFunc(onWindowReshape);
    /**
     Register mouse events handlers
     */
    glutMouseFunc(onMouseButton);
    glutMotionFunc(onMouseMove);
    glutPassiveMotionFunc(onMousePassiveMove);
    
    /**
     Register keyboard events handlers
     */
    glutKeyboardFunc(onKeyDown);
    glutKeyboardUpFunc(onKeyUp);
    
    mainInit();
    
    /**
     Create GLUT mouse button menus
     */
    //        mainCreateMenu();
    
    glutMainLoop();
    
    return 0;
    
}


