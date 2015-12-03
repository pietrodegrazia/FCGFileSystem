//
//  FileManager.cpp
//  FCGFileSystem
//
//  Created by Pietro Degrazia on 11/24/15.
//  Copyright © 2015 PietroHenrique. All rights reserved.
//

#include "FileManager.hpp"

vector<dirent> currentDirList;
vector <vector<dirent> > fileSystem;
vector<int> fileIndex;
vector<char*> currentPathComponents;

int direntIsFile(dirent dir){
    if(dir.d_type == 8){
        return 1;
    } else {
        return 0;
    }
}

char* getCurrentPath(){
    int cmpSize = currentPathComponents.size() > 0 ? currentPathComponents.size() : 1;
    
    char* path = (char*)malloc(sizeof(char) * FILENAME_MAX * cmpSize);
    strcpy(path, kRootFolder);
    strcat(path, "/");
    for ( int i = 0; i < currentPathComponents.size(); i++) {
        strcat(path, currentPathComponents[i]);
        strcat(path, "/");
    }
    return path;
}


char* getCurrentPathAppending(const char* component){
    char* dirpath = (char*)malloc(sizeof(char) * FILENAME_MAX);
        strcpy(dirpath,getCurrentPath());
    char* path = (char*)malloc(sizeof(char) * FILENAME_MAX);
    
    strcpy(path, dirpath);
    strcat(path, component);
    
    return path;
}




void getFileListForPath(){
    char* dirpath = (char*)malloc(sizeof(char) * FILENAME_MAX);
    strcpy(dirpath, getCurrentPath());
    DIR *dir;
    int depth = currentPathComponents.size();
    vector<dirent> newVector;
    struct dirent *ent;
    if ((dir = opendir(dirpath)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if (strcmp(ent->d_name, "..") && strcmp(ent->d_name, ".")) {
                newVector.push_back(*ent);
            }
        }
        fileIndex.push_back(0);
        fileSystem.push_back(newVector);
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("\nˆˆˆˆˆˆˆCOULD NOT OPEN DIRECTORYˆˆˆˆˆˆˆˆˆ\n");
    }
}

















//void getFileListForPath(){
//    currentDirList.clear();
//    
//    char* dirpath = (char*)malloc(sizeof(char) * FILENAME_MAX);
//    strcpy(dirpath, getCurrentPath());
//    DIR *dir;
//    struct dirent *ent;
//    if ((dir = opendir(dirpath)) != NULL) {
//        while ((ent = readdir (dir)) != NULL) {
//            if (strcmp(ent->d_name, "..") && strcmp(ent->d_name, ".")) {
//                currentDirList.push_back(*ent);
//            }
//        }
//        printf("Loaded? -- Size: %lu", currentDirList.size());
//        printf("\n________________________________________________________\n");
//        closedir (dir);
//    } else {
//        /* could not open directory */
//        perror ("\nˆˆˆˆˆˆˆCOULD NOT OPEN DIRECTORYˆˆˆˆˆˆˆˆˆ\n");
//    }
//}