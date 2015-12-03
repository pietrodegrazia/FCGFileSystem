#include "ViewManager.hpp"
#include "FileManager.hpp"

char windowName[] = "FCG File System 2015";
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



int zero = 0;

void writeText(int x, int y,int z, char *string){
    
    //TEXT
    glMatrixMode( GL_PROJECTION ) ;
    glPushMatrix() ; // save
    glLoadIdentity();// and clear
    glMatrixMode( GL_MODELVIEW ) ;
    glPushMatrix() ;
    glLoadIdentity() ;
    
    glDisable( GL_DEPTH_TEST ) ; // also disable the depth test so renders on top
    glDisable(GL_LIGHTING); // no lights
    
    glRasterPos2f(-1, -1); // center of screen. (-1,0) is center left.
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    char buf[300];
    sprintf( buf, "Oh hello" );
    const char * p = buf;
    do glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *p ); while( *(++p) );
    
    glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on
    glEnable(GL_LIGHTING); // no lights
    
    glMatrixMode( GL_PROJECTION ) ;
    glPopMatrix() ; // revert back to the matrix I had before.
    glMatrixMode( GL_MODELVIEW ) ;
    glPopMatrix() ;
    
//    //set the position of the text in the window using the x and y coordinates
//    glRasterPos2f(x,y);
//    //get the length of the string to display
//    int len = (int) strlen(string);
//    
//    //loop to display character by character
//    for (int i = 0; i < len; i++){
//        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
//    }
}

void write(string text, int x, int y){
    glRasterPos2i(x,y);
    
    for(int i = 0; i < text.length(); i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text.data()[i]);
    }
}

void updateIndex(bool increment){
    int depth = fileSystem.size() -1;
    int currentIndex = fileIndex[depth];
    if (increment && (currentIndex+1 < fileSystem[depth].size() ) ) {
        fileIndex[depth] = currentIndex + 1;
        glutPostRedisplay();
    } else if( !(increment) && ( currentIndex-1 >= 0 ) ){
        fileIndex[depth] = currentIndex - 1;
        glutPostRedisplay();
    }

//    printf(" \n\n ATUAl: %s\n   Index: %i", fileSystem[depth][currentIndex].d_name, currentIndex);
    
}

void openFile(char* filePath, char* fileName){
    char* fullFilePath = (char*)malloc(sizeof(char)*FILENAME_MAX*fileSystem.size());
    sprintf(fullFilePath, "%s%s", filePath, fileName);
    
    char* command = (char*)malloc(sizeof(char)*FILENAME_MAX*fileSystem.size());
    sprintf(command, "open '%s'", fullFilePath);
    system(command);
}

void handleEnterPressed(){
    printf("\n************* ENTER PRESSED ****************\n");
    int depth = fileSystem.size()-1;
    int currentIndex = fileIndex[depth];
    int file = direntIsFile(fileSystem[depth][currentIndex]);
    if (file == 1) {
        printf("  File: %s\n   Index: %i", fileSystem[currentPathComponents.size()][currentIndex].d_name, currentIndex);
        openFile(getCurrentPath(), fileSystem[depth][currentIndex].d_name);
    } else if (file == 0){
        printf("  Directory: %s\n   Index: %i", fileSystem[currentPathComponents.size()][currentIndex].d_name, currentIndex);

        char* newCmp = (char*)malloc(sizeof(char) * FILENAME_MAX);
        strcpy(newCmp, fileSystem[currentPathComponents.size()][currentIndex].d_name);
        
        currentPathComponents.push_back(newCmp);
        getFileListForPath();
        moveOriginOnAxisX();
    }
    glutPostRedisplay();
}

void handleBackspace(){
    if(currentPathComponents.size() > 0){
        currentPathComponents.pop_back();
        fileSystem.pop_back();
        fileIndex.pop_back();
//        getFileListForPath();
        glutPostRedisplay();
    }
}

void mainIdle() {
    glutSetWindow(mainWindowId);
}

/**
 Create mouse button menu
 */
void mainCreateMenu() {
//    glutCreateMenu(mainHandleMouseRightButtonMenuEvent);
    glutAddMenuEntry("Quit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mainInit() {
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f,0.0f,0.0f);
    setWindow();
    setViewport(0, windowWidth, 0, windowHeight);
    
    //	initSound();
    
    initTexture();
}

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



void setViewport(GLint left, GLint right, GLint bottom, GLint top) {
    glViewport(left, bottom, right - left, top - bottom);
}

void onWindowReshape(int x, int y) {
    windowWidth = x;
    windowHeight = y;
    setWindow();
    setViewport(0, windowWidth, 0, windowHeight);
    glutPostRedisplay();
}

void renderScene() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    updateCam();
    renderFloor();
    renderFileList();
}