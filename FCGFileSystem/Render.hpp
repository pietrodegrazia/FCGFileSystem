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

extern void renderDirectory(int index, int depth);
extern void updateState();
extern void mainRender();
extern void renderFile(int index, int depth);

#endif /* Render_hpp */
