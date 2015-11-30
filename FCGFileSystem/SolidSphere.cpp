//
//  SolidSphere.cpp
//  FCGFileSystem
//
//  Created by Henrique Valcanaia on 11/24/15.
//  Copyright © 2015 PietroHenrique. All rights reserved.
//

#include "SolidSphere.hpp"

#define _USE_MATH_DEFINES
#include <GLUT/GLUT.h>
#include <vector>
#include <cmath>
#define MAX_RINGS 1000
#define MAX_SECTORS 50
#define FILE_SPHERE_RADIUS 1

class SolidSphere
{
protected:
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::vector<GLushort> indices;
    
public:
    SolidSphere(float radius, unsigned int rings, unsigned int sectors){
        float const R = 1./(float)(rings-1);
        float const S = 1./(float)(sectors-1);
        int r, s;
        
        vertices.resize(rings * sectors * 3);
        normals.resize(rings * sectors * 3);
        texcoords.resize(rings * sectors * 2);
        std::vector<GLfloat>::iterator v = vertices.begin();
        std::vector<GLfloat>::iterator n = normals.begin();
        std::vector<GLfloat>::iterator t = texcoords.begin();
        for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
            float const y = sin( -M_PI_2 + M_PI * r * R );
            float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
            float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );
            
            *t++ = s*S;
            *t++ = r*R;
            
            *v++ = x * radius;
            *v++ = y * radius;
            *v++ = z * radius;
            
            *n++ = x;
            *n++ = y;
            *n++ = z;
        }
        
        indices.resize(rings * sectors * 4);
        std::vector<GLushort>::iterator i = indices.begin();
        for(r = 0; r < rings-1; r++) for(s = 0; s < sectors-1; s++) {
            *i++ = r * sectors + s;
            *i++ = r * sectors + (s+1);
            *i++ = (r+1) * sectors + (s+1);
            *i++ = (r+1) * sectors + s;
        }
    }
    
    void draw(GLfloat x, GLfloat y, GLfloat z){
//        printf("\n CUBOLA = X: %f\n",x);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(x,y,z);
        
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        
        glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
        glNormalPointer(GL_FLOAT, 0, &normals[0]);
        glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
        glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
        glPopMatrix();
    }
};

//SolidSphere sphere(1, 12, 24);
//
//void display()
//{
//    int const win_width  = windowWidth; // retrieve window dimensions from
//    int const win_height = windowHeight; // framework of choice here
//    float const win_aspect = (float)win_width / (float)win_height;
//    
//    glViewport(0, 0, win_width, win_height);
//    
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(45, win_aspect, 1, 10);
//    
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    
//#ifdef DRAW_WIREFRAME
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//#endif
//    sphere.draw(0, 0, -5);
//    
//    swapBuffers();
//}