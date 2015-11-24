/**
 Implementa a movimentaÁ„o simples de uma camera em primeira pessoa para um personagem que anda
 sobre um plano.
 */

//#include <windows.h>


#include <unistd.h>
#include <ftw.h>
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
#include "dirent.h"
#include <vector>
#include <string>

//bitmap class to load bitmaps for textures
#include "bitmap.h"


#ifndef USE_FDS
#define USE_FDS 15
#endif

//#include <mmsystem.h>
//#pragma comment(lib, "winmm.lib")

#define PI 3.14159265

// sound stuff
#define NUM_BUFFERS 1
#define NUM_SOURCES 1
#define NUM_ENVIRONMENTS 1

// Consts
#define kRootFolder "/Users/pietrodegrazia/Documents/UFRGS/FCG/FCGFileSystem/FCGFileSystem/DirA"
#define MAX_FILE_NAME 255

void mainInit();
//void initSound();
void initTexture();
void createGLUI();
void mainRender();
void mainCreateMenu();
void onMouseButton(int button, int state, int x, int y);
void onMouseMove(int x, int y);
void onKeyDown(unsigned char key, int x, int y);
void onKeyUp(unsigned char key, int x, int y);
void onGLUIEvent(int id);
void onWindowReshape(int x, int y);
void mainIdle();
int main(int argc, char **argv);
void setWindow();
void setViewport(GLint left, GLint right, GLint bottom, GLint top);
void updateState();
void renderFloor();
void updateCam();

/**
 Screen dimensions
 */
int windowWidth = 600;
int windowHeight = 480;

/**
 Screen position
 */
int windowXPos = 100;
int windowYPos = 150;

int mainWindowId = 0;

double xOffset = -1.9;
double yOffset = -1.3;
int mouseLastX = 0;
int mouseLastY = 0;

float roty = 0.0f;
float rotx = 90.0f;

bool rightPressed = false;
bool leftPressed = false;
bool upPressed = false;
bool downPressed = false;
bool rPressed = false;
bool cPressed = false;
bool spacePressed = false;

float speedX = 0.0f;
float speedY = 0.0f;
float speedZ = 0.0f;

float posX = 0.0f;
float posY = 0.4f;
float posZ = 1.0f;

/*
 variavel auxiliar pra dar variaÁ„o na altura do ponto de vista ao andar.
 */
float headPosAux = 0.0f;

float maxSpeed = 0.25f;

float planeSize = 4.0f;

vector<dirent> currentDirList;
vector<char*> currentPathComponents;
/*
 // more sound stuff (position, speed and orientation of the listener)
 ALfloat listenerPos[]={0.0,0.0,4.0};
 ALfloat listenerVel[]={0.0,0.0,0.0};
 ALfloat listenerOri[]={0.0,0.0,1.0,
 0.0,1.0,0.0};
 
 // now the position and speed of the sound source
 ALfloat source0Pos[]={ -2.0, 0.0, 0.0};
 ALfloat source0Vel[]={ 0.0, 0.0, 0.0};
 
 // buffers for openal stuff
 ALuint  buffer[NUM_BUFFERS];
 ALuint  source[NUM_SOURCES];
 ALuint  environment[NUM_ENVIRONMENTS];
 ALsizei size,freq;
 ALenum  format;
 ALvoid  *data;*/



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

void setWindow() {
    //roty = 0.0f;
    //rotx = 90.0f;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)windowWidth/(GLfloat)windowHeight,0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posX,posY + 0.025 * std::abs(sin(headPosAux*PI/180)),posZ,
              posX + sin(roty*PI/180),posY + 0.025 * std::abs(sin(headPosAux*PI/180)) + cos(rotx*PI/180),posZ -cos(roty*PI/180),
              0.0,1.0,0.0);
}

/**
 Atualiza a posiÁ„o e orientaÁ„o da camera
 */
