//
//  Cube.cpp
//  FCGFileSystem
//
//  Created by Pietro Degrazia on 11/24/15.
//  Copyright © 2015 PietroHenrique. All rights reserved.
//glutSolidSphere(GLdouble radius, GLint slices, GLint stacks)

#include "Cube.hpp"

#define MAX_RINGS 1000
#define MAX_SECTORS 50
#define FILE_SPHERE_RADIUS 1

void drawCube(GLfloat x, GLfloat y, GLfloat z, bool shouldHighlight){
//    printf("\n CUBO = X: %f\n",x);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x,y,z);

    glBegin(GL_QUADS);
    
    if (shouldHighlight) {
        glColor3f(0.5f, 1.0f, 0.0f);
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    
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

void drawSphere(GLfloat x, GLfloat y, GLfloat z, bool shouldHighlight){
   
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x,y,z);
    
    if (shouldHighlight) {
        glColor3f(0.5f, 1.0f, 0.0f);
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    glutSolidSphere(FILE_SPHERE_RADIUS ,MAX_SECTORS , MAX_RINGS);
    
    
    glPopMatrix();
    
}

