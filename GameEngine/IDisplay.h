//
//  IDisplay.h
//  3DGameEngine
//
//  Created by Johannes Roth on 16.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__IDisplay__
#define __3DGameEngine__IDisplay__

#include <string>
#include "Math3D.h"

class IDisplay
{
public:
	IDisplay() {  }
	virtual ~IDisplay() {  }

	virtual void SetTitle(const std::string &title) = 0;
	virtual void SetWidth(int width) = 0;
	virtual void SetHeight(int height) = 0;
	virtual void SetSize(int width, int height) = 0;

	virtual void SetSize(const SVector2 &size) { SetSize(size.x, size.y); }

	virtual std::string GetTitle() const = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
};

#endif