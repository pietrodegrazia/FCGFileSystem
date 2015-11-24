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

#define PADDING 5

extern void renderFile(int i);
extern void updateState();
extern void mainRender();
extern void renderDirectory(int i);


#endif /* Render_hpp */
