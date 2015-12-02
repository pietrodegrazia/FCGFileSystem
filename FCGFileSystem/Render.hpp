//
//  Render.hpp
//  FCGFileSystem
//
//  Created by Pietro Degrazia on 11/24/15.
//  Copyright © 2015 PietroHenrique. All rights reserved.
//

#ifndef Render_hpp
#define Render_hpp

#include <stdio.h>
#include <GLUT/glut.h>
#include "CameraManager.hpp"
#include "FileManager.hpp"
#include "SolidSphere.cpp"
#include "Cube.hpp"
#include "Constants.h"

extern void renderFile(int i);
extern void updateState();
extern void renderFileListWithDepth();
extern void mainRender();
extern void renderDirectory(int i);
extern void renderFileAtDepth(int i, int depth);
extern void renderDirectoryAtDepth(int i, int depth);

#endif /* Render_hpp */
