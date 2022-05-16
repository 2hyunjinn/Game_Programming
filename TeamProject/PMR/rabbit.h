#pragma once
#include "SDL.h"

class Rabbit : public PhaseInterface
{
public:
	Rabbit();
	~Rabbit();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
};


