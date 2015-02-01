//
//  FileSystem.h
//  GameEngine
//
//  Created by Johannes Roth on 21.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __GameEngine__FileSystem__
#define __GameEngine__FileSystem__

#include "Singleton.h"
#include <string>
#include <fstream>

class CFileSystem : public CSingleton_tpl<CFileSystem>
{
public:
    CFileSystem();
    ~CFileSystem();
    
    std::string GetPathToResourceFile(const std::string &resourceFilename) const;
    std::string GetContentsOfFile(const std::string &path) const;
    
private:
    std::string m_resourcePath;
};

extern const CFileSystem *g_FileSys;

#endif /* defined(__GameEngine__FileSystem__) */
