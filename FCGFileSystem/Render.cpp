//
//  Render.cpp
//  FCGFileSystem
//
//  Created by Pietro Degrazia on 11/24/15.
//  Copyright © 2015 PietroHenrique. All rights reserved.
//

#include "Render.hpp"


float planeSize = 100.0f;


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
//    bits = LoadDIBitmap("/Users/valcanaia/Documents/UFRGS/2015-2/FCG/Pratica/Exercise_x3/FPS/res/tiledbronze.bmp", &info);
//    bits = LoadDIBitmap("/Users/pietrodegrazia/Documents/UFRGS/FCG/FCGFileSystem 2/FCGFileSystem/circuit.bmp", &info);
    bits = LoadDIBitmap("/Users/valcanaia/Documents/UFRGS/2015-2/FCG/Trabalho Final/FCGFileSystem/FCGFileSystem/circuit.bmp", &info);
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

bool selected = false;
void renderFileList(){
    char* depthPath = (char*)malloc(sizeof(char)*FILENAME_MAX);
    strcpy(depthPath, kRootFolder);
    
    for (int depth = 0; depth < fileSystem.size(); depth++){
        if(depth>0){
            strcat(depthPath, "/");
            strcat(depthPath, currentPathComponents[depth-1]);
        }
        
        for(int index = 0; index < fileSystem[depth].size(); index++){
            char* indexPath = (char*)malloc(sizeof(char)*FILENAME_MAX);
            strcpy(indexPath, depthPath);
            strcat(indexPath, "/");
            strcat(indexPath, fileSystem[depth][index].d_name);
            
            int file = direntIsFile(fileSystem[depth][index]);
            selected = index == fileIndex[depth] ? true : false;
            if (file == 1) {
                renderFile(index, depth);
            } else if (file==0){
                renderDirectory(index, depth);
            } else {
                printf("Desconhecido\n");
            }

        }
    }
}

float initialX = 0;
void renderFile(int index, int depth){
    drawSphere(PADDING*index, 0,  -(PADDING*5*depth)+1, selected);
}

void renderDirectory(int index, int depth){
    drawCube(PADDING*index, 0, -(PADDING*5*depth)+1,selected);
}

void updateState() {
    updateCam();
}

/**
 Render scene
 */
void mainRender() {
    char* txt = (char*)malloc(10);
    strcpy(txt, "miauzao");
    writeText(0, 0, 0, txt);

    
    updateState();
    renderScene();
    glFlush();

}


//
//void renderFile(int i){
//    SolidSphere s = SolidSphere(FILE_SPHERE_RADIUS, MAX_RINGS ,MAX_SECTORS);
//    s.draw(PADDING*i, 0, 0,selected);
//}
//
//void renderDirectory(int i){
//    drawCube(PADDING*i, 0,0,selected);
//}




//
//void renderFileList(){
//    char* path = (char*)malloc(sizeof(char)*FILENAME_MAX);
//    for ( int i = 0; i < currentDirList.size(); i++) {
//        strcpy(path, getCurrentPathAppending(currentDirList[i].d_name));
//        int file = isFile(path);
//        selected = i == currentIndex ? true : false;
//        if (file == 1) {
//            renderFile(i);
//        } else if (file==0){
//            renderDirectory(i);
//        } else {
//            printf("Desconhecido\n");
//        }
//    }
//}