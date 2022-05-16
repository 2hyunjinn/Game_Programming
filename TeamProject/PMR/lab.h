#pragma once

#include "SDL.h"

class Lab : public PhaseInterface
{
public:
	Lab();
	~Lab();

	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	virtual void current_Events();

private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination

	int character_go_left;
	int character_go_right;
	int character_go_up;
	int character_go_down;
	int button_state; // ¹öÆ°
	int character_x;
	int character_y;
};


