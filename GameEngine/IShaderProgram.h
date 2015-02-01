//
//  IShaderProgram.h
//  3DGameEngine
//
//  Created by Johannes Roth on 17.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__IShaderProgram__
#define __3DGameEngine__IShaderProgram__

#include "Math3D.h"
#include "ITexture.h"
#include "IShader.h"
#include <map>
#include <vector>

enum
{
	eSHADERPROPERTY_DEPTHTESTENABLED,
	eSHADERPROPERTY_DEPTHTESTCOMPAREFUNC,
	eSHADERPROPERTY_DEPTHMASKENABLED,
	eSHADERPROPERTY_BLENDENABLED,
	eSHADERPROPERTY_BLENDEQUATION,
	eSHADERPROPERTY_BLENDSOURCEFUNC,
	eSHADERPROPERTY_BLENDDESTFUNC,
	eSHADERPROPERTY_RENDERMODE,
    eSHADERPROPERTY_CULLFACEENABLED,
    eSHADERPROPERTY_CULLFACE,
    eSHADERPROPERTY_FRONTFACE
};

enum
{
	eCOMPAREFUNC_NEVER,
	eCOMPAREFUNC_LESS,
	eCOMPAREFUNC_EQUAL,
	eCOMPAREFUNC_LOWEREQUAL,
	eCOMPAREFUNC_GREATER,
	eCOMPAREFUNC_NOTEQUAL,
	eCOMPAREFUNC_GREATEREQUAL,
	eCOMPAREFUNC_ALWAYS
};

enum
{
	eBLENDFUNC_ZERO,
	eBLENDFUNC_ONE,
	eBLENDFUNC_SOURCECOLOR,
	eBLENDFUNC_ONEMINUSSOURCECOLOR,
	eBLENDFUNC_DESTCOLOR,
	eBLENDFUNC_ONEMINUSDESTCOLOR,
	eBLENDFUNC_SOURCEALPHA,
	eBLENDFUNC_ONEMINUSSOURCEALPHA,
	eBLENDFUNC_DESTALPHA,
	eBLENDFUNC_ONEMINUSDESTALPHA,
	eBLENDFUNC_CONSTANTCOLOR,
	eBLENDFUNC_ONEMINUSCONSTANTCOLOR,
	eBLENDFUNC_CONSTANTALPHA,
	eBLENDFUNC_ONEMINUSCONSTANTALPHA,
	eBLENDFUNC_SOURCEALPHASATURATE
};

enum
{
	eBLENDEQUATION_ADD,
	eBLENDEQUATION_SUBTRACT,
	eBLENDEQUATION_REVERSESUBTRACT
};

enum
{
	eRENDERMODE_SOLID,
	eRENDERMODE_WIREFRAME
};

enum
{
    eCULLFACE_FRONT,
    eCULLFACE_BACK
};

enum
{
    eFRONTFACE_CLOCKWISE,
    eFRONTFACE_COUNTERCLOCKWISE
};

class IShaderProgram
{
public:
	IShaderProgram() {  }
	virtual ~IShaderProgram() {  }
    
    virtual void AddShader(IShader *shader) = 0;
    virtual void Build() = 0;

	virtual void SetProperties() const = 0;
	virtual void Use() const = 0;
    
    virtual void SetUniformInt(const std::string &uniformName, int value) const = 0;
    virtual void SetUniformFloat(const std::string &uniformName, float value) const = 0;
    virtual void SetUniformVector3(const std::string &uniformName, const SVector3 &vector) const = 0;
    virtual void SetUniformColor(const std::string &uniformName, const SColor &color) const = 0;
    virtual void SetUniformMatrix4(const std::string &uniformName, const SMatrix4 &matrix) const = 0;
    
    virtual void SetUniformDataInt(const std::string &uniformName, const void *value) const = 0;
    virtual void SetUniformDataFloat(const std::string &uniformName, const void *value) const = 0;
    virtual void SetUniformDataVector3(const std::string &uniformName, const void *vector) const = 0;
    virtual void SetUniformDataColor(const std::string &uniformName, const void *color) const = 0;
    virtual void SetUniformDataMatrix4(const std::string &uniformName, const void *matrix) const = 0;
    
    virtual void BindTexture(const std::string &textureName, const ITexture *texture, int textureSlot = 0) const = 0;

    virtual void SetBool(int property, bool value) { m_boolValues[property] = value; }
    virtual void SetFloat(int property, float value) { m_floatValues[property] = value; }
    virtual void SetInt(int property, int value) { m_intValues[property] = value; }
    virtual void SetColor(int property, const SColor &value) { m_colorValues[property] = value; }

    virtual const std::vector<std::string> &GetUniforms() const = 0;

protected:
    mutable std::map<int, bool> m_boolValues;
    mutable std::map<int, float> m_floatValues;
    mutable std::map<int, int> m_intValues;
    mutable std::map<int, SColor> m_colorValues;
    std::vector<IShader *> m_attachedShaders;
};

#endif