void updateCam() {
    gluLookAt(posX, posY + 0.025 * std::abs(sin(headPosAux*PI/180)),posZ,
              posX + sin(roty*PI/180),posY + 0.025 * std::abs(sin(headPosAux*PI/180)) + cos(rotx*PI/180),posZ -cos(roty*PI/180),
              0.0,1.0,0.0);
    
    /*listenerPos[0] = posX;
     listenerPos[1] = posY;
     listenerPos[2] = posZ;
     
     source0Pos[0] = posX;
     source0Pos[1] = posY;
     source0Pos[2] = posZ;*/
}

void setViewport(GLint left, GLint right, GLint bottom, GLint top) {
    glViewport(left, bottom, right - left, top - bottom);
}


/**
 Initialize
 */
void mainInit() {
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f,0.0f,0.0f);
    setWindow();
    setViewport(0, windowWidth, 0, windowHeight);
    
    //	initSound();
    
    initTexture();
    
    printf("w - go forward \n");
    printf("s - go backward \n");
    printf("mouse - look around \n");
}

/**
 Initialize openal and check for errors
 
 void initSound() {
 
	printf("Initializing OpenAl \n");
 
	// Init openAL
 //	alutInit(0, NULL);
 
	alGetError(); // clear any error messages
 
 // Generate buffers, or else no sound will happen!
 alGenBuffers(NUM_BUFFERS, buffer);
 
 if(alGetError() != AL_NO_ERROR)
 {
 printf("- Error creating buffers !!\n");
 exit(1);
 }
 else
 {
 printf("init() - No errors yet.\n");
 }
 
 //	alutLoadWAVFile("..\\res\\Footsteps.wav",&format,&data,&size,&freq,false);
 alBufferData(buffer[0],format,data,size,freq);
 //alutUnloadWAV(format,data,size,freq);
 
	alGetError();
 alGenSources(NUM_SOURCES, source);
 
 //    if(alGetError() != AL_NO_ERROR)
 //    {
 //        printf("- Error creating sources !!\n");
 //        exit(2);
 //    }
 //    else
 //    {
 //        printf("init - no errors after alGenSources\n");
 //    }
 
	listenerPos[0] = posX;
	listenerPos[1] = posY;
	listenerPos[2] = posZ;
 
	source0Pos[0] = posX;
	source0Pos[1] = posY;
	source0Pos[2] = posZ;
 
	alListenerfv(AL_POSITION,listenerPos);
 alListenerfv(AL_VELOCITY,listenerVel);
 alListenerfv(AL_ORIENTATION,listenerOri);
 
	alSourcef(source[0], AL_PITCH, 1.0f);
 alSourcef(source[0], AL_GAIN, 1.0f);
 alSourcefv(source[0], AL_POSITION, source0Pos);
 alSourcefv(source[0], AL_VELOCITY, source0Vel);
 alSourcei(source[0], AL_BUFFER,buffer[0]);
 alSourcei(source[0], AL_LOOPING, AL_TRUE);
 
	printf("Sound ok! \n\n");
 }*/

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

