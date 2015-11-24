//
//  Cube.cpp
//  FCGFileSystem
//
//  Created by Pietro Degrazia on 11/24/15.
//  Copyright © 2015 PietroHenrique. All rights reserved.
//

#include "Cube.hpp"


void drawCube(GLfloat x, GLfloat y, GLfloat z){
//    printf("\n CUBO = X: %f\n",x);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x,y,z);

    
    glBegin(GL_QUADS);


    glNormal3d(0, 0, -1);
    glVertex3f(1, -1, -1 );
    glVertex3f(1, 1, -1 );
    glVertex3f(-1, 1, -1 );
    glVertex3f(-1, -1, -1 );
    
    glEnd();
    
    // White side - BACK
    glBegin(GL_QUADS);
    
    glNormal3d(0, 0, 1);
    glVertex3f( 1, -1, 1 );
    glVertex3f(  1,  1, 1 );
    glVertex3f( -1,  1, 1 );
    glVertex3f( -1, -1, 1 );
    glEnd();
    
    // Purple side - RIGHT
    glBegin(GL_QUADS);
    
    glNormal3d(1, 0, 0);
    glVertex3f( 1, -1, -1 );
    glVertex3f( 1,  1, -1 );
    glVertex3f( 1,  1,1 );
    glVertex3f( 1, -1, 1 );
    glEnd();
    
    // Green side - LEFT
    glBegin(GL_QUADS);
    
    glNormal3d(-1, 0, 0);
    glVertex3f( -1, -1,  1 );
    glVertex3f( -1,  1,  1 );
    glVertex3f( -1,  1, -1 );
    glVertex3f( -1, -1, -1 );
    glEnd();
    
    // Blue side - TOP
    glBegin(GL_QUADS);
    
    glNormal3d(0, 1, 0);
    glVertex3f(  1,  1,  1 );
    glVertex3f(  1,  1, -1 );
    glVertex3f( -1,  1, -1 );
    glVertex3f( -1,  1,  1 );
    glEnd();
    
    // Red side - BOTTOM
    glBegin(GL_QUADS);
    
    glNormal3d(0, -1, 0);
    glVertex3f(  1, -1, -1 );
    glVertex3f(  1, -1,  1 );
    glVertex3f( -1, -1,  1 );
    glVertex3f( -1, -1, -1 );
    glEnd();

    glPopMatrix();

//    glFlush();
    
}


