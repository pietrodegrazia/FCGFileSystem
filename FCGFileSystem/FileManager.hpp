//
//  FileManager.hpp
//  FCGFileSystem
//
//  Created by Pietro Degrazia on 11/24/15.
//  Copyright © 2015 PietroHenrique. All rights reserved.
//

#ifndef FileManager_hpp
#define FileManager_hpp

#include <stdio.h>
#include <stdlib.h>
#include "dirent.h"
#include <ftw.h>
#include <vector>
#include <string>
#include <errno.h>

using namespace std;

//#define kRootFolder "/Users/pietrodegrazia/Documents/UFRGS/FCG/FCGFileSystem 2/FCGFileSystem/DirA"
#define kRootFolder "/Users/valcanaia/Documents/UFRGS/2015-2/FCG/Trabalho Final/FCGFileSystem/FCGFileSystem/DirA"



extern char* getCurrentPathAppending(const char* component);
extern int isFile(const char* name);
extern char* getCurrentPath();
extern void getFileListForPath();

extern vector<dirent> currentDirList;
extern vector<char*> currentPathComponents;

#endif /* FileManager_hpp */