void renderFileList(){
    for ( int i = 0; i < currentDirList.size(); i++) {
        printf("%s\n", currentDirList[i].d_name);
        
//        if (isFile()) {
//            statements
//        }
        
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

void renderScene() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    updateCam();
    renderFloor();
}

float initialY = 0.4f;

float jumpUpFactor = 0.025f;
float jumpDownFactor = 0.025f;
float jumpHeight = 0.8f;
bool isJumping = false;
bool isJumpingUp = false;
bool isJumpingDown = false;
void jump(){
    if (spacePressed && !isJumping) {
        isJumping = true;
        isJumpingUp = true;
        isJumpingDown = false;
    }
    
    if (isJumpingUp) {
        posY += jumpUpFactor;
        if (posY > jumpHeight) {
            posY = jumpHeight;
            isJumpingUp = false;
            isJumpingDown = true;
        }
    }
    
    if (isJumpingDown) {
        posY -= jumpDownFactor;
        if (posY < initialY) {
            posY = initialY;
            isJumping = false;
            isJumpingDown = false;
        }
    }
}

float crawlingFactor = 0.025f;
float crawlingHeight = 0.125f;
bool isCrawling = false;
void crawl(){
    if (cPressed) {
        if (!isJumping) {
            isCrawling = true;
            posY -= crawlingFactor;
            if (posY < crawlingHeight) {
                posY = crawlingHeight;
            }
        }
    }else{
        if (isCrawling){
            posY += crawlingFactor;
            if (posY > initialY) {
                posY = initialY;
                isCrawling = false;
            }
        }
    }
}

void rotateLeft(){
    if (leftPressed) {
        roty -= 4.0f;
    }
}

void rotateRight(){
    if (rightPressed) {
        roty += 4.0f;
    }
}

float runAccelerationFactor = 1.5f;
void goForward(){
    if (upPressed) {
        speedX = 0.025 * sin(roty*PI/180);
        speedZ = -0.025 * cos(roty*PI/180);
        
        if (rPressed) {
            speedX *= runAccelerationFactor;
            speedZ *= runAccelerationFactor;
        }
        posX += speedX;
        posZ += speedZ;
    }
}

void goBackwards(){
    if (downPressed) {
        speedX = 0.025 * sin(roty*PI/180);
        speedZ = -0.025 * cos(roty*PI/180);
        if (rPressed) {
            speedX *= runAccelerationFactor;
            speedZ *= runAccelerationFactor;
        }
        
        posX -= speedX;
        posZ -= speedZ;
    }
}

float moveHeadHeightVariation = 1.0f;
float initialYMoveHead = 0.0f;
float moveHeadFactor = 0.025f;
void moveHead(){
    if ((upPressed || downPressed) && (!isJumping) ){
        if (headPosAux == 0.0f){
            headPosAux = fmod(headPosAux, 90) - 1 * headPosAux / 90;
            headPosAux -= 4.0f;
            //            This controle is in the outside if to make it 'generic'
            //            if (headPosAux < 0.0f) {
            //                headPosAux = 0.0f;
            //            }
        }else{
            headPosAux += 7.0f;
            if (headPosAux > 180.0f) {
                headPosAux = 0.0f;
            }
        }
    }
}

float mouseOldX = 0;
float mouseOldY = 0;
float mouseMoveFactor = 1.0f;
void moveCamera(){
    // Deprecated in OS X 10.9
    windowXPos = glutGet(GLUT_WINDOW_X);
    windowYPos = glutGet(GLUT_WINDOW_Y);
    windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    
    // restrain mouse to the window
    bool isMouseInsideWindow = (mouseLastY > 0) && (mouseLastY < windowHeight) && (mouseLastX > 0) && (mouseLastX < windowWidth);
    if (isMouseInsideWindow){
        float mouseMoveX = (mouseLastX - mouseOldX);
        float mouseMoveY = (mouseLastY - mouseOldY);
        
        if (mouseMoveX > 0){
            // Right
            roty += mouseMoveFactor;
        }else{
            // Left
            if (mouseMoveX < 0){
                roty -= mouseMoveFactor;
            }else{
                // no move
            }
        }
        
        if (mouseMoveY > 0){
            // Up
            rotx += mouseMoveFactor;
        }else{
            // Down
            if (mouseMoveY < 0){
                rotx -= mouseMoveFactor;
            }else{
                // no move
            }
        }
        
        mouseOldX = mouseLastX;
        mouseOldY = mouseLastY;
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
    //	sleep(30);
}

/**
 Handles events from the mouse right button menu
 */
void mainHandleMouseRightButtonMenuEvent(int option) {
    switch (option) {
        case 1 :
            exit(0);
            break;
        default:
            break;
    }
}

/**
 Create mouse button menu
 */
void mainCreateMenu() {
    glutCreateMenu(mainHandleMouseRightButtonMenuEvent);
    glutAddMenuEntry("Quit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/**
 Mouse button event handler
 */
void onMouseButton(int button, int state, int x, int y) {
    //printf("onMouseButton button: %d \n", button);
    glutPostRedisplay();
}

/**
 Mouse move while button pressed event handler
 */
void onMouseMove(int x, int y) {
    mouseLastX = x;
    mouseLastY = y;
    //    printf("%d, %d\n", x, y);
    
    glutPostRedisplay();
}

/**
 Mouse move with no button pressed event handler
 */
void onMousePassiveMove(int x, int y) {
    mouseLastX = x;
    mouseLastY = y;
}

/**
 Key press event handler
 */
void onKeyDown(unsigned char key, int x, int y) {
    switch (key) {
        case 32: //space
            spacePressed = true;
            break;
            
        case 119: //w
            //            if (!upPressed) {
            //				alSourcePlay(source[0]);
            //PlaySound((LPCSTR) "..\\..\\Footsteps.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            //            }
            upPressed = true;
            break;
            
        case 115: //s
            downPressed = true;
            break;
            
        case 97: //a
            leftPressed = true;
            break;
            
        case 99:
            cPressed = true;
            break;
            
        case 100: //d
            rightPressed = true;
            break;
            
        case 114:
            rPressed = true;
            break;
            
        default:
            break;
    }
    
    //glutPostRedisplay();
}

/**
 Key release event handler
 */
void onKeyUp(unsigned char key, int x, int y) {
    switch (key) {
        case 32:
            // the control to release space will be in the jump function
            spacePressed = false;
            break;
            
        case 119: //w
            //            if (upPressed) {
            //				alSourceStop(source[0]);
            //PlaySound(NULL, 0, 0);
            //            }
            upPressed = false;
            break;
            
        case 115: //s
            downPressed = false;
            break;
            
        case 97: //a
            leftPressed = false;
            break;
            
        case 99:
            cPressed = false;
            break;
            
        case 100: //d
            rightPressed = false;
            break;
            
        case 114:
            rPressed = false;
            break;
            
        case 27:
            exit(0);
            break;
            
        default:
            break;
    }
    
    //glutPostRedisplay();
}

void onWindowReshape(int x, int y) {
    windowWidth = x;
    windowHeight = y;
    setWindow();
    setViewport(0, windowWidth, 0, windowHeight);
}

/**
 Glut idle funtion
 */
void mainIdle() {
    /**
     Set the active window before send an glutPostRedisplay call
     so it wont be accidently sent to the glui window
     */
    glutSetWindow(mainWindowId);
    glutPostRedisplay();
}

//void listdir(const char *name, int level)
//{
//    DIR *dir;
//    struct dirent *entry;
//    
//    if (!(dir = opendir(name)))
//        return;
//    if (!(entry = readdir(dir)))
//        return;
//    
//    do {
//        if (entry->d_type == DT_DIR) {
//            char path[1024];
//            int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
//            path[len] = 0;
//            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
//                continue;
//            printf("%*s[%s]\n", level*2, "", entry->d_name);
//            listdir(path, level + 1);
//        }
//        else
//            printf("%*s- %s\n", level*2, "", entry->d_name);
//    } while ((entry = readdir(dir)));
//    closedir(dir);
//}

int print_entry(const char *filepath, const struct stat *info,
                const int typeflag, struct FTW *pathinfo)
{
    /* const char *const filename = filepath + pathinfo->base; */
    const double bytes = (double)info->st_size; /* Not exact if large! */
    struct tm mtime;
    
    localtime_r(&(info->st_mtime), &mtime);
    
//    printf("%04d-%02d-%02d %02d:%02d:%02d",
//           mtime.tm_year+1900, mtime.tm_mon+1, mtime.tm_mday,
//           mtime.tm_hour, mtime.tm_min, mtime.tm_sec);
    
//    if (bytes >= 1099511627776.0)
//        printf(" %9.3f TiB", bytes / 1099511627776.0);
//    else
//        if (bytes >= 1073741824.0)
//            printf(" %9.3f GiB", bytes / 1073741824.0);
//        else
//            if (bytes >= 1048576.0)
//                printf(" %9.3f MiB", bytes / 1048576.0);
//            else
//                if (bytes >= 1024.0)
//                    printf(" %9.3f KiB", bytes / 1024.0);
//                else
//                    printf(" %9.0f B  ", bytes);
    
    if (typeflag == FTW_SL) {
        char   *target;
        size_t  maxlen = 1023;
        ssize_t len;
        
        while (1) {
            
            target = (char*)malloc(maxlen + 1);
            if (target == NULL)
                return ENOMEM;
            
            len = readlink(filepath, target, maxlen);
            if (len == (ssize_t)-1) {
                const int saved_errno = errno;
                free(target);
                return saved_errno;
            }
            if (len >= (ssize_t)maxlen) {
                free(target);
                maxlen += 1024;
                continue;
            }
            
            target[len] = '\0';
            break;
        }
        
        printf(" %s -> %s\n", filepath, target);
        free(target);
        
    } else
        if (typeflag == FTW_SLN)
            printf(" %s (dangling symlink)\n", filepath);
        else
            if (typeflag == FTW_F)
                printf(" %s\n", filepath);
            else
                if (typeflag == FTW_D || typeflag == FTW_DP)
                    printf(" %s/\n", filepath);
                else
                    if (typeflag == FTW_DNR)
                        printf(" %s/ (unreadable)\n", filepath);
                    else
                        printf(" %s (unknown)\n", filepath);
    
    return 0;
}


int print_directory_tree(const char *const dirpath)
{
    int result;
    
    /* Invalid directory path? */
    if (dirpath == NULL || *dirpath == '\0')
        return errno = EINVAL;
    
    result = nftw(dirpath, print_entry, USE_FDS, FTW_PHYS);
    if (result >= 0)
        errno = result;
    
    return errno;
}

int isFile(const char* name)
{
    DIR* directory = opendir(name);
    
    if(directory != NULL)
    {
        closedir(directory);
        return 0;
    }
    
    if(errno == ENOTDIR)
    {
        return 1;
    }
    
    return -1;
}

char* getCurrentPath(){
    int cmpSize = 1;
    if (currentPathComponents.size() >0) {
        cmpSize = currentPathComponents.size();
    }
    char* path = (char*)malloc(sizeof(char) * MAX_FILE_NAME * cmpSize);
    strcpy(path, kRootFolder);
    strcat(path, "/");
//    char* component = (char*)malloc(sizeof(char) * MAX_FILE_NAME);
    for ( int i = 0; i < currentPathComponents.size(); i++) {
//        strcpy(component, currentPathComponents[i]);
        strcat(path, currentPathComponents[i]);
        strcat(path, "/");
    }
    
    return path;
}

void getFileListForPath(){

    char* dirpath = getCurrentPath();
    
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(dirpath)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if (strcmp(ent->d_name, "..") && strcmp(ent->d_name, ".")) {
                char* path = (char*)malloc(sizeof(char*)*256);
//                printf("dirpath: %s", dirpath);
                strcpy(path, dirpath);
                strcat(path, "/");
                strcat(path, ent->d_name);
                
                currentDirList.push_back(*ent);
                int file = isFile(path);
                printf ("%s",path);
                
                if (file == 1){
                    printf(", File\n");
                } else if (file == 0) {
                    printf(", Directory\n");
                }
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
    }
}

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
        mainWindowId = glutCreateWindow("FPS");
    
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



    
    
    
    
    //    listdir(".", 0);
//    return 0;
    
    //    DIR *dir;
//    struct dirent *ent;
//    if ((dir = opendir ("/Users")) != NULL) {
//        /* print all the files and directories within directory */
//        while ((ent = readdir (dir)) != NULL) {
//            printf ("%s\n", ent->d_name);
//        }
//        closedir (dir);
//    } else {
//        /* could not open directory */
//        perror ("");
//        return EXIT_FAILURE;
//    }

