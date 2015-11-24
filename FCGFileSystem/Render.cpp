//
//  Render.cpp
//  FCGFileSystem
//
//  Created by Pietro Degrazia on 11/24/15.
//  Copyright © 2015 PietroHenrique. All rights reserved.
//

#include "Render.hpp"

float planeSize = 4.0f;


// parte de cÛdigo extraÌdo de "texture.c" por Michael Sweet (OpenGL SuperBible)
// texture buffers and stuff
int i;                       /* Looping var */
BITMAPINFO	*info;           /* Bitmap information */
GLubyte	    *bits;           /* Bitmap RGB pixels */
GLubyte     *ptr;            /* Pointer into bit buffer */
GLubyte	    *rgba;           /* RGBA pixel buffer */
GLubyte	    *rgbaptr;        /* Pointer into RGBA buffer */
GLubyte     temp;            /* Swapping variable */
GLenum      type;            /* Texture type */
GLuint      texture;         /* Texture object */



/**
 Initialize the texture
 */
void initTexture(void){
    printf ("Loading texture..\n");
    // Load a texture object (256x256 true color)
    bits = LoadDIBitmap("/Users/valcanaia/Documents/UFRGS/2015-2/FCG/Pratica/Exercise_x3/FPS/res/tiledbronze.bmp", &info);
    if (bits == (GLubyte *)0) {
        printf ("Error loading texture!\n\n");
        return;
    }
    
    // Figure out the type of texture
    if (info->bmiHeader.biHeight == 1)
        type = GL_TEXTURE_1D;
    else
        type = GL_TEXTURE_2D;
    
    // Create and bind a texture object
    glGenTextures(1, &texture);
    glBindTexture(type, texture);
    
    // Set texture parameters
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Create an RGBA image
    rgba = (GLubyte *)malloc(info->bmiHeader.biWidth * info->bmiHeader.biHeight * 4);
    
    i = info->bmiHeader.biWidth * info->bmiHeader.biHeight;
    for( rgbaptr = rgba, ptr = bits;  i > 0; i--, rgbaptr += 4, ptr += 3)
    {
        rgbaptr[0] = ptr[2];     // windows BMP = BGR
        rgbaptr[1] = ptr[1];
        rgbaptr[2] = ptr[0];
        rgbaptr[3] = (ptr[0] + ptr[1] + ptr[2]) / 3;
    }
    
    glTexImage2D(type, 0, 4, info->bmiHeader.biWidth, info->bmiHeader.biHeight,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba );
    
    //    printf("Textura %d\n", texture);
    //    printf("Textures ok.\n\n", texture);
}



GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
    {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
    {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
    {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */
void renderFile(){
    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;
    
    int i;
    
    for (i = 0; i < 6; i++) {
        glBegin(GL_QUADS);
        glNormal3fv(&n[i][0]);
        glVertex3fv(&v[faces[i][0]][0]);
        glVertex3fv(&v[faces[i][1]][0]);
        glVertex3fv(&v[faces[i][2]][0]);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}


void renderFloor() {
    
    // i want some nice, smooth, antialiased lines
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
    
    // set things up to render the floor with the texture
    glShadeModel(GL_FLAT);
    glEnable (type);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(0.4f,0.4f,0.4f,1.0f);
    
    glPushMatrix();
    
    float textureScaleX = 10.0;
    float textureScaleY = 10.0;
    
    glBegin(GL_QUADS);
    glTexCoord2f(textureScaleX, 0.0f);   // coords for the texture
    glVertex3f(-planeSize, 0.0f, planeSize);
    
    glTexCoord2f(0.0f, 0.0f);  // coords for the texture
    glVertex3f(planeSize, 0.0f, planeSize);
    
    glTexCoord2f(0.0f, textureScaleY);  // coords for the texture
    glVertex3f(planeSize, 0.0f, -planeSize);
    
    glTexCoord2f(textureScaleX, textureScaleY);  // coords for the texture
    glVertex3f(-planeSize, 0.0f, -planeSize);
    glEnd();
    
    glDisable(type);
    
    glColor4f(0.8f,0.8f,0.8f,1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i <= 10; i++) {
        glVertex3f(-planeSize, 0.0f, -planeSize + i*(2*planeSize)/10.0f);
        glVertex3f(planeSize, 0.0f, -planeSize + i*(2*planeSize)/10.0f);
    }
    for (int i = 0; i <= 10; i++) {
        glVertex3f(-planeSize + i*(2*planeSize)/10.0f, 0.0f, -planeSize);
        glVertex3f(-planeSize + i*(2*planeSize)/10.0f, 0.0f, planeSize);
    }
    glEnd();
    
    glPopMatrix();
}


void renderFileList(){
    printf("\n-- Rendering File List --\n");
    char* path = (char*)malloc(sizeof(char*)*256);
    
    for ( int i = 0; i < currentDirList.size(); i++) {
        path = getCurrentPathAppending(currentDirList[i].d_name);
        int file = isFile(path);
        //        printf("%s", path);
        
        if (file == 1) {
            printf("\nFILE\n");
            renderFile();
        } else if (file==0){
            printf("\nDirectory\n");
        }
        printf("%s\n", path);
    }
    
}








void updateState() {
    moveCamera();
    jump();
    crawl();
    goForward();
    goBackwards();
    moveHead();
}

/**
 Render scene
 */
void mainRender() {
    updateState();
    renderScene();
    glFlush();
    glutPostRedisplay();
}