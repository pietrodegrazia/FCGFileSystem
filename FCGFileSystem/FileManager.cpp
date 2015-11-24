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


char* getCurrentPathAppending(char* component){
    
    char* dirpath = getCurrentPath();
    char* path = (char*)malloc(sizeof(char*)*256);
    
    strcpy(path, dirpath);
    //    strcat(path, "/");
    strcat(path, component);
    
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
                printf ("\n%s",path);
                
                if (file == 1){
                    printf(", File/n");
                } else if (file == 0) {
                    printf(", Directory/n");
                }
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
    }
}