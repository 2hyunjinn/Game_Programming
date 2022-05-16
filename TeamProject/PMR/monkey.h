#pragma once
#include "SDL.h"

class Monkey : public PhaseInterface
{
public:
	Monkey();
	~Monkey();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
};


