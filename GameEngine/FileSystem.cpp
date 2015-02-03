//
//  FileSystem.cpp
//  GameEngine
//
//  Created by Johannes Roth on 21.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "FileSystem.h"
#include <assert.h>

const CFileSystem *g_FileSys = CFileSystem::GetInstance();

CFileSystem::CFileSystem()
{
    // TODO: Implement this correctly
    m_resourcePath = "/Volumes/Daten/Development/C, C++/GameEngine/";
}

CFileSystem::~CFileSystem()
{
}

std::string CFileSystem::GetPathToResourceFile(const std::string &resourceFilename) const
{
    return m_resourcePath + resourceFilename;
}

std::string CFileSystem::GetContentsOfFile(const std::string &path) const
{
    std::ifstream file(path);
    assert(file.is_open());
    
    std::string line;
    std::string content;
    
    while (getline(file, line))
    {
        content += line + "\n";
    }
    
    file.close();
    
    return content;
}