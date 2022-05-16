#pragma once
#include "SDL.h"

class Rabbit_Game : public PhaseInterface
{
public:
	Rabbit_Game();
	~Rabbit_Game();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	virtual void print_eng(int c);
	virtual void Reset();

private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
};


