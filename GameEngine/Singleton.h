//
//  Singleton.h
//  3DGameEngine
//
//  Created by Johannes Roth on 21.12.14.
//  Copyright (c) 2014 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__Singleton__
#define __3DGameEngine__Singleton__

#include <memory>

template <class T>
class CSingleton_tpl
{
public:
    inline static T *GetInstance()
    {
        static bool bInitialized = false;
        static std::unique_ptr<T> pInstance;
        
        if (!bInitialized)
        {
            pInstance = std::unique_ptr<T>(new T);
            bInitialized = true;
        }
        
        return pInstance.get();
    }
};

#endif
