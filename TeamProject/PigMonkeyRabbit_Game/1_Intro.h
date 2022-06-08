#pragma once
#include "0_GameFunc.h";

class Intro : public PhaseInterface
{
public:
	Intro();
	~Intro();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:
	SDL_Texture* texture_[6]; // the SDL_Texture 
	SDL_Rect source_rectangle_[6]; // the rectangle for source image
	SDL_Rect destination_rectangle_[6]; // for destination

	SDL_Surface* temp_surface;

	Mix_Chunk* click_sound;
	Mix_Music* intro_music;

	int time;
	int cnt;
};
