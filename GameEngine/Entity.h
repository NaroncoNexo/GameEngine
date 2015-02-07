//
//  Entity.h
//  3DGameEngine
//
//  Created by Johannes Roth on 05.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__Entity__
#define __3DGameEngine__Entity__

#include "Transform.h"
#include <vector>
#include <memory>
#include <functional>
#include <stdarg.h>

class IEntityExtension;
class CEntity;
struct SEntityExtensionRenderParams;

class CCamera;

struct SEntityExtensionRenderParams
{
    const CCamera *camera;
};

class IEntityExtension
{
public:
    IEntityExtension() {  }
    virtual ~IEntityExtension() {  }

    virtual void Create(int argc, va_list args) = 0;
    virtual void Release() = 0;

    virtual void OnAdd() = 0;
    virtual void OnRemove() = 0;
    
    virtual void Update() = 0;
    virtual void Render(const SEntityExtensionRenderParams &params) = 0;
    
    inline void SetEntity(CEntity *entity) { m_entity = entity; }
    inline CEntity *GetEntity() const { return m_entity; }
    
protected:
    CEntity *m_entity { nullptr };
};

typedef std::function<void (CEntity *, int, va_list)> EntityConfigurator_t;

class CEntity
{
public:
    CEntity();
    virtual ~CEntity();

    void AddChild(CEntity *child);
    CEntity *AddChild(EntityConfigurator_t Configurator = [](CEntity *, int, va_list){}, int argc = 0, ...);
    void RemoveAllChildren();
    
    void RemoveFromParent();
    
    virtual void Update();
    virtual void Render(const SEntityExtensionRenderParams &params);
    
    void UpdateExtensions();
    void RenderExtensions(const SEntityExtensionRenderParams &params);
    
    template <class T> T *AddExtension(int argc = 0, ...)
    {
        T *e;
        if ((e = GetExtension<T>()) != nullptr)
        {
            return e;
        }
    
        T *extension = new T;
    
        m_extensions.push_back(extension);
        extension->SetEntity(this);
        
        va_list args;
        va_start(args, argc);
        extension->Create(argc, args);
        va_end(args);
        
        extension->OnAdd();
        
        return extension;
    }
    
    template <class T> void RemoveExtension()
    {
        IEntityExtension *extension = GetExtension<T>();

        extension->OnRemove();
        
        m_extensions.erase(std::find(m_extensions.begin(), m_extensions.end(), extension));
        extension->SetEntity(nullptr);

        delete extension;
    }

    inline void SetAutoreleasing(bool flag) { m_autoreleasing = flag; }
    
    template <class T> T *GetExtension()
    {
        for (auto ext : m_extensions)
            if (typeid(*ext) == typeid(T))
                return (T *)ext;
    
        return nullptr;
    }

    SMatrix4 GetTransformationMatrix() const;
    
    inline CTransform *GetTransform() const { return m_transform; }
    inline CEntity *GetParent() const { return m_parent; }
    inline const std::vector<CEntity *> &GetChildren() const { return m_children; }
    inline bool IsAutoreleasing() const { return m_autoreleasing; }
    
protected:
    CTransform *m_transform { nullptr };
    std::vector<CEntity *> m_children;
    std::vector<IEntityExtension *> m_extensions;
    CEntity *m_parent { nullptr };
    bool m_autoreleasing { false };
};

class CEntityRoot : public CEntity
{
public:
    CEntityRoot();
    virtual ~CEntityRoot();
    
    virtual void Update();
    virtual void Render();
    
    inline void AddCamera(CCamera *camera) { m_cameras.push_back(camera); }
    
private:
    std::vector<CCamera *> m_cameras;
};

#endif