//
//  FileManager.cpp
//  FCGFileSystem
//
//  Created by Pietro Degrazia on 11/24/15.
//  Copyright © 2015 PietroHenrique. All rights reserved.
//

#include "FileManager.hpp"

vector<dirent> currentDirList;
vector<char*> currentPathComponents;

int isFile(const char* name){
    DIR* directory = opendir(name);
    
    if(directory != NULL) {
        closedir(directory);
        return 0;
    }
    
    if(errno == ENOTDIR){
        return 1;
    }
    
    return -1;
}

char* getCurrentPath(){
    int cmpSize = currentPathComponents.size() > 0 ? currentPathComponents.size() : 1;
    
    char* path = (char*)malloc(sizeof(char) * FILENAME_MAX * cmpSize);
    strcpy(path, kRootFolder);
    strcat(path, "/");
    
    if (currentPathComponents.size() == 1) {
        printf("\n");
    }
    
    for ( int i = 0; i < currentPathComponents.size(); i++) {
        strcat(path, currentPathComponents[i]);
        strcat(path, "/");
    }
    
    return path;
}


char* getCurrentPathAppending(char* component){
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
    struct dirent *ent;
    if ((dir = opendir(dirpath)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if (strcmp(ent->d_name, "..") && strcmp(ent->d_name, ".")) {
                currentDirList.push_back(*ent);

                char* path = (char*)malloc(sizeof(char) * FILENAME_MAX);
                strcpy(path, dirpath);
                strcat(path, ent->d_name);
                
                int file = isFile(path);
                printf ("\n%s",path);
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