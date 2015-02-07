//
//  SDL2Window.h
//  3DGameEngine
//
//  Created by Johannes Roth on 16.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__SDL2Window__
#define __3DGameEngine__SDL2Window__

#include <IDisplay.h>
#include <SDL2/SDL.h>

class CSDL2Window : public IDisplay
{
public:
	CSDL2Window(const std::string &title, int width, int height);
	~CSDL2Window();

	virtual void SetTitle(const std::string &title);
	virtual void SetWidth(int width);
	virtual void SetHeight(int height);
	virtual void SetSize(int width, int height);

	virtual std::string GetTitle() const;
	virtual int GetWidth() const;
	virtual int GetHeight() const;
	virtual bool HasFocus() const;

	inline void SetHasFocus(bool hasFocus) { m_hasFocus = hasFocus; }

	inline SDL_Window *GetSDLWindow() const { return m_SDLWindow; }

private:
	SDL_Window *m_SDLWindow;
	bool m_hasFocus{ true };
};

#endif