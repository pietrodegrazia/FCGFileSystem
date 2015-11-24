//
//  ViewManager.hpp
//  FCGFileSystem
//
//  Created by Pietro Degrazia on 11/24/15.
//  Copyright © 2015 PietroHenrique. All rights reserved.
//

#ifndef ViewManager_hpp
#define ViewManager_hpp

#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include <GLUT/glut.h>
#include "CameraManager.hpp"
#include <math.h>
#include <cmath>

#define PI 3.14159265
/**
 Screen dimensions
 */
extern char windowName[];
extern int windowWidth;
extern int windowHeight;
extern int windowXPos;
extern int windowYPos;

extern int mainWindowId;
extern void mainIdle();
extern void mainInit();
extern void setWindow();
extern void updateCam();

extern void setViewport(GLint left, GLint right, GLint bottom, GLint top);
extern void initTexture(void);
extern void renderFloor();
extern void renderFileList();
extern void renderScene();
extern void onWindowReshape(int x, int y);
extern void mainCreateMenu();
extern void mainInit();
extern void handleEnterPressed();

#endif /* ViewManager_hpp */
