#pragma once

#include "SDL.h"

class Stage1 : public PhaseInterface
{
public:
	Stage1();
	~Stage1();

	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	virtual void PaintText(int time_ms_);
	virtual void Reset();
	virtual void ClearGame();

private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
};

