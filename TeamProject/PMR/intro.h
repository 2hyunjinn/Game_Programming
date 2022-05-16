#pragma once
#include "SDL.h"

class Intro : public PhaseInterface
{
public:
	Intro();
	~Intro();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:
	SDL_Texture* texture_[5]; // the SDL_Texture 
	SDL_Rect source_rectangle_[5]; // the rectangle for source image
	SDL_Rect destination_rectangle_[5]; // for destination

	SDL_Surface* temp_surface;
};


