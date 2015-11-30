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


int currentIndex = 0;

int zero = 0;

void updateIndex(bool increment){
    if (increment && (currentIndex+1 < currentDirList.size() ) ) {
        currentIndex++;
    } else if( !(increment) && ( currentIndex-1 >= 0 ) ){
        currentIndex--;
    }
}


void handleEnterPressed(){
    printf("\n************* ENTER PRESSED ****************\n");
    char* path = (char*)malloc(sizeof(char) * FILENAME_MAX);
    strcpy(path, getCurrentPathAppending(currentDirList[currentIndex].d_name));

    printf("Selected: %s\n", path);
    
    int file = isFile(path);
    if (file == 1) {
        printf("File: %s\n Index: %i", currentDirList[currentIndex].d_name, currentIndex);
    } else if (file == 0){
        printf("Directory: %s\n Index: %i", currentDirList[currentIndex].d_name, currentIndex);

        char* newCmp = (char*)malloc(sizeof(char) * FILENAME_MAX);
        strcpy(newCmp, currentDirList[currentIndex].d_name);
        
        currentPathComponents.push_back(newCmp);
        getFileListForPath();
        moveOriginOnAxisX();
    }
    glutPostRedisplay();
}

void handleBackspace(){
    if(currentPathComponents.size() > 0){
        currentPathComponents.pop_back();
        currentDirList.clear();
        getFileListForPath();
        glutPostRedisplay();
    }
}

void mainIdle() {
    /**
     Set the active window before send an glutPostRedisplay call
     so it wont be accidently sent to the glui window
     */
    glutSetWindow(mainWindowId);
//    glutPostRedisplay();
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