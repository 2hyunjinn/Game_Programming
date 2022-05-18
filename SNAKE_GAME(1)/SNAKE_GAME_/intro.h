#pragma once
#include "GameFunc.h"

class Intro : public PhaseInterface
{
public:
	Intro();
	~Intro();
	void HandleEvents();
	void Update();
	void Render();

private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	int x, y; // mouse
